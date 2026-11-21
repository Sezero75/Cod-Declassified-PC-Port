"""Build a private Windows installation from the player's local inputs."""
import hashlib
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import zipfile
from pathlib import PureWindowsPath

KIT = Path(__file__).resolve().parent
TITLE = "PCSB00213"
EXPECTED = "87a69abf822985a83e65fa2da81714f18bcc53ed0b5981001fe2a4b764e0cf1a"
MODULES = "libc libgxm_es4 libgpu_es4 libfios2 np_matching2 libssl np_common librudp".split()

def unpack_game(archive, target):
    """Accept a normal root-layout VPK/ZIP, copying just the input files we use."""
    roots = {"audio", "video", "misc", "sce_sys", "sce_module", "mai_moe"}
    single = {"eboot.bin", "eboot.bin.elf", "build.psa", "hud_settings.ini"}
    total = 0
    with zipfile.ZipFile(archive) as z:
        for entry in z.infolist():
            parts = entry.filename.split("/")
            if entry.is_dir() or parts[0] not in roots and entry.filename not in single:
                continue
            if any(not part or part in {".", ".."} or part.endswith((" ", ".")) or
                   any(ord(c)<32 or c in '<>:"\\|?*' for c in part) or
                   PureWindowsPath(part).is_reserved() for part in parts):
                raise ValueError("Invalid filename in game archive.")
            total += entry.file_size
            if total > 8 * 1024**3:
                raise ValueError("Archive exceeds the supported game size.")
            output = target.joinpath(*parts)
            output.parent.mkdir(parents=True, exist_ok=True)
            with z.open(entry) as source, output.open("xb") as dest:
                shutil.copyfileobj(source, dest)


def install(nativ, game, firmware, destination):
    if destination.exists() or destination.is_relative_to(KIT):
        raise ValueError("Choose a new installation folder outside the GitHub project.")
    if (nativ / "version.txt").read_text().strip() != "v0.1.5":
        raise ValueError("Select the Project Nativ v0.1.5 Windows installation.")
    destination.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="declassified-build-", dir=destination.parent) as temporary:
        scratch = Path(temporary)
        if game.is_file():
            unpack_game(game, scratch / "input")
            game = scratch / "input"
        if not (game / "build.psa").is_file():
            raise ValueError("Select the game folder containing build.psa, or a VPK/ZIP with build.psa at its root.")
        tools = scratch / "tools"
        library = scratch / "library"
        title = library / "decrypted" / TITLE
        elf = title / "elf"
        elf.mkdir(parents=True)
        for folder in ("runtime", "pipeline", "recompiler", "third_party", "decrypt"):
            shutil.copytree(nativ / folder, tools / folder)
        shutil.copytree(KIT / "overlay", tools, dirs_exist_ok=True)
        pack = tools / "packs" / TITLE
        pack.mkdir(parents=True)
        shutil.copyfile(KIT / "pack.toml", pack / "pack.toml")
        shutil.copyfile(nativ / "version.txt", tools / "version.txt")
        python = nativ / "python/python.exe"
        env = dict(os.environ, ATIV_DUMP=str(library), ATIV_WIN_TOOLCHAIN=str(nativ / "toolchain"),
                   RECOMP_CPU="generic", JOBS="4", PYTHONUTF8="1")
        def run(*args):
            subprocess.run(list(args), env=env, check=True, cwd=scratch)
        def pipeline(*args):
            run(python, tools / "pipeline/vitarecomp.py", *args)
        inputs = scratch / "modules"
        inputs.mkdir()
        for name, parent in (("eboot.bin", game), ("libc.suprx", game / "sce_module"),
                             ("libfios2.suprx", game / "sce_module")):
            prepared = parent / (name + ".elf")
            if prepared.is_file():
                shutil.copyfile(prepared, elf / prepared.name)
            elif name == "eboot.bin" and (game / "mai_moe/eboot_origin.bin").is_file():
                shutil.copyfile(game / "mai_moe/eboot_origin.bin", inputs / name)
            elif (parent / name).is_file():
                shutil.copyfile(parent / name, inputs / name)
        if any(inputs.iterdir()):
            run(python, tools / "decrypt/fself2elf.py", inputs, elf)
        main = elf / "eboot.bin.elf"
        if not main.is_file() or hashlib.sha256(main.read_bytes()).hexdigest() != EXPECTED:
            raise ValueError("This build needs the EU 1.00 game (PCSB00213). For an encrypted copy, import it in Project Nativ first and select its prepared app0 folder.")
        (title / "version").write_text("1.00\n")
        if firmware.is_file():
            pipeline("firmware", firmware)
        else:
            if not (firmware / "os0/us/libgxm_es4.suprx.elf").is_file():
                raise ValueError("Select the Vita 3.74 firmware PUP or the prepared 3.74 folder.")
            shutil.copytree(firmware, library / "firmware/3.74")
        if not (library / "firmware/3.74").is_dir():
            raise ValueError("The supported firmware version is 3.74.")
        for command in ("analyze", "recompile", "build"):
            pipeline(command, TITLE)
        app = scratch / "finished"
        data = app / "Data"
        assets = data / "app0"
        assets.mkdir(parents=True)
        for folder in ("audio", "video", "misc"):
            shutil.copytree(game / folder, assets / folder)
        for name in ("build.psa", "hud_settings.ini", "sce_sys/param.sfo"):
            target = assets / name
            target.parent.mkdir(exist_ok=True)
            shutil.copyfile(game / name, target)
        if (game / "sce_sys/trophy").is_dir():
            shutil.copytree(game / "sce_sys/trophy", assets / "sce_sys/trophy")
        for name in ["game_host.exe", "SDL3.dll", "game.img"] + [m + ".img" for m in MODULES]:
            shutil.copyfile(title / "recomp" / name, data / name)
        csc = Path(os.environ["WINDIR"]) / "Microsoft.NET/Framework64/v4.0.30319/csc.exe"
        run(csc, "/nologo", "/target:winexe", "/reference:System.Windows.Forms.dll",
            "/reference:System.Drawing.dll", "/out:" + str(app / "Declassified.exe"), KIT / "Launch.cs")
        app.rename(destination)
    print("Ready to play:", destination / "Declassified.exe")


if __name__ == "__main__":
    try:
        install(*(Path(arg).resolve() for arg in sys.argv[1:]))
    except (ValueError, OSError, zipfile.BadZipFile, subprocess.CalledProcessError) as error:
        sys.exit("Setup stopped: " + str(error))
