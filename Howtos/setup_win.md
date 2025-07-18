---
layout: default_c

RefPages:
- setup_linux
- setup_win
- building_project
--- 

<br>

# 1 Windows Setup Instruction

## 2.1 Requirements for Windows

&nbsp;&nbsp; 📚  Visual Studio 2022 Community Edition (optional)  
&nbsp;&nbsp; 📚  Visual Studio code (optional)  
&nbsp;&nbsp; 📚  Python 3  
&nbsp;&nbsp; 📚  PowerShell  

<br>

## 2.2  Built GLFW library (Windows):

GLFW Version 3.4 has a CMake file that generates Visual Studio projects, which can be built using **Visual Studio 2022 Community Edition** (VS2022) and the msbuild tool.

- In your project folder create, if needed, a folder `dependencies\win\` and change to this folder. 
- In that folder, follow this link [from here](https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip) to download GLFW
-  Unzip the glfw-3.4.zip file. When extracting, make sure you select the option to extract the contents directly into glfw-3.4 (not into a subfolder like glfw-3.4\glfw-3.4). If your extraction tool creates a nested folder, manually move all files and folders from the inner glfw-3.4 up to glfw-3.4 and delete the extra subfolder.
  - Use a reliable extraction tool that does not skip hidden or system files.


### 2.2.1. dynamically(DLL) multithreaded libraries (preferred)
To Create the DLL **release\debug** use:


- `mkdir  'project root\dependencies\win\glfw-3.4\outdll` if not yet available:
- Change directory `'project root\dependencies\win\glfw-3.4\outdll`
- Run:  
`cmake .. -G "Visual Studio 17 2022" -A x64 -DBUILD_SHARED_LIBS=ON`  
- Than Run:  
`msbuild GLFW.sln /p:Configuration=Debug /p:Platform=x64`
- Copy the generated `glfw3.dll` file to the project root

> This ensures **VS2022** builds the **Debug multithreaded DLL** version in the ***./outdll/src/Debug*** folder, 
> or the **Release multithreaded DLL** version in the ***./outdll/src/Release*** folder, depending on the selected
> **Solution Configuration** in Visual Studio. You can then copy the ***glfw3.dll*** file to your application executable folder to use it.

### 2.2.2 statical library use:  

- `mkdir  'project root\dependencies\win\glfw-3.4\outstatic` if not yet available:
- Change directory `'project root\dependencies\win\glfw-3.4\outstatic`
- Run:  
`cmake .. -G "Visual Studio 17 2022" -A x64 -DBUILD_SHARED_LIBS=OFF`
- Than run:  
`msbuild GLFW.sln /p:Configuration=Debug /p:Platform=x64`

> This ensures **VS2022** builds the **Debug static multithreaded** version in the ***./outstatic/src/Debug*** folder,
> or the **Release static multithreaded** version in the ***./outstatic/src/Release*** folder, again depending on the
> **Solution Configuration**. The filename is:  ***glfw3.lib*** and will be linked into your application when you link against it

### 2.2.3 Update CMake files

After building the GLFW library (as DLL or static) Update the `cmake/windows.cmake`, <small>function: ***n_SetExtraWindowsFolders()***</small>
- Check/Set the include folder:`${PROJECT_SOURCE_DIR}/dependencies/win/glfw-3.4/include` <small>(GLFW_WIN_INCLUDE_DIR)</small>  

- ***Static linking***
  - Make sure the path to the **library folder** (file with .lib) is added to: `${PROJECT_SOURCE_DIR}/dependencies/win/glfw-3.4/outstatic/src/debug` <small>(GLFW_WIN_LIB_DIR)</small>
  - Make sure the variable **GLFW_LIBS_WIN_LOCAL** contains **glfw3*** the **name of the .lib file** (glfw3.lib) in the library folder
- ***Dynamic linking***
  - Make sure the path to the **library folder** (file with .lib) is added to `${PROJECT_SOURCE_DIR}/dependencies/win/glfw-3.4/outdll/src/debug` <small>(GLFW_WIN_LIB_DIR)</small>
  - Make sure the variable **GLFW_LIBS_WIN_LOCAL** contains **glfw3dll** the name of the import library file (glfw3dll.lib) in the library folder
  - Make sure the `.dll` file is available in your application’s runtime folder.

<br>

## 2.3 Built Skia library

