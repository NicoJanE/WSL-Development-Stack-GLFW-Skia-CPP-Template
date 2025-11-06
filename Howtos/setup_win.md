---
layout: default_c

RefPages:
- setup_linux
- setup_win
- VSC-AgentMode_win
- building_project
--- 

<br>

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  Windows Setup Instruction</span>

## Introduction

This template is intended for use in conjunction with a **WSL** (Windows Subsystem for Linux) distribution running on a **Windows 11** host.
This section explains how to configure a Windows environment to build your GLFW/Skia project for Windows

###  Requirements for Windows

&nbsp;&nbsp; 📚  Visual Studio 2022 Community Edition (optional)  
&nbsp;&nbsp; 📚  Visual Studio code (optional)  
&nbsp;&nbsp; 📚  Python 3  
&nbsp;&nbsp; 📚  PowerShell  

---

## Setup Instructions

### Cross-Platform Development Setup

**This is the Windows component** of a dual-platform development environment:

- **Windows Setup (This Page)**: Native development tools, Visual Studio, debugging
- **WSL Linux Setup**: Cross-platform builds and Linux testing → [Linux Setup Guide](setup_linux)

**Why both?** You'll develop primarily on Windows but can build and test Linux versions seamlessly through WSL.

**💫 New Setup wit VSC Agent [See here](VSC-AgentMode_win)**
This will try to use the VS Co-pilot agent to install the installation, mentioned below (Experimental)

---

### Built GLFW library for Windows

GLFW Version 3.4 has a CMake file that generates Visual Studio projects, which can be built using **Visual Studio 2022 Community Edition** (VS2022) and the MSbuild tools.

