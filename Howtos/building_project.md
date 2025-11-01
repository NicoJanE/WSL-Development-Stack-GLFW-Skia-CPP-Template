---
layout: default_c
RefPages:
- building_project
- setup_linux
- setup_win
--- 

<br>

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  Docker Container</span>

## 1. Building the project

This project uses CMake (the CMakeLists.txt file) to configuring the build process for both Windows and Linux while using the same project source location, the WSL will use the mount to compile and build the Linux version on the Windows disk

## 1.1 Build for Windows

Before building the project with on of the methods described below, **make sure:**

- That the path to `vcvars64.bat` is correctly set in `./cmake/CMakeLists_Init-env.bat`

### 1.1.1 Using Visual Studio 2022 (any edition)

This section describes building with **Visual Studio 2022** (including the Community Edition) It configures the build environment for Microsoft’s own make utility: **NMake** and uses the `CMakePresets.json` to read the configuration.

- in a CLI Open the root folder of the project.
- In the root folder execute theses commands once:
  - `cmake --preset=windows-nmake-debug`
  - `cmake --preset=windows-nmake-release`    
*Results: This will create the dedicated output folders:*
     - build-win-vs\debug 
     - build-win-vs\release
     - **Make sure** to copy the ***glfw3.dll*** to these folder when not using a static library but a DLL!


- Open VS 2022. And use the command  **File ➜ Open ➜ Folder**  option to open the project folder (create a **.vs** folder in the root)
- At the top of Visual Studio, locate the Startup Item drop-down near the “Start” (▶️) button 
  - Select **glfw_sample_[].exe** this will set it as startup projects
- In the build combo-box you should have the options
  - PRJ-build(Debug)
  - PRJ-build(Release)
- Use the normal Visual Studio method to debug and run the program
- The output from Visual Studio can be found in the sub folder: **./build-win-vs**

### 1.1.2 Using Terminal (NMake)

- Open the root folder in a Power-Shell terminal
- Run the command: `./build.ps1`
- Note: you can switch the Debug and release build in the `./build.ps1` script at the top
- The output from Visual Studio can be found in the sub folder: **./build-win**

>**The `build.ps1` script will:**  
>\- Setup the Visual Studio build environment variables.  
>\- Run the CMake command to configure the **makefile** for NMake: `sh  cmake .. -G "NMake Makefiles"`  
>\- Runs the `NMake` command to build the project based on the above generated makefile

### 1.1.3 Visual Studio Code

- Open the root folder of the project  In Visual Studio Code
- Than use the: Terminal -> Build Windows App.
This will actuall use the same script as used in 3.1.2 "Using Terminal (NMake)"
- The output from Visual Studio can be found in the sub folder: **./build-win**
- You may need to adjust the ./vscode/launch.json file to make sure it points to the correct executable

<br>

## 1.2 Build for Linux

This section describes the building of the program using the GNU Make tool, it assumes that the source on is located under the Windows mount point (usual /mnt/c or something) While this is for Linux complications slower(2 to 5 times) this is fine for small projects. For large projects you may consider to sync the mounted folder to the Linux filesystem first

- From the project folder (`/mnt/d/myproject`) execute:
  - `./build.sh`
  
And Of course you can use the VSC and build it with Visual Studio code as described above in ***section '1.1.3'***