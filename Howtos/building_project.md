---
layout: default_c
RefPages:
- building_project
- setup_linux
- setup_win
--- 

<br>

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  build the sample project</span>

## Introduction

This project uses CMake (the CMakeLists.txt file) to configuring the build process for both Windows and Linux while using the same project source location, the WSL will use the mount to compile and build the Linux version on the Windows disk.

## Build for Windows

Before building the project with on of the methods described below, **make sure:**

- That the path to ***vcvars64.bat*** is correctly set in the file: ***./cmake/CMakeLists_Init-env.bat***
  - to find the location of this batch file you can ues the following Power-shell command:
    <pre class="nje-cmd-one-line-sm-indent1">Get-ChildItem -Path "C:\" -Filter "vcvars64.bat" -Recurse -ErrorAction SilentlyContinue </pre>

### Using Visual Studio 2022 (any edition)

This section describes building with **Visual Studio 2022** (including the Community Edition) It configures the build environment for Microsoft’s own make utility: ***NMake*** and uses the ***CMakePresets.json*** to read the configuration.

1. In a CLI open the root folder of the project.
1. In the root folder execute theses commands once:
   - <pre class="nje-cmd-one-line-sm-indent1">cmake --preset=windows-nmake-debug</pre>
   - <pre class="nje-cmd-one-line-sm-indent1">cmake --preset=windows-nmake-release</pre>

  <div class="nje-expect-multi-lines-indent2">
  This will create the dedicated output folders:
  - build-win-vs\debug
  - build-win-vs\release
  - **Make sure** to copy the ***glfw3.dll*** to these folder when not using a static library but a DLL!
  </div>
  <div class="nje-br2"> </div>

3\. Open VS 2022. And use the command  **File ➜ Open ➜ Folder**  option to open the project folder (create a **.vs** folder in the root)  
4\. At the top of Visual Studio, locate the Startup Item drop-down near the “Start” (▶️) button  
5\. Select **glfw_sample_[].exe** this will set it as startup projects  
6\. In the build combo-box you should have the options: <br>
    &nbsp; &nbsp;***- PRJ-build(Debug)***  
    &nbsp; &nbsp;***- PRJ-build(Release)***  
7\. Use the normal Visual Studio method to debug and run the program  
8\. The output from Visual Studio can be found in the sub folder: **./build-win-vs**

### Using Terminal (NMake)

1. Open the root folder in a Power-Shell terminal
1. Run the command: <span class="nje-cmd-inline-sm">./build.ps1 ,/span
1. Note: you can switch the Debug and release build in the ***./build.ps1** script at the top
1. The output from Visual Studio can be found in the sub folder: **./build-win**

<div class="nje-expect-multi-lines-indent1">

**The `build.ps1` script will:**  

- Setup the Visual Studio build environment variables.
- Run the CMake command to configure the **makefile** for NMake: <span class="nje-cmd-inline-sm">sh  cmake .. -G "NMake Makefiles"</pre>
- Runs the **NMake** command to build the project based on the above generated makefile.

</div>

### Visual Studio Code

To develop in Visual Code:

- Open the root folder of the project  In Visual Studio Code
- Than use the: Terminal -> Build Windows App. This will actually use the same script as used in 3.1.2 "Using Terminal (NMake)"
- The output from Visual Studio can be found in the sub folder: **./build-win**
- You may need to adjust the ./vscode/launch.json file to make sure it points to the correct executable

---
<div class="nje-br1"> </div>

## Build for Linux

This section describes the building of the program using the GNU Make tool, it assumes that the source on is located under the Windows mount point (usual /mnt/c or something) While this is for Linux complications slower(2 to 5 times) this is fine for small projects. For large projects you may consider to sync the mounted folder to the Linux filesystem first

- From the project folder (`/mnt/d/myproject`) execute:
  - `./build.sh`

**Thats's all!** And Of course you can use the VSC and build it with Visual Studio code as described above in ***section Visual Studio Code***

<div class="nje-br2"> </div>

<sub><i> This file is part of: GLFW-Skia C++ Template Stack Copyright (c) 2025 Nico Jan Eelhart. This source code is licensed under the MIT License found in the 'LICENSE.md' file in the root directory of this source tree.</i>
</sub>

<p align="center">─── ✦ ───</p>