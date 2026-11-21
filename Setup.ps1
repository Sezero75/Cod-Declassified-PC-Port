param([string]$Game, [string]$Nativ, [string]$Firmware, [string]$Destination)
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Windows.Forms
function Select-Folder([string]$label) {
    $picker = New-Object System.Windows.Forms.FolderBrowserDialog
    $picker.Description = $label
    $picker.ShowNewFolderButton = $false
    try {
        if ($picker.ShowDialog() -ne 'OK') { throw 'Setup cancelled.' }
        return $picker.SelectedPath
    } finally { $picker.Dispose() }
}
try {
    if (!$Game) { $Game = Select-Folder 'Select your extracted EU PCSB00213 game folder (the one containing build.psa).' }
    if (!$Nativ) { $Nativ = Select-Folder 'Select your Project Nativ v0.1.5 folder (the one containing Project Nativ.exe).' }
    if (!$Firmware) {
        $picker = New-Object System.Windows.Forms.OpenFileDialog
        $picker.Title = 'Select your PS Vita 3.74 firmware update'
        $picker.Filter = 'Vita firmware (*.PUP)|*.pup'
        try {
            if ($picker.ShowDialog() -ne 'OK') { throw 'Setup cancelled.' }
            $Firmware = $picker.FileName
        } finally { $picker.Dispose() }
    }
    if (!$Destination) { $Destination = Join-Path $env:LOCALAPPDATA 'Declassified Community\Game' }
    $python = Join-Path $Nativ 'python\python.exe'
    if (!(Test-Path -LiteralPath $python)) { throw 'The selected folder is missing Project Nativ for Windows.' }
    & $python -B (Join-Path $PSScriptRoot 'setup_game.py') $Nativ $Game $Firmware $Destination
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    [void][System.Windows.Forms.MessageBox]::Show("Your game is ready. Open Declassified.exe in this folder:`n$Destination", 'Setup complete')
} catch { [Console]::Error.WriteLine($_.Exception.Message); exit 1 }
