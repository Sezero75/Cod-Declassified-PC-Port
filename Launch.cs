using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Text.RegularExpressions;
using System.Windows.Forms;

internal static class Launch
{
    private static readonly string[] Modules = {
        "libc", "libgxm_es4", "libgpu_es4", "libfios2", "np_matching2", "libssl", "np_common", "librudp"
    };

    private static bool ReadService(string file, out string endpoint, out string key)
    {
        endpoint = key = "";
        if (!File.Exists(file)) return false;
        foreach (var raw in File.ReadLines(file)) {
            var line = raw.Trim();
            if (line.StartsWith("endpoint=")) endpoint = line.Substring(9).Trim();
            if (line.StartsWith("public_key=")) key = line.Substring(11).Trim().ToLowerInvariant();
        }
        var parts = endpoint.Split(':');
        ushort port;
        return parts.Length == 2 && Regex.IsMatch(parts[0], @"\A[A-Za-z0-9.\-]+\z")
            && UInt16.TryParse(parts[1], out port) && port > 0
            && Regex.IsMatch(key, @"\A[0-9a-f]{64}\z");
    }

    private static string ReadRenderer(string path)
    {
        if (!File.Exists(path)) return "auto";
        string value = File.ReadAllText(path).Trim();
        return IsRenderer(value) ? value : "auto";
    }

    private static bool IsRenderer(string value)
    {
        return value == "auto" || value == "vulkan" || value == "direct3d12";
    }

    private static decimal ReadFov(string profile)
    {
        decimal value = 1;
        string path = Path.Combine(profile, "settings.ini");
        if (File.Exists(path))
            foreach (string line in File.ReadLines(path)) {
                string[] parts = line.Split(new char[] {'='}, 2);
                decimal parsed;
                if (parts.Length == 2 && parts[0].Trim() == "fov" &&
                    Decimal.TryParse(parts[1].Trim(), NumberStyles.Float, CultureInfo.InvariantCulture, out parsed))
                    value = Math.Min(1.50m, Math.Max(0.75m, parsed));
            }
        return value;
    }

    private static bool ChooseGraphics(ref string renderer, ref decimal fov, ref bool performance)
    {
        using (var dialog = new Form()) {
            dialog.Text = "Declassified";
            dialog.StartPosition = FormStartPosition.CenterScreen;
            dialog.FormBorderStyle = FormBorderStyle.FixedDialog;
            dialog.MaximizeBox = false;
            dialog.AutoScaleMode = AutoScaleMode.Dpi;
            dialog.Font = SystemFonts.MessageBoxFont;
            dialog.ClientSize = new Size(392, 235);
            dialog.Icon = Icon.ExtractAssociatedIcon(Application.ExecutablePath);
            var backend = new ComboBox { Left = 20, Top = 37, Width = 352, DropDownStyle = ComboBoxStyle.DropDownList };
            bool dx = HasDirectX();
            string[] ids = dx ? new[] { "auto", "vulkan", "direct3d12" } : new[] { "vulkan" };
            backend.Items.AddRange(dx ? new[] { "Automatic (Vulkan, then DirectX 12)", "Vulkan",
                "DirectX 12 (Mesa Dozen)" } : new[] { "Vulkan" });
            backend.SelectedIndex = Math.Max(0, Array.IndexOf(ids, renderer));
            var zoom = new NumericUpDown { Left = 20, Top = 101, Width = 86, Minimum = .75m, Maximum = 1.50m,
                Increment = .05m, DecimalPlaces = 2, Value = fov };
            var light = new CheckBox { Text = "Performance mode (1x resolution and FXAA)", Left = 20, Top = 140, AutoSize = true, Checked = performance };
            var play = new Button { Text = "Play", Left = 278, Top = 185, Width = 94, Height = 30, DialogResult = DialogResult.OK };
            dialog.Controls.AddRange(new Control[] {
                new Label { Text = "Graphics renderer", Left = 20, Top = 16, AutoSize = true }, backend,
                new Label { Text = "Field of view", Left = 20, Top = 80, AutoSize = true }, zoom,
                new Label { Text = "1.00 is the original view", Left = 115, Top = 105, AutoSize = true }, light, play
            });
            dialog.AcceptButton = play;
            if (dialog.ShowDialog() != DialogResult.OK) return false;
            renderer = ids[backend.SelectedIndex];
            fov = zoom.Value;
            performance = light.Checked;
            return true;
        }
    }

    private static bool HasDirectX() {
        string folder = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Data", "Direct3D12");
        return Array.TrueForAll(new[] { "dzn_icd.x86_64.json", "dxil.dll", "vulkan-1.dll", "vulkan_dzn.dll" },
            name => File.Exists(Path.Combine(folder, name)));
    }

    private static int RunRenderer(ProcessStartInfo launch, string renderer, string data, string logPath,
                                   bool relayConfigured, out bool failedDuringGraphics)
    {
        launch.EnvironmentVariables["DECLASSIFIED_RENDERER"] = renderer;
        if (renderer == "direct3d12") {
            string folder = Path.Combine(data, "Direct3D12");
            string manifest = Path.Combine(folder, "dzn_icd.x86_64.json");
            launch.EnvironmentVariables["VK_DRIVER_FILES"] = manifest;
            launch.EnvironmentVariables["VK_ICD_FILENAMES"] = manifest;
            launch.EnvironmentVariables["SDL_VULKAN_LIBRARY"] = Path.Combine(folder, "vulkan-1.dll");
            launch.EnvironmentVariables["VK_LOADER_LAYERS_DISABLE"] = "~implicit~";
        }
        failedDuringGraphics = false;
        using (var log = new StreamWriter(logPath, false)) {
            log.AutoFlush = true;
            if (!relayConfigured) log.WriteLine("Public matchmaking service is not configured.");
            log.WriteLine("Selected renderer: " + renderer);
            using (var game = Process.Start(launch)) {
                string line;
                while ((line = game.StandardError.ReadLine()) != null) {
                    log.WriteLine(line);
                    if (line == "renderer: initializing") failedDuringGraphics = true;
                    if (line == "renderer: ready") failedDuringGraphics = false;
                }
                game.WaitForExit();
                return game.ExitCode;
            }
        }
    }