- Activate a Power-shell in the project folder
- In your project folder create, if needed, a folder and change to it: <span class="nje-cmd-inline-sm">.\dependencies\win </span>  
- Download [**glfw-3.4.zip**](https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip) it in the above folder (result is: **.\dependencies\win\glfw-3.4.zip**)
- For the next step use a reliable extraction tool that does not skip hidden or system files and extracts the zip file in the right location, after extracting the files  should be in the folder: **.\dependencies\win\glfw-3.4\\**. I use the 7z zip utility from [here](https://www.7-zip.org/download.htm) when using the following command in a Powershell CLI (in the mentioned folder), the zip should be extract in the right location, execute the command:  <span class="nje-cmd-inline-sm"> 7z x glfw-3.4.zip "-o."</span>

#### Create a dynamically(DLL) multithreaded glfw library (preferred)

To Create the DLL **release\debug** use:

- If not yet available make the **outdll** directory
  <pre class="nje-cmd-one-line-sm-indent1">mkdir project root\dependencies\win\glfw-3.4\outdll </pre>
- Change to that directory
  <pre class="nje-cmd-one-line-sm-indent1">project root\dependencies\win\glfw-3.4\outdll</pre>
- Than Run:  
   <pre class="nje-cmd-one-line-sm-indent1">cmake .. -G "Visual Studio 17 2022" -A x64 -DBUILD_SHARED_LIBS=ON </pre>
- Next,  use PowerShell to search for **msbuild.exe** on the system, this is because we need the full path to msbuild.exe. Us this Power-shell command:
  <pre class="nje-cmd-one-line-sm-indent1">Get-ChildItem -Path "C:\" -Filter "msbuild.exe" -Recurse -ErrorAction SilentlyContinue </pre>

- Now use the Full path to msbuild.exe to create the library, In the Power-Shell CLI run:
  <pre class="nje-cmd-one-line-sm-indent1">& /path/to/msbuild GLFW.sln /p:Configuration=Debug /p:Platform=x64 </pre>
- then copy the generated **glfw3.dll** file to the project root.

<div class="nje-expect-multi-lines-indent1">
This ensures **VS2022** builds the **Debug multithreaded DLL** version in the ***./outdll/src/Debug*** folder, 
or the **Release multithreaded DLL** version in the ***./outdll/src/Release*** folder, depending on the selected
**Solution Configuration** in Visual Studio. You can then copy the ***glfw3.dll*** file to your application executable folder to use it.
</div>
<div class="nje-br1"> </div>

### Statical library use

- If not yet available make the **outdll** directory
  <pre class="nje-cmd-one-line-sm-indent1">mkdir  'project root\dependencies\win\glfw-3.4\outstatic </pre>
- Change to that directory 
  <pre class="nje-cmd-one-line-sm-indent1">project root\dependencies\win\glfw-3.4\outstatic</pre>
- Than Run:  
   <pre class="nje-cmd-one-line-sm-indent1">cmake .. -G "Visual Studio 17 2022" -A x64 -DBUILD_SHARED_LIBS=OFF </pre>
- Next,  use PowerShell to search for **msbuild.exe** on the system, this is because we need the full path to msbuild.exe. Us this Power-shell command:
  <pre class="nje-cmd-one-line-sm-indent1">Get-ChildItem -Path "C:\" -Filter "msbuild.exe" -Recurse -ErrorAction SilentlyContinue </pre>
- Now use the Full path to msbuild.exe to create the library, In the Power-Shell CLI run:
  <pre class="nje-cmd-one-line-sm-indent1">& /path/to/msbuild GLFW.sln /p:Configuration=Debug /p:Platform=x64 </pre>
- then copy the generated **glfw3.dll** file to the project root.

<div class="nje-expect-multi-lines-indent1">
This ensures **VS2022** builds the **Debug static multithreaded** version in the ***./outstatic/src/Debug*** folder,
or the **Release static multithreaded** version in the ***./outstatic/src/Release*** folder, again depending on the
**Solution Configuration**. The filename is:  ***glfw3.lib*** and will be linked into your application when you link against it
</div>
<div class="nje-br1"> </div>

### Update CMake files

After building the GLFW library (as DLL or static) Update the  <span class="nje-cmd-inline-sm">cmake/windows.cmake file</span>, <small>function: ***n_SetExtraWindowsFolders()***</small>

- Check/Set the include folder variable **GLFW_WIN_INCLUDE_DIR** to: 
  <pre class="nje-cmd-one-line-sm-indent1">${PROJECT_SOURCE_DIR}/dependencies/win/glfw-3.4/include</pre>
- In case of:
  - ***Static linking***
    - Make sure the path to the library folder **GLFW_WIN_LIB_DIR** is set to: 
      <pre class="nje-cmd-one-line-sm-indent1">${PROJECT_SOURCE_DIR}/dependencies/win/glfw-3.4/outstatic/src/debug </pre>
    - Make sure the variable **GLFW_LIBS_WIN_LOCAL** contains **glfw3** the **name of the .lib file** (glfw3.lib)
  - ***Dynamic linking***
    - Make sure the path to the library folder:**GLFW_WIN_LIB_DIR** is set to 
      <pre class="nje-cmd-one-line-sm-indent1">${PROJECT_SOURCE_DIR}/dependencies/win/glfw-3.4/outdll/src/debug</pre>
    - Make sure the variable **GLFW_LIBS_WIN_LOCAL** contains **glfw3dll** the name of the import library file (glfw3dll.lib)
    - Make also sure the `.dll` file is available in your application’s runtime folder.

<div class="nje-br1"> </div>

## Built Skia library

1. First Build the ***depot_tools***. depot_tools is a collection of scripts/tools used to manage large Google Git projects
   - In your project folder Navigate to the folder: **.\dependencies\win** or create it, if it does not exists
   - Clone the git repository:  
     <pre class="nje-cmd-one-line-sm-indent1">git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git </pre>

<div class="nje-expect-multi-lines-indent3">
- This creates a folder: **.\dependencies\win\depot_tools** add this to the **system path** and reopen the **CLI**  
- Test. Execute: <span class="nje-cmd-inline-sm">gclient help</span> → should display help information.
</div>
<div class="nje-br1"> </div>

### Built dependency Ninja if needed

- Execute <span class="nje-cmd-inline-sm">ninja --version</span> When this returns a version Ninja is already build and you skip this and continue with the next section ***Build Skia Debug*** below.
- If ninja is not installed **Download** it form [**here**](https://github.com/ninja-build/ninja/releases/latest)
- **Extract** it in the project root under the subfolder: **.\dependencies\win**
- Make sure to add the installed folder with <span class="nje-cmd-inline-sm">ninja.exe</span> to your system **PATH** so that **ninja.exe** is available in your terminal

<details class="nje-warn-box">
  <summary>Path **ninja** must be before depot_tools
  </summary>
 **Ensure that the ninja path is defined before depot_tools in your PATH!**{: style="color: red;font-size:12px; "}  
 depot_tools includes a **ninja.bat** file that will break builds if used accidentally, this maya also result into vague build issues.
</details>
<div class="nje-br2"> </div>

- **Test**. Open a **CLI** and execute: 
  <pre class="nje-cmd-one-line-sm-indent1">ninja --version</pre>

<details class="nje-error-box">
  <summary>Received an error?
  </summary>
  When this command:<span class="nje-cmd-inline-sm">ninja --version</span> returns: ***python not found***  
  This is because Windows is trying to run a fake python.exe from the Microsoft Store, instead of your real Python install!  
  
 ✅ **Fix**  
 Rename the python.exe and python3.exe files in the following folder to .bak or something similar.
 <span class="nje-cmd-inline-sm">  explorer "$env:LOCALAPPDATA\Microsoft\WindowsApps" </span>

 ⚠️ **Bonus round**{: style="color: black;font-size:12px; "}(when you're extra unlucky — and you probably are): The file will be in use. Because why wouldn't it be?
 Open a Power-shell in administrator mode and delete or rename the files.
</details>
 <div class="nje-br1"> </div>

### Build Skia Debug

- **Check this**: When you have build Skia before, especially if done in an previous project folder (i.e: **./other project/dependencies/win**), check and remove the old **System environment variables and paths**, old system variables can impact the a new installation, so remove these:  

  - Environment variable: **EMSDK**
  - Environment variable: **EMSDK_NODE**
  - Environment variable: **EMSDK_PYTHON**
  - Environment variable: **JAVA_HOME** *only when points to a Skai subfolder*
  - Environment Path: **Remove** the old paths to the Skia subfolders (usual at the top)  
  <span class="nje-br"> </span>
   <small>📌**Tip** Use the following Powershell command to check the value of the variables: <span class="nje-cmd-inline-sm">Get-ChildItem Env:EMSDK*</span> </small>  
   <small>⚠️**warning** failing to do so may lead to nasty Skia build issues </small>

- In your project folder navigate to: <span class="nje-cmd-inline-sm">.\dependencies\win</span>
- Clone **Skia** Execute command:  
  <pre class="nje-cmd-one-line-sm-indent1">git clone  --recursive https://skia.googlesource.com/skia.git </pre>
- Change **cd** to
  <pre class="nje-cmd-one-line-sm-indent1">project root\dependencies\win\skia</pre>
- Execute command:
  <pre class="nje-cmd-one-line-sm-indent1">git checkout chrome/m126`  # To checkout a stable build instead a the master branch (Use same as on Linux!) </pre>
- The following command will call a the Skia build script which uses depot_tools to **get** the **dependencies**:  
- Execute command: 
  <pre class="nje-cmd-one-line-sm-indent1">python tools\git-sync-deps </pre>
  - ***Test***: It should have created tools like <span class="nje-cmd-inline-sm">gn</span> and other dependencies, test type in the CLI:  
  Execute command: <span class="nje-cmd-inline-sm">.\bin\gn --version </span>
  
<details class="nje-warn-box">
  <summary>Check for errors
  </summary>
 Check for errors like:
 *<span class="nje-cmd-inline-sm">file name too long...</span>*

If you see this, your Skia build will fail. This is one of the most common causes (together the previous warning box) of strange or hard-to-diagnose build errors on Windows, especially with Skia or other large C++ projects.  

✅ **Solution**:  
 You must shorten the folder path. Try the following:  
`C:\libs\skia`  

📌 Many developers abandon deeply nested folder structures altogether for Skia and similar projects due to this issue.
</details>
<div class="nje-br2"> </div>

- Make sure to be in the folder:
  <pre class="nje-cmd-one-line-sm-indent1">project root\dependencies\win\skia</pre>
- create folder: 
  <pre class="nje-cmd-one-line-sm-indent1">mkdir out\Debug </pre>
- In the next steps  we are going to **Generate build** files with GN (uses *Ninja*)  
- Execute this command in powershell CLI:

<pre class="nje-cmd-multi-line-sm-indent4">@"
is_debug = true
is_official_build = false
skia_use_gl = true
target_cpu = "x64"
skia_enable_fontmgr_empty = false
skia_use_angle = false
skia_use_icu = true
extra_cflags = ["/MDd", "/D_ITERATOR_DEBUG_LEVEL=2", "/GR"]
"@ | Out-File out\Debug\args.gn -Encoding ASCII
</pre>

- Execute in PowerShell CLI: 
  <pre class="nje-cmd-one-line-sm-indent1">.\bin\gn gen out\Debug</pre>
  <span class="nje-expect" style="margin-top:0px;"> This configures the debug build!</span>

<details class="nje-back-box">
  <summary>Alternative Manual generate build files
  </summary>
 <!-- copilot-ignore-start -->
  This give you the option to change arguments in a file that will be opened automatically, use this if you want to configure Skia manual
  - Make sure to be in the folder: `project root\dependencies\win\skia`
  - Execute:  `.\bin\gn args out\Debug`
  - Paste the following into the **editor** that opens:

   *Editor opens past in this, and save & close the editor and **`gn`** will **continue** :*  
   <small>📌 Tip: use this command to display the valid options: <span class="nje-cmd-inline-sm">gn args --list out/Debug</pre> </small>
  
  <pre class="nje-cmd-multi-line-sm-indent4">
  is_debug = true
  is_official_build = false
  skia_use_gl = true
  target_cpu = "x64"    
  skia_enable_fontmgr_empty = false      # Optional: enable full font manager
  skia_use_angle = false                 # Optional: disable ANGLE if using native OpenGL
  skia_use_icu = true                    # ICU required for Unicode support
  
  extra_cflags = [ "/MDd", "/D_ITERATOR_DEBUG_LEVEL=2", "/GR" ]             # Dynamic
   #extra_cflags = [ "/MTd", "/D_ITERATOR_DEBUG_LEVEL=2" ]            # Static
   #extra_ldflags = [ "/NODEFAULTLIB:LIBCMT", "/DEFAULTLIB:LIBCMTD" ] #
  
   /# DON't add these deprecated\removed options they may cause build errrors
   /# skia_enable_gpu = true               # IS Build ERROR!
  </pre>
  <!-- copilot-ignore-end -->
<p align="center" style="padding:20px;">─── ✦ ───</p>
</details>
 <span class="nje-br"> </span>

- ~~Activate the MS VC environmen,  **Not needed**  to call 'vcvars64.bat' **gn** can handled it self~~
- **Build** it: 
  <pre class="nje-cmd-one-line-sm-indent1">ninja -C out\Debug</pre>

<div class="nje-expect-multi-lines-indent2">
Build result should include files like:
- out\Debug\skia.lib
- out\Debug\libskia.a
- out\Debug\obj\skia\*.obj
</div>
<span class="nje-br"> </span>

- Update the file **./cmake/windows.cmake** file, make sure it contains:
  <pre class="nje-cmd-one-line-sm-indent1">set(SKIA_WIN_CORE_INCLUDE "${PROJECT_SOURCE_DIR}/dependencies/win/skia")</pre>
 ⚠️ **<small>Don't add the `include` folder! This folder is part of the include directive of the Skia files </small> <br>**{: style="color: black;font-size:14px; "}  

- Update the file  **./cmake/windows.cmake** file, make sure it contains:
  <pre class="nje-cmd-one-line-sm-indent1">set(SKIA_WIN_LIBS "${PROJECT_SOURCE_DIR}/dependencies/win/skia/out/Debug"),</pre>
- Ensure `skia`is added to the  variable: **SKIA_LIBS_LOCAL** in the file **cmake/windows.cmake**
<span class="nje-br"> </span>

### Build Skia Release

This will create the Skia release library

### Install ***libjpeg-turbo***

- Navigate to: **./dependencies/win** of the project root folder.
- Download libjpeg-turbo [**from here**](https://github.com/libjpeg-turbo/libjpeg-turbo)
- Create build directory
  <span class="nje-cmd-inline-sm">mkdir build</span>
- Change to the build output folder and(**cd build**)
- Run 'configure':
  <pre class="nje-cmd-one-line-sm-indent1"> cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release </pre>
- Build it: 
  <pre class="nje-cmd-one-line-sm-indent1"> cmake --build . --config Release </pre>
- Add the include and library folders manually to the Skia release build config below.
- Make sure you return to the subfolder **./dependencies/win/skia** of the **project root** folder!

### Generate build files for Skia Release

- Navigate to: **./dependencies/win/skia** of the project root folder.
- create folder: <span class="nje-cmd-inline-sm">mkdir build</span>
- Execute this command: in powershell CLI: 
<pre class="nje-cmd-multi-line-sm-indent4">
@"
is_debug = false
is_official_build = true
skia_use_gl = true
target_cpu = "x64"
skia_use_system_zlib = false
skia_use_system_harfbuzz = false
skia_use_system_libpng = false
skia_use_system_libwebp = false
skia_use_expat = false
skia_use_icu = false  # no international text layout, no BiDi!
extra_cflags = [
"/I../../../libjpeg-turbo/src",  ""/I../../../libjpeg-turbo/build""
]
"@ | Out-File out\Release\args.gn -Encoding ASCII
</pre>

- Configures the build:
  <pre class="nje-cmd-one-line-sm-indent1">.\bin\gn gen out\Release</pre>
  <span class="nje-expect" style="margin-top:0px;"> This configures the Release build!</span>

- Make sure to be in the folder: **project root\dependencies\win\skia**
- create the **Build** with:
  <pre class="nje-cmd-one-line-sm-indent1">`ninja -C out\Release</pre>
  <span class="nje-expect" style="margin-top:0px;"> This Creates the Release build!</span>

This finalizes the build process for Windows

## How to proceed

Nect you should be able to build the included template project for instructions see:
**The build project [documentation](building_project)**

<span class="nje-br"> </span>


<details>
<summary class="clickable-summary"> <span class="summary-icon"></span>
    <span style="color: #097df1ff; font-size: 26px;">Appendix I</span> <span style="color: #409EFF; font-size: 16px; font-style: italic;"> - Common Pitfalls </span>
</summary>

### ⚠️ Common Pitfalls (Windows)

Setup your build environment in Windows is by definition more error sensitive then setting it up in Linux. Here a a few tips to help you avoid (build) issues:

- 🚫 Avoid **spaces or special characters** in project paths  
- 🚫Make sure the official <span class="nje-cmd-inline-sm">ninja.exe</span> is **first in PATH environment variable**, not <span class="nje-cmd-inline-sm">depot_tools\ninja.bat</span> failing to do so will generate builds errors during build of Skia
- 🚫Make sure Skia is not to deep nested, to avoid errors related to long path names, building Skia
- 🚫 Avoid **spaces or special characters** in project paths:  
- ✅ Use full paths in `gn.exe` **avoid** relative path
- 🔄 Always **reopen the terminal** after changing the environment

</details>

<sub><i> This file is part of: GLFW-Skia C++ Template Stack Copyright (c) 2025 Nico Jan Eelhart. This source code is licensed under the MIT License found in the 'LICENSE.md' file in the root directory of this source tree.</i>
</sub>

<p align="center">─── ✦ ───</p>