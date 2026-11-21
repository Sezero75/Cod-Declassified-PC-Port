Unofficial native Call of Duty: Black Ops Declassified port for pc was built form the PS Vita’s Version. Declassified PC brings it to Windows with direct mouse aiming, keyboard controls, and a camera that can show more of the world on an ultrawide monitor.

You bring your own copy of the game and PS Vita firmware. The build kit uses Project Nativ to recompile the game and the system libraries it needs into a native Windows application. Once setup finishes, launch Declassified.exe to play.
What changes on PC
- Mouse and keyboard. Aim with the mouse, move with WASD, and click through menus. On-screen prompts show the keyboard controls.
- Controller support. Use a familiar shooter layout with stick-click sprint and melee, plus tap-to-crouch and hold-to-prone.
- Widescreen and field of view. Play at 21:9 or 32:9, adjust the FOV, and choose whether the HUD sits at the screen edges or stays centered in a 16:9 area.
- Graphics options. Increase the rendering resolution and choose between FXAA and temporal anti-aliasing. Vulkan is the default renderer.
- Campaign and multiplayer. Both use the same launcher. Online lobby discovery requires a configured matchmaking relay.

The kit supports the European PS Vita release, version 1.00 (PCSB00213). Drag your extracted game folder or compatible VPK/ZIP onto Add Game.cmd, then select Project Nativ for Windows v0.1.5 and your PS Vita 3.74 firmware. Setup builds the playable copy on your PC. The repository contains the build tools and port changes. Players supply the game and firmware themselves.

Credits
- Original game — Nihilistic Software developed Call of Duty: Black Ops Declassified for PS Vita. Activision published it. [Original PlayStation announcement](https://blog.playstation.com/2012/08/14/see-the-first-trailer-for-call-of-duty-black-ops-declassified-on-ps-vita/)
- Native recompilation and runtime — Project Nativ and its contributors built the tools that translate the Vita game into a Windows executable and run it on PC. [Project Nativ](https://github.com/TheLostPantheon/nativ)
- Declassified PC adaptation — @Sezero75 the Windows build kit and the game-specific work on mouse aiming, controller mappings, widescreen, FOV, and rendering fixes.
- Third-party software — Lee Salzman’s ENet provides networking components. AMD FidelityFX provides the FSR technology used for temporal anti-aliasing. Additional upstream credits are listed in THIRD_PARTY.md.
