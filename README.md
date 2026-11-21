# Declassified PC build kit

Build an unofficial Windows x64 port of Black Ops Declassified from your own EU copy (PCSB00213, version 1.00). The installer checks the game's executable against the version supported by the controller, camera and widescreen changes.

## Add your game

1. Extract the Windows x64 distribution of **Project Nativ v0.1.5**. Keep its bundled Python and compiler together. [Project Nativ releases](https://github.com/TheLostPantheon/nativ/releases/tag/v0.1.5)
2. Extract this build kit to a separate folder. Have your own PS Vita 3.74 firmware update file and EU game available.
3. **Drag your game folder or root-layout VPK/ZIP onto `Add Game.cmd`.** You can also double-click it and select an extracted game folder. Choose the Project Nativ folder and firmware file when prompted.
4. Wait for compilation to finish. Open **`%LOCALAPPDATA%\Declassified Community\Game\Declassified.exe`** to play. Subsequent launches go straight through that executable.

The game folder should contain `build.psa`, `audio`, `video` and the main executable. If you have a licensed encrypted package, prepare it using Project Nativ's game import first, then select its `decrypted\PCSB00213\app0` folder. Save files are stored in the launcher's Declassified-Windows profile.

The kit uses Vulkan by default. The launcher also recognizes a separately installed compatible Mesa Dozen runtime under `Data\Direct3D12`. Online discovery requires a configured relay. This repository includes no hosted matchmaking service or private relay credentials.

## Build location and development

The installer creates a temporary build beside the destination, verifies the main executable, recompiles the game locally and copies the playable files into a new folder. To build another revision, supply a fresh destination. For prepared firmware, pass the 3.74 folder containing `os0` and `vs0`.

```powershell
.\Setup.ps1 -Nativ 'D:\Project Nativ' -Game 'D:\My games\PCSB00213' -Firmware 'D:\Firmware\PSVUPDAT.PUP' -Destination 'D:\Games\Declassified'
```

The `overlay` directory contains source changes applied over the Windows v0.1.5 tool distribution during the build. The GPL-2.0-or-later terms and upstream notices are included in `LICENSE` and `THIRD_PARTY.md`. ENet retains its license in `overlay/third_party/enet/LICENSE`. Keep game dumps, generated game code, firmware, private credentials and finished builds outside the repository and its GitHub Releases.