    [STAThread]
    private static int Main()
    {
        try {
            string data = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Data");
            string root = Environment.GetEnvironmentVariable("DECLASSIFIED_DATA");
            if (String.IsNullOrWhiteSpace(root))
                root = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "Declassified-Windows");
            string profile = Directory.CreateDirectory(Path.Combine(Path.GetFullPath(root), "profile")).FullName;
            Directory.CreateDirectory(Path.Combine(profile, "fs"));
            var launch = new ProcessStartInfo {
                FileName = Path.Combine(data, "game_host.exe"), WorkingDirectory = profile,
                Arguments = "\"" + Path.Combine(data, "game.img") + "\" 810f5614 100000000000",
                UseShellExecute = false, CreateNoWindow = true, RedirectStandardError = true
            };
            var env = launch.EnvironmentVariables;
            string endpoint, key;
            bool relayConfigured = ReadService(Path.Combine(data, "matchmaking.ini"), out endpoint, out key);
            env["RECOMP_TITLE"] = "PCSB00213";
            env["RECOMP_GAME_NAME"] = "Call of Duty - Black Ops Declassified";
            env["RECOMP_MODULES"] = String.Join(",", Array.ConvertAll(Modules, n => Path.Combine(data, n + ".img")));
            env["RECOMP_FS"] = "fs";
            env["DECLASSIFIED_ASSETS"] = Path.Combine(data, "app0");
            env["RECOMP_SETTINGS_SHARED"] = "./shared-settings.ini";
            env["RECOMP_LOG"] = "0";
            env.Remove("RECOMP_ONLINE");
            env["RECOMP_GAME_OPTIONS"] = "online,fov";
            env["DECLASSIFIED_RELAY_ONLY"] = "1";
            env["DECLASSIFIED_RELAY_KEY"] = relayConfigured ? key : "";
            env["RECOMP_ONLINE_RELAYS"] = relayConfigured ? endpoint : "";
            env["RECOMP_ONLINE_PEERS"] = "";
            env["RECOMP_ONLINE_OVERLAY"] = "1";
            env["RECOMP_ONLINE_NO_DIRECT"] = "1";
            env["RECOMP_ONLINE_NO_LAN"] = "1";
            env["RECOMP_ONLINE_NO_DHT"] = "1";
            env["RECOMP_ONLINE_UPNP"] = "0";
            env["RECOMP_MATCHING_SERVER"] = "";
            env.Remove("RECOMP_ONLINE_HOST_PORT");
            env["RECOMP_NET_REDIRECT"] = "www.google.com=127.0.0.1";
            string logPath = Path.Combine(profile, "session.log");
            string rendererPath = Path.Combine(profile, "renderer.txt");
            string requested = ReadRenderer(rendererPath);
            string qualityPath = Path.Combine(profile, "performance.txt");
            bool performance = File.Exists(qualityPath) && File.ReadAllText(qualityPath).Trim() == "1";
            decimal previousFov = ReadFov(profile), fov = previousFov;
            string scripted = Environment.GetEnvironmentVariable("DECLASSIFIED_RENDERER");
            if (IsRenderer(scripted)) requested = scripted;
            else if (Environment.GetEnvironmentVariable("RECOMP_HEADLESS") == null) {
                Application.EnableVisualStyles();
                if (!ChooseGraphics(ref requested, ref fov, ref performance)) return 0;
                File.WriteAllText(rendererPath, requested);
                File.WriteAllText(qualityPath, performance ? "1" : "0");
            }
            if (fov != previousFov) env["DECLASSIFIED_START_FOV"] = fov.ToString(CultureInfo.InvariantCulture);
            if (performance) {
                env["RECOMP_RENDER_SCALE"] = "1";
                env["RECOMP_FSR"] = "0";
                env["RECOMP_POST_AA"] = "1";
            }
            var candidates = new List<string>();
            if (requested == "auto") {
                candidates.Add("vulkan");
                if (HasDirectX()) candidates.Add("direct3d12");
            } else candidates.Add(requested);
            int result = 1;
            bool graphicsFailure = false;
            foreach (string candidate in candidates) {
                result = RunRenderer(launch, candidate, data, logPath, relayConfigured, out graphicsFailure);
                if (result == 0 || !graphicsFailure || candidate == candidates[candidates.Count-1]) break;
                File.Copy(logPath, Path.Combine(profile, "session-" + candidate + ".log"), true);
            }
            if (result != 0) throw new IOException(graphicsFailure
                ? "Graphics startup failed. Select another renderer in the launcher. Details are in " + logPath
                : "The game stopped. See " + logPath);
            return 0;
        } catch (Exception ex) {
            if (Environment.GetEnvironmentVariable("RECOMP_HEADLESS") == null)
                MessageBox.Show(ex.Message, "Declassified", MessageBoxButtons.OK, MessageBoxIcon.Error);
            return 1;
        }
    }
}
