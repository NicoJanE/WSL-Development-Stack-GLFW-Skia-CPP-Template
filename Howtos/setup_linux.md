---
layout: default_c

RefPages:
- setup_linux
- setup_win
- building_project
--- 


<br>

# 1 Linux Setup Instruction

## 1.1 Requirements

This template is intended for use with a **WSL** (Windows Subsystem for Linux) distribution running on a **Windows 11** host.
This section explains how to configure a Linux environment to build your GLFW/Skia project under WSL.


> *Note:*{: style="color: black;font-size:13px; "} <br>
> <small>Note that this Linux setup uses the same project source directory as the Windows setup. This allows you to build the application for both Linux and Windows using a shared codebase, with only minimal setup required for each platform. <br></small>



> 🛑**Setup Warning**  
> For convenience, I provide a Debian-based WSL distribution that includes the **MATE X11 desktop environment**.  This setup requires **XLaunch** (an X11 server) to be installed on the Windows host. Instructions are included in the WSL distribution itself. **To get started with the WSL environment, see** [this repository](https://github.com/NicoJanE/WSL-OS-With-GUI-Desktop). Please read future!  
>
>>  - <small> Launch the MATE desktop by: `./start-mate.sh` (user's root dir.).  </small>
>>  - <small> Login credentials: **user** = `nico`, **password** = `nico`  <small>
>
> **That may not work well enough!**  
> Some X11 servers only support very old versions of OpenGL, often limited to version 1.4. For example, **VcXsrv**, the X11 server used in the above WSL distribution, supports only OpenGL 1.4. **Due to this limitation**, it's recommended to use a default WSL installation with **WSLg**, which supports much more recent **OpenGL versions up to 4.6**.  
>
>> **Tip: Check OpenGL version**  
>> `glxinfo | grep "OpenGL version"`
>
>**Final Recommendation:**{: style="color: black;font-size:13px; "}  
> For best graphics support and compatibility, use a **default WSL Ubuntu installation with built-in WSLg support**. For Manual WSL installation instructions click link below.
>
<details closed>  
  <summary class="clickable-summary">
  <span  class="summary-icon"></span> 
   Manual install WSL
  </summary> 	<!-- On same line is failure, Don't indent the following Markdown lines!  -->

> 
> ### Manual Create WSL Environment
>
>This chapter explains how to set up a WSL backend environment manual by using the ***.Appx*** or ***.>AppxBundle*** packages
>
> #### 1. Download the WSL packages from [here](https://learn.microsoft.com/en-us/windows/wsl/install-manual).
>   - Scroll to the "Downloading distributions" section.
>   - Download the Ubuntu 24.04 `.AppxBundle` (this guide assumes this version).
>   - Unpack the package, like, assuming you downloaded `Ubuntu2404-240425.AppxBundle`:
>
> #### 2. Get the right **WSL Import** file
>   - Rename `Ubuntu2404-240425.AppxBundle` to `Ubuntu2404-240425.zip`
>   - Unpack it using 7zip or similar
>   - Find  `Ubuntu_2404.0.5.0_x64.appx` 
>      - Rename it to: `Ubuntu_2404.0.5.0_x64.zip` unpack it.
>      - Unpack it.  
> **Result** you'll get the file: `install.tar.gz` this is what you’ll use in the next step,
>
> #### 3. Create the WSL
>   -  Place the WSL file in centralized location, i.e. `/My-wsl-environments/wsl-sample/`
>   -  In that location execute:
>      - `wsl --import wsl-sample /My-wsl-environments/wsl-sample install.tar.gz`  
>      *(wsl --import [name wsl] [destination] [location-to/install.tar.gz] )*
>
>### Some  WSL commands:
>
><pre class="nje-cmd-multi-line">
>wsl -l -v              # List all distributions with status
>wsl [name] -d          # starts it
>wsl --unregister [name]# Remove a distribution
></pre>

</details>
 


In light of the above we assume that you will use **Debian-based** WSL-2 distribution. You can use `apt install` to install the required packages.

> Debian-based Linux distributions include:  
> &nbsp;&nbsp; *Ubuntu, Linux Mint, Kali Linux, Pop!_OS, Zorin OS, elementary OS, Parrot OS, and others.*

> *Remark:*{: style="color: black;font-size:13px; "} <br>
><small> The libraries (**depot_tools, GLFW, and Skia**) for Windows are installed inside the project folder: **\dependencies\win**  </small>
>
> <small>
> Under Linux, these packages are easier to install system-wide. Therefore, the Linux versions are installed **globally** where possible.
> For libraries that must be built **manually** (currently only depot_tools), they are installed in the **user's home folder** as part of the Linux development build. </small>

<br>

## 1.2. Install GLFW library

- Install the libraries with:
  - `sudo apt update`
  - `sudo apt install cmake g++ libglfw3-dev libgl1-mesa-dev libx11-dev gdb`
    - How to find the include folder: `dpkg -L libglfw3-dev | grep '\.h$'` 
    - How to find the Lib folder: `dpkg -L libglfw3-dev | grep '\.so'` 

  >*Remark*{: style="color: black;font-size:13px; "} <br>
  > <small> A more general method to look for a specific library is:  
  > `sudo find /usr/lib /usr/local/lib -name "libGL.so`  
  > (remember to drop the 'lib' and '.so' part when using the library in CMake\Make, just saying) <br></small>

  - Check\Update the `cmake/linux.cmake` file with the include folder an library folder of GLFW, see function: **SetLinuxDirectories**. 
  - Check also the `GLFW_LIBS_LOCAL` which specifies the use library name(s) use for GLFW (and for some general libraries used)

<br>

## 1.3 Install Skia library

- Install the libraries with:
  - `sudo apt update`
  - `sudo apt install build-essential git python3 pkg-config libglu1-mesa-dev libgl1-mesa-dev ninja-build libfontconfig1-dev libexpat1-dev libfreetype6-dev libpng-dev libjpeg-dev libharfbuzz-dev libwebp-dev`

### 1.3.1- Install the library **depot_tools**:

- Make a directory in for the user home directory(make sure user owns it) to install **depot_tools** into, for example: `/home/name/tools/libs` and **cd** to it
- clone: `git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git`
- Add the path to begin of the path environment (so it will have priority):  
  `echo 'export PATH="$HOME/tools/libs/depot_tools:$PATH"' >> ~/.bashrc`  
  `source ~/.bashrc`

### 1.3.2 Setup amd configure Skia

- Use the new created  home directory to install **Skia** into, thus make sure your in: `/home/name/tools/libs/`
- clone: `git clone https://skia.googlesource.com/skia.git`
- Navigate to: `cd skia`  
- Sync dependencies with:  `python3 tools/git-sync-deps` this will install tools like ***gn*** and others
  - check with: 
  `which gn      # should display location of gn`

### 1.3.3 Creating build versions

All combinations can be found here but obvious choice is the **Shared Debug**

- **Generate Static Release** build files with:  
`./bin/gn gen out/release/static --args='is_official_build=true is_component_build=false is_debug=false skia_use_gl=true' `
  - **Build it** with:  
    `ninja -C out/release/static`

- **Generate Static Debug** build files with:  
`./bin/gn gen out/debug/static --args='is_debug=true is_official_build=false is_component_build=false skia_use_gl=true' `
  - **Build it** with:  
    `ninja -C out/debug/static`

- **Generate Shared Release** build files with: 
`./bin/gn gen out/release/shared --args='is_debug=false is_official_build=true is_component_build=true skia_use_gl=true' `
  - **Build it** with:  
    `ninja -C out/release/shared`

- ✅**Generate Shared Debug** build files with:  
`./bin/gn gen out/debug/shared --args='is_debug=true is_official_build=false is_component_build=true skia_use_gl=true' `
  - **Build it** with:  
    `ninja -C out/debug/shared`

### 1.3.4 Check\Update ./cmake/linux.cmake file for Skia

For the Skia  include folder an library folder set the variables, see function: SetLinuxDirectories  
- For example set:  
  `set(SKIA_LINUX_CORE_INCLUDE_DIR "/name/tools/skia" CACHE PATH "SKIA include dir")`
  `set(SKIA_LINUX_LIBS_DIR "/name/tools/skia/out/debug/shared" CACHE PATH "SKIA Lib dir")`

- Check also the `SKIA_LIBS_LOCAL` which specifies the use library name(s)


**Use the the build documentation to build the [sample project](building_project)**