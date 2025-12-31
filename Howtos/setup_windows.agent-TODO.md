

<br>

<!-- copilot-ignore-start -->
<small>***Note*** *instructions for AI Agent VSC for manual instruction [Linux go here](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_linux)*
</small>
<!-- copilot-ignore-end -->


# 1 Windows Setup Instruction

1. Create folder: win (if not present)
1. Change directory: cd dependencies\win
1. Download glfw-3.4.zip into win
1. Extract glfw-3.4.zip so files are directly inside glfw-3.4 (not nested)
1. Check if extraction created a nested folder: dependencies\win\glfw-3.4\glfw-3.4
1. If nested, move all files and subfolders from dependencies\win\glfw-3.4\glfw-3.4 to dependencies\win\glfw-3.4
1. Remove the now-empty nested folder dependencies\win\glfw-3.4\glfw-3.4
1. Create folder: dependencies\win\glfw-3.4\outdll (if not present)
1. Change directory: cd dependencies\win\glfw-3.4\outdll
1. Run: cmake .. -G "Visual Studio 17 2022" -A x64 -DBUILD_SHARED_LIBS=ON
1. Search for msbuild.exe on the system (PowerShell search)
1. Run: vcvars64.bat (default path provided)
1. Build: & msbuild GLFW.sln /p:Configuration=Debug /p:Platform=x64
1. Copy the generated glfw3.dll file to the project root
1. Update windows.cmake as specified (include/lib paths, variable values)
1. Run: ninja --version
1. If not installed, download and extract ninja to win
1. Add ninja to system PATH and verify with ninja --version
1. Remove old Skia-related environment variables and paths (as specified)
1. Change directory: cd dependencies\win
1. Clone Skia: git clone --recursive https://skia.googlesource.com/skia.git
1. Change directory: cd dependencies\win\skia
1. Checkout stable branch: git checkout chrome/m126
1. Sync Skia dependencies: python tools\git-sync-deps
1. Test GN: .\bin\gn --version
1. Create folder: mkdir out\Debug
1. Write GN args to out\Debug\args.gn (exact content from guide)
1. Generate build files: .\bin\gn gen out\Debug
1. Build: ninja -C out\Debug
1. Verify output: out\Debug\skia.lib, etc.
1. Update windows.cmake as specified (include/lib paths, variable values)
1. Download and build libjpeg-turbo as specified
1. Create folder: mkdir out\Release
1. Write GN args to out\Release\args.gn (exact content from guide)
1. Generate build files: .\bin\gn gen out\Release
1. Build: ninja -C out\Release
1. Verify output

<span style="color: #6d757dff; font-size: 13px; font-style: italic;"> <br>
<i><b>License</b><br>This file is part of: **GLFW-Skia C++ Template Stack**  Copyright (c) 2025-2026 Nico Jan Eelhart.This repository is [MIT licensed](MIT-license.md) and free to use. For optional commercial support, customization, training, or long-term maintenance, see [COMMERCIAL.md](COMMERCIAL.md).</i>
</span>

<br>
<p align="center">─── ✦ ───</p>
