---
layout: default_c
RefPages:
- building_project
- setup_linux
- setup_win

TableCont:
- Introduction
- Build for Windows
- Build for Linux
--- 

<br>

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  build the sample project</span>

<a id="Introduction"></a>
## Introduction

This project uses CMake (the CMakeLists.txt file) to configuring the build process for both Windows and Linux while using the same project source location, the WSL will use the mount to compile and build the Linux version on the Windows disk.

<a id="Build for Windows"></a>

## Build Sample project for Windows

This section describes the method to build the sample template project under Windows.

### Get the Visual Studio Runtime variables

This stack supports ***Visual Studio 2022*** and ***Visual Studio 2026***. We need a reference to the batch file to add to our build system. Depending on which batch file is chosen, the system will build under VS-2022 or VS-2026. The procedure below will discover the version(s) you have installed and ensure that the environment variables are added to the CMake system:
- To find the location of this batch file, you can use the following PowerShell command:
  <pre class="nje-cmd-multi-line-sm">
     & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" `
    -products * `
    -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
    -find **\VC\Auxiliary\Build\vcvars64.bat
  </pre>
- Add the path to ***vcvars64.bat***  to the file: ***${PROJECT_SOURCE_DIR}/cmake/CMakeLists_Init-env.bat***

### Build using Visual Studio (any edition)

This section describes building with **Visual Studio 2022/2026** (including the Community Edition) It configures the build environment for Microsoft’s own make utility: ***NMake*** and uses the ***CMakePresets.json*** to read the configuration.

1. In a Power-Shell CLI open the root folder of the project.
1. In the root folder execute theses commands once:
   - <pre class="nje-cmd-one-line-sm-indent1">cmd /c "call cmake\CMakeLists_Init-env.bat nul && cmake --preset=windows-nmake-debug"</pre>
   - <pre class="nje-cmd-one-line-sm-indent1">cmd /c "call cmake\CMakeLists_Init-env.bat nul && cmake --preset=windows-nmake-release"</pre>

  <div class="nje-expect-multi-lines-indent2">
  This will create the dedicated output folders:
  - build-win-vs\debug
  - build-win-vs\release
  - **Warning:** Make sure to copy the ***glfw3.dll*** to these folder ( using none static library)
  </div>
  <div class="nje-br2"> </div>

3\. Open **VS 2022** or **VS 2026**. And use the command  **File ➜ Open ➜ Folder**  option to open the project root folder (this creates a **.vs** folder in the root)  
4\. At the top of Visual Studio, locate the Startup Item drop-down near the “Start” (▶️) button  
5\. Select **glfw_sample_[].exe** this will set it as startup projects  
6\. In the build combo-box you should have the options: <br>
    &nbsp; &nbsp;***- PRJ-build(Debug)***  
    &nbsp; &nbsp;***- PRJ-build(Release)***  
7\. Use the normal Visual Studio method to debug and run the program  
8\. The output from Visual Studio can be found in the sub folder: **./build-win-vs**

---

### Build using Terminal (NMake)

1. Open the root folder in a Power-Shell terminal
1. Run the command: <span class="nje-cmd-inline-sm">./build.ps1 </span>
1. Note: you can switch the Debug and release build in the ***./build.ps1*** script at the top
1. The output from Visual Studio can be found in the sub folder: **./build-win**

<div class="nje-expect-multi-lines-indent1">

**The `build.ps1` script will:**  

- Setup the Visual Studio build environment variables.
- Run the CMake command to configure the **makefile** for NMake: <span class="nje-cmd-inline-sm">sh  cmake .. -G "NMake Makefiles"</span>
- Runs the **NMake** command to build the project based on the above generated makefile.

</div>

---

### Build using Visual Studio Code

To Build/develop in Visual Studio Code:

- Open the root folder of the project in Visual Studio Code
- Then use: **Terminal** -> **Run Build Tasks...** and choose ***Build Windows App***. This will use the same script as described in the "Using Terminal (NMake)" section
- The output can be found in the sub folder: **./build-win**
- You may need to adjust the **./.vscode/launch.json** file to ensure it points to the correct executable

---
<div class="nje-br1"> </div>

<a id="Build for Linux"></a>

## Build for Linux (NEEDS check, Next)

This section describes building the program using the GNU Make tool. It assumes that the source code is located under a Windows mount point (typically /mnt/c or /mnt/d). While this approach is slower for Linux compilation (2 to 5 times), it works fine for small projects. For large projects, you may consider syncing the mounted folder to the Linux filesystem first.

- From the project folder (`/mnt/d/myproject`) execute:
  - `./build.sh`

**That's all!** You can also use Visual Studio Code and build it as described above in the ***Visual Studio Code*** section.

<div class="nje-br2"> </div>

<sub><i> This file is part of: GLFW-Skia C++ Template Stack Copyright (c) 2025 Nico Jan Eelhart. This source code is licensed under the MIT License found in the 'LICENSE.md' file in the root directory of this source tree.</i>
</sub>

<p align="center">─── ✦ ───</p>