1. First Build the ***depot_tools***. depot_tools is a collection of scripts/tools used to manage large Google Git projects 
  - In your project folder Navigate  to the folder: `.\dependencies\win` or create it, if it does not exists, 
  - Clone the git repository:  `git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git`
>\- This creates a folder: **.\dependencies\win\depot_tools** add this to the **system path** and reopen the **CLI**  
>\- Test. Execute: `gclient help` → should display help information.

### 2.3.1 Built dependency Ninja

- **Download** it form [here](https://github.com/ninja-build/ninja/releases/latest) 
- **Extract** and add the folder with ninja.exe to your system **PATH**

> ⚠️ **Ensure this path is defined before depot_tools in your PATH!  
> depot_tools includes a `ninja.bat` file that will break builds if used accidentally. <br> This maya also result into vague build issues**{: style="color: black;font-size:12px; "} 


- **Test**. Open a **CLI** and type: `ninja --version`

> 🤢**Error?**  
`python not found` using: `ninja --version` <br>
Because of course... Windows tries to run a fake python.exe from the Microsoft Store, instead of your real Python install.  
>
>> ✅ **Fix**  
>> Rename the python.exe and python3.exe files in the following folder to .bak or something similar
>> `explorer "$env:LOCALAPPDATA\Microsoft\WindowsApps"`
>
>> ⚠️ **Bonus round (when you're extra unlucky — and you probably are): The file will be in use. Because why wouldn't it be?
>> Open a Power-shell in administrator mode and delete or rename the files. <br>**{: style="color: black;font-size:12px; "}  

<br>


### 2.3.2 Build Skia Debug

- When you have build Skia before (especially if done in an , old,project folder: `./dependencies/win`), check and remove the old **System environment variables and paths**, old can impact the a new installation. Remove These:  

  - Environment variable: **EMSDK**
  - Environment variable: **EMSDK_NODE**
  - Environment variable: **EMSDK_PYTHON**
  - Environment variable: **JAVA_HOME** *only when points to a Skai subfolder*
  - Environment Path: **Remove** the old paths to the Skia subfolders (usual at the top)  
   <small>📌**Tip** Use the following Powershell command to check the value of the variables:  `Get-ChildItem Env:EMSDK*` </small> 
   <small>⚠️**warning** failing to do so may lead to nasty Skia build issues </small>
- In your project folder navigate to: `.\dependencies\win:`
- Clone **Skia**:  `git clone  --recursive https://skia.googlesource.com/skia.git`   
     - Change to location skia
     - `git checkout chrome/m126`  # To checkout a stable build instead a the master branch (Use same as on Linux!)       
- The following command will call a the Skia build script which uses depot_tools to **get** the **dependencies**:  `python tools\git-sync-deps` 
  - ***Test***: It should have created tools like `gn` and other dependencies, test type in the CLI:  
   `.\bin\gn --version`
  
>⚠️ **Warning**  
> Check for errors like:
> *`file name too long...`*
>
>If you see this, your Skia build will fail. This is one of the most common causes (together with 2.3.1) of strange or hard-to-diagnose build errors on Windows, especially with Skia or other large C++ projects.  
>
>>✅ **Solution**:  
>> You must shorten the folder path. Try the following:  
>>`C:\libs\skia`  
>
>📌 <small>Many developers abandon deeply nested folder structures altogether for Skia and similar projects due to this issue.</small>


- **Generate build** files with GN (uses *Ninja*)  
  1\. **Automatic generate build files (preferred)**  
    - Execute in powershell: 
    ```
  @"
  is_debug = true
  is_official_build = false
  skia_use_gl = true
  target_cpu = "x64"
  skia_enable_fontmgr_empty = false
  skia_use_angle = false
  skia_use_icu = true
  extra_cflags = ["/MDd", "/D_ITERATOR_DEBUG_LEVEL=2", "/GR"]
  "@ | Out-File out\Debug\args.gn -Encoding ASCII
  ```
- Than execute in the PowerShell CLI: ``.\bin\gn gen out\Debug``

  2\. **Manual generate build files**  
  This give you the ption to change arguments in a file that will be opened automatically
  - Execute:  `.\bin\gn args out\Debug`
  - Paste the following into the **editor** that opens:

  > *Editor opens past in this, and save & close the editor and **`gn`** will **continue** :*  
  > <small>📌 Tip: use this command to display the valid options: `gn args --list out/Debug` </small>
  >

  >``` text
  >is_debug = true
  >is_official_build = false
  >skia_use_gl = true
  >target_cpu = "x64"    
  >skia_enable_fontmgr_empty = false      # Optional: enable full font manager
  >skia_use_angle = false                 # Optional: disable ANGLE if using native OpenGL
  >skia_use_icu = true                    # ICU required for Unicode support
  >
  >extra_cflags = [ "/MDd", "/D_ITERATOR_DEBUG_LEVEL=2", "/GR" ]             # Dynamic
  > #extra_cflags = [ "/MTd", "/D_ITERATOR_DEBUG_LEVEL=2" ]            # Static
  > #extra_ldflags = [ "/NODEFAULTLIB:LIBCMT", "/DEFAULTLIB:LIBCMTD" ] #
  >
  > # DON't add these deprecated\removed options they may cause build errrors
  > # skia_enable_gpu = true               # IS Build ERROR!
  >```

  


- ~~Activate the MS VC environment, **Check the path** (***command seems not needed?***):~~
 ~~`& "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat` `~~
- ***Build** it: `ninja -C out\Debug`

>``` text
>Result should include:
>- out\Debug\skia.lib         
>- out\Debug\libskia.a
>- out\Debug\obj\skia\*.obj        
>```

- Update the `./cmake/windows.cmake` file, make sure it contains:  
`set(SKIA_WIN_CORE_INCLUDE "${PROJECT_SOURCE_DIR}/dependencies/win/skia")`

> ⚠️ **<small>Don't add the `include` folder! This folder is part of the include directive of the Skia files </small> <br>**{: style="color: black;font-size:14px; "}  

- Update the `./cmake/windows.cmake` file, make sure it contains:  
`set(SKIA_WIN_LIBS "${PROJECT_SOURCE_DIR}/dependencies/win/skia/out/Debug")`
- Ensure `skia`is added to the  variable: SKIA_LIBS_LOCAL in `cmake/windows.cmake`

<br>

### 2.3.3 Build Skia Release

This will create the Skia release library

### 2.3.3.1 Install `libjpeg-turbo` 
  - Download [from here](https://github.com/libjpeg-turbo/libjpeg-turbo) and buildt in the `./dependencies/win` folder
  - `mkdir build` and `cd build`
  - Configure: `cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release`
  - Build: `cmake --build . --config Release`
  - Add the include and library folders manually to the Skia release build config below.

### 2.3.3.2 Generate build files for Skia Release
- Navigate to: `./dependencies/win/skia`
- Execute: `.\bin\gn args out\Release`

> *Editor opens past in this, and save & close the editor and **`gn`** will **continue** :*
>

>``` text  
>is_debug = false
>is_official_build = true
>skia_use_gl = true
># skia_use_vulkan = true       # Windows: Supported
># skia_use_d3d = false         # Windows: Experimental support
># skia_use_metal = false       # NOT for Windows. Mac Only
>target_cpu = "x64"
>skia_use_system_zlib = false
>skia_use_system_harfbuzz = false
>skia_use_system_libpng = false
>skia_use_system_libwebp = false
>skia_use_expat = false
>skia_use_icu = false  # no international text layout, no BiDi!
>extra_cflags = [
>"/ID:/CPP/Projects/OPEN_SOURCE/control/dependencies/win/libjpeg-turbo/src",  # Check this path!  relative MAY produce headache!
>"/ID:/CPP/Projects/OPEN_SOURCE/control/dependencies/win/libjpeg-turbo/build" # Check this path!  relative MAY produce headache!
>]
> ```

- Build it: `ninja -C out\Release`

>``` text
> Result should be the `skia.lib` file among others
>```


### 2.4 ⚠️ Common Pitfalls (Windows)
Setup your build environment in Windows is by definition more error sensitive then setting it up in Linux. Here a a few tips to help you avoid (build) issues:
- 🚫 Avoid **spaces or special characters** in project paths  
- 🚫Make sure the official `ninja.exe` is **first in PATH environment variable**, not `depot_tools\ninja.bat`. failing to do so will generate builds errors during build of Skia
- 🚫Make sure Skia is not to deep nested, to avoid errors related to long path names, building Skia
- 🚫 Avoid **spaces or special characters** in project paths:  
- ✅ Use full paths in `gn.exe` **avoid** relative path
- 🔄 Always **reopen the terminal** after changing the environment


**Use the the build documentation to build the [sample project](building_project)**