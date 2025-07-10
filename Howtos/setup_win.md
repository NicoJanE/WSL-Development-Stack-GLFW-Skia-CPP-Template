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

GLFW Version 3.4 has a CMake file that generates Visual Studio projects, which can be built using **Visual Studio 2022 Community Edition** (VS2022)

- In your project folder create a folder `dependencies\win\glfw` and change to this folder. In that folder, download the GLFW Source from [here](https://www.glfw.org/download.html) and build it with **one** of the following methods:

### 2.2.1. dynamically(DLL)  multithreaded libraries(release\debug) use:

- `mkdir  outdll`
- From within the above folder configure the VS2022 files:
`cmake .. -G "Visual Studio 17 2022" -A x64 -DBUILD_SHARED_LIBS=ON`  
- In VS 20022 open the **GLFW.sln** file and choose:**'Build' -> '0 ALL BUILD'**

> This ensures **VS2022** builds the **Debug multithreaded DLL** version in the ***./outdll/src/Debug*** folder, 
> or the **Release multithreaded DLL** version in the ***./outdll/src/Release*** folder, depending on the selected
> **Solution Configuration** in Visual Studio. You can then copy the ***glfw3.dll*** file to your application executable folder to use it.

### 2.1.2 statical library use:  

- `mkdir  outstatic`
- From within the above folder configure the VS2022 files:  
`cmake .. -G "Visual Studio 17 2022" -A x64 -DBUILD_SHARED_LIBS=OFF`
- In VS 20022 open the **GLFW.sln** file and choose:**'Build' -> '0 ALL BUILD'**

> This ensures **VS2022** builds the **Debug static multithreaded** version in the ***./outstatic/src/Debug*** folder,
> or the **Release static multithreaded** version in the ***./outstatic/src/Release*** folder, again depending on the
> **Solution Configuration**. The filename is:  ***glfw3.lib*** and will be linked into your application when you link against it

### 2.1.3 Update CMake files

After creating  DLL or static GLFW library

- Make sure the path to the **include** folder is added to `cmake/windows.cmake`.
- Also make sure the path to the **library** folder is added to `cmake/windows.cmake` (for static linking).When using the DLL, make sure the `.dll` file is available in your application’s runtime folder.

<br>

## 2.3 Built Skia library

1. First Build the ***depot_tools***. depot_tools is a collection of scripts/tools used to manage large Google Git projects 
  - In your project folder Navigate  to the folder: `.\dependencies\win` or create it, if it does not exists, 
  - Clone the git repository:  `git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git`
>\- This creates a folder: **.\dependencies\win\depot_tools** add this to the **system path** and reopen the **CLI**  
>\- Test. Execute: `gclient help` → should display help information.

### 2.3.1 Built dependency Ninja

- Download it form [here](https://github.com/ninja-build/ninja/releases/latest) 
- Extract and add the folder with ninja.exe to your system **PATH**

> ⚠️ **Ensure this path is defined before depot_tools in your PATH!  
> depot_tools includes a `ninja.bat` file that will break builds if used accidentally. <br>**{: style="color: black;font-size:12px; "} 


- **Test**. Open a **CLI** and type: `ninja --version`

> 🤢**Error?**: `python not found` using: `ninja --version` <br>
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

- In your project folder navigate to: `.\dependencies\win:`
- Clone **Skia**:  `git clone  --recursive https://skia.googlesource.com/skia.git`          
- Navigate to sub folder:`cd skia`
- The following command will call a the Skia build script which uses depot_tools to **get** the **dependencies**:  `python tools\git-sync-deps` 

> **Test**: It should have created tools like `gn` and other dependencies, test type in the CLI: `.\bin\gn --version`

- Generate build files with GN (uses *Ninja*) Execute:  `.\bin\gn args out\Debug`
- Paste the following into the editor that opens:

> *Editor opens past in this, and save & close the editor and **`gn`** will **continue** :*
>

>``` text
>is_debug = true
>is_official_build = false
>skia_use_gl = true
>target_cpu = "x64"    
>skia_enable_fontmgr_empty = false      # Optional: enable full font manager
>skia_enable_gpu = true                 # Needed for OpenGL
>skia_use_angle = false                 # Optional: disable ANGLE if using native OpenGL
>skia_use_icu = true                    # ICU required for Unicode support
>#extra_cflags = [ "/MTd", "/D_ITERATOR_DEBUG_LEVEL=2" ]   # static
>extra_cflags = [ "/MDd", "/D_ITERATOR_DEBUG_LEVEL=2" ]  # Dynamic
>#extra_ldflags = [ "/NODEFAULTLIB:LIBCMT", "/DEFAULTLIB:LIBCMTD" ]
>```

- Build it: `ninja -C out\Debug`

>``` text
>Result should include:
>- out\Debug\skia.lib         
>- out\Debug\libskia.a
>- out\Debug\obj\skia\*.obj        
>```

- Update the `./cmake/windows.cmake` file, make sure it contains:  
`set(SKIA_WIN_CORE_INCLUDE "${PROJECT_SOURCE_DIR}/dependencies/win/skia")`

> ⚠️ **<small>Don't add the include folder! `include` The include folder is added in Skia files, in the include directives!</small> <br>**{: style="color: black;font-size:14px; "}  

- Update the `./cmake/windows.cmake` file, make sure it contains:  
`set(SKIA_WIN_LIBS "${PROJECT_SOURCE_DIR}/dependencies/win/skia/out/Debug")`
- Ensure `skia`is added to the  variable: SKIA_LIBS_LOCAL in `cmake/windows.cmake` (see 1.3)

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

<br>

### 2.4 ⚠️ Common Pitfalls (Windows)

- ✅ Make sure the official `ninja.exe` is **first in PATH**, not `depot_tools\ninja.bat`.
- ✅ Use full paths in `gn.exe` 🚫 avoid relative path
- 🔄 Always **reopen the terminal** after changing the environment
- 🚫 Avoid **spaces or special characters** in project paths:  
 `C:\Users\John Doe\skia` → ❌ Bad idea
