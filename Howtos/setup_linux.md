---
layout: default_c

RefPages:
- setup_linux
- setup_win
- building_project

TableCont:
- Introduction
- Setup Instructions
- Prepare the WSL
- Install the GLFW library
- Install the Skia library
- WSL Notes

--- 

<br>

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  Linux Setup Instruction</span>
![MIT License](https://img.shields.io/badge/License-MIT-green) ![Commercial Services Available](https://img.shields.io/badge/Services-Optional-blue)

<a id="Introduction"></a>

## Introduction

This template is designed for use in conjunction with a **WSL** (Windows Subsystem for Linux) distribution running on a **Windows 11** host.
This section provides step-by-step instructions for setting up the Linux build environment in WSL. It includes building the GLFW and Skia libraries from source.
Because this environment creates a graphical build environment that generates GUI applications, we need a way to display the GUI on the screen.
In WSL, this can be done in two ways: using the built-in WSLg subsystem (the default) or using the X11 protocol in combination with forwarding to the Windows host.
We will use the WSLg option. For more background information, see the background section **'Which Graphics Engine'** details below.

The setup process involves:

- Building GLFW 3.4 with CMake
- Building Skia graphics library with debug and release configurations
- Configuring dependencies for your development environment

<details class="nje-back-box">
  <summary>Which Graphics Engine
  </summary>

## Graphics Engine Used

**This GLFW-Skia C++ Template uses WSLg by default** - Microsoft's built-in graphics subsystem for WSL2 that provides native OpenGL support up to version 4.6.

### Two Graphics Options Available

1. **WSLg (Recommended & Default)** 
   - Built into modern WSL2 installations
   - Native OpenGL 4.6 support
   - Individual GUI applications display on Windows desktop
   - **This is what this template is configured for**

2. **X11 Forwarding (Alternative)**
   - Requires separate X11 server (XLaunch/VcXsrv)
   - Limited to OpenGL 1.4
   - Full desktop environment available
   - [See separate repository](https://github.com/NicoJanE/WSL-OS-With-GUI-Desktop) for setup

Unless you specifically need a full Linux desktop environment, stick with the default WSLg setup.

<p align="center" style="padding:20px;">─── ✦ ───</p>
</details> <span class="nje-br2"> </span>

---

<a id="Setup Instructions"></a>

## Setup Instructions

This is the **Linux component** of a dual-platform development environment:

- **Windows Setup**: Native development tools, Visual Studio, debugging → [Windows Setup Guide](setup_win)
- **WSL Linux Setup (This Page)**: Cross-platform builds and Linux testing

**Why both?** Development is done primarily on Windows, but you can build and test Linux versions seamlessly through WSL.

<a id="Prepare the WSL"></a>

### Prepare the WSL

Start your WSL, or create one first. Alternatively, you can import a default one if you have an exported version. In that case, use a command like:

<pre class="nje-cmd-multi-line-sm-indent0">
# From project root, import new WSL based on existing exported WSL.
wsl --import NewDist  .\_wsl_data\NewDist\ D:\WSL\WSL-Exports\Debian-clean.tar

# This command creates the directory `NewDist` automatically
# Note that '_wsl_data' must exist
</pre>

When you need to create a new WSL from scratch, use these recommended **manual installation** instructions. See [**here**](#manual-wsl) in the sub-paragraph [***WSL Notes & Background Information***](#notes-warnings-background), which contains the instructions

<details class="nje-warn-box">
  <summary> Alternative X11 Forwarding Setup Available
  </summary>

**Note:** This template uses **WSLg by default**, but I also provide an alternative X11 forwarding setup.

For a full Linux desktop experience, I provide a Debian-based WSL distribution that includes the **MATE X11 desktop environment**. This setup requires **XLaunch** (an X11 server) to be installed on the Windows host. **To get started with this alternative setup, see** [this repository](https://github.com/NicoJanE/WSL-OS-With-GUI-Desktop).  

**Important limitation:** X11 forwarding only supports older OpenGL versions (typically 1.4), while **WSLg supports OpenGL up to 4.6**. For GLFW-Skia development, WSLg provides much better graphics performance.

> **Tip: Check your current OpenGL version**  
> `glxinfo | grep "OpenGL version"`

**Recommendation:**{: style="color: black;font-size:13px; "}  
Stick with the default **WSLg setup** unless you specifically need a full Linux desktop environment.

</details>
<div class="nje-br4"> </div>

When starting WSL, make sure you use a WSL user that you have created. **Don't** use the root account! For instructions when needed, see [***Notes, Warnings & Background Information***](#notes-warnings-background).
Throughout the rest of this document, we will use `apt install` to install the required packages. Supported Linux distributions are mentioned in the link above.
<br>

### Decisions made

The following decisions that have been made, regarding project location and library locations:

- **Project locations**  
  This Linux setup uses the same project source directory as the Windows setup. This allows you to build the application for both Linux and Windows using a shared codebase, with only minimal setup required for each platform  
  <div class="nje-br1"> </div>
- **Library locations**  
  The libraries (***depot_tools, GLFW, and Skia***) for Windows are installed inside the project folder: `\dependencies\win`
  Under Linux, these packages are easier to install system-wide. Therefore, the Linux versions are installed **globally** where possible.
  For libraries that must be built **manually** (currently only depot_tools), they are installed in the **user's home folder** as part of the Linux development build.
<br>


<a id="WSL Notes"></a>

#### WSL Notes

This paragraph contains some background information about the WSL,  in case your are less familiar The WSL creation and usage.

<details class="nje-note-box">
  <summary>Debian-based Linux distributions🐧
  </summary>
  
**These distributions are based on Debian and use `apt`**

- Ubuntu,
- Linux Mint,
- Kali Linux,
- Pop!_OS,
- Zorin OS,
- Elementary OS,
- Parrot OS,
- and others
</details>
<div class="nje-br4"> </div>

<details class="nje-remark-box">
  <summary>Did you know? WSL Export & Import
  </summary>
  <div class="nje-text-block" style="background-color:#e6e3e3; color:black; margin-left:16px;">
   📍You can **export** and **import** WSL distributions? This can be very convenient: you can create a standard base WSL, export it, rename and import it for different projects. This also makes it easy to archive your WSL environment once you're done with a project.
  </div>
</details>
<div class="nje-br4"> </div>

<details class="nje-back-box">
  <a name="manual-wsl"></a>
  <summary>Manual Create WSL Environment🔧
  </summary>

# Introduction

This chapter explains how to set up a WSL backend environment manual by using the ***.Appx*** or ***.AppxBundle*** packages

## Download the WSL packages

- From [here](https://learn.microsoft.com/en-us/windows/wsl/install-manual).
- Scroll to the *"Downloading distributions" section.
- Download the Ubuntu 24.04 `.AppxBundle` (this guide assumes this version).
- Unpack the package, like, assuming you downloaded `Ubuntu2404-240425.AppxBundle`:

## Get the right **WSL Import** file

- Rename `Ubuntu2404-240425.AppxBundle` to `Ubuntu2404-240425.zip`
- Unpack it using 7zip or similar
- Find  `Ubuntu_2404.0.5.0_x64.appx` 
  - Rename it to: `Ubuntu_2404.0.5.0_x64.zip` unpack it.
  - Unpack it.  
**Result** you'll get the file: `install.tar.gz` this is what you’ll use in the next step,

### Create the WSL

To create the WSL file finally, Use:

- Place the WSL file in centralized location, i.e. `/My-wsl-environments/wsl-sample/`
- In that location execute:
  - `wsl --import wsl-sample /My-wsl-environments/wsl-sample install.tar.gz`  
   *(wsl --import [name wsl] [destination] [location-to/install.tar.gz] )*

### Other WSL commands

Some supporting WSL commands

<pre class="nje-cmd-multi-line">
wsl -l -v               # List all distributions with status
wsl -d [name]           # starts it
wsl --unregister [name] # Remove a distribution
wsl --export DistributionName BackupFile.tar
wsl --import NewDistributionName InstallLocation BackupFile.tar
</pre>

<p align="center" style="padding:20px;">─── ✦ ───</p>
</details>
<div class="nje-br4"> </div>

<details class="nje-back-box">
  <summary>Create User / Start WSL💫
  </summary>

### Why not use the root user

Avoid running WSL as the `root` user. Instead, create a normal user account, many GUI apps and build tools expect a standard user environment with a home directory, correct permissions, and access to `sudo`. Running as `root` can cause permission issues, misconfigured environments, or unexpected behavior during builds.
  
### Create a user

- `adduser nico`                    # create user with password & home directory
- `usermod -aG sudo nico`           # add to sudo group — allows use of sudo
- `su - nico`	                      # switch to the new user
- `cut -d: -f1 /etc/passwd`         # list all users (optional check)
- `getent group sudo`               # user member of su.
- `groups nico`                     # groups user belongs to
- `id nico`                         # ~same

### Start WSL with the new user

- `wsl -d debian-gui -u nico`                         # start WSL as this user
- `wsl --manage debian-gui --set-default-user nico`   # set default user

<p align="center" style="padding:20px;">─── ✦ ───</p>
</details>
<br>

**💫 New Setup with VSC Agent [See here](VSC-AgentMode_lin)**  
This will try to use the VS Co-pilot agent to install the installation, mentioned below (Experimental)

---

<a id="Install the GLFW library"></a>

### Install the GLFW library

Make sure you have a WSL environment installed and started, the following command are in the Bash shell of the WSL, installation is done with **root** user, alternatively you can create a user and install all under that user (see section [WSL-Notes](#WSL Notes))

- <pre class="nje-cmd-one-line-sm-indent1">wsl -d [wsl-name]          # starts it </pre>
- Install these libraries with:
  <pre class="nje-cmd-one-line-sm-indent1">sudo apt update </pre>
  <pre class="nje-cmd-one-line-sm-indent1">sudo apt install cmake g++ libglfw3-dev libgl1-mesa-dev libx11-dev gdb libxkbcommon-dev libxinerama-dev libxcursor-dev libxi-dev </pre>
- Find the  the include folder, note down the include folder, cause it is need below:
  <pre class="nje-cmd-one-line-sm-indent1">dpkg -L libglfw3-dev | grep '\.h$' </pre>
  <span class="nje-expect-block"> this may result something like:  
  /usr/include/GLFW/glfw3.h  
  /usr/include/GLFW/glfw3native.h  
  In that case make sure to to note down: **/usr/include/GLFW**
  </span>
- Find the  the lib folder, note it down library folder, cause it is need below:
  <pre class="nje-cmd-one-line-sm-indent1">dpkg -L libglfw3-dev | grep '\.so' </pre> 
  <span class="nje-expect-block"> this may result something like:  
  /usr/lib/x86_64-linux-gnu/libglfw.so
  In that case make sure to to note down: **/usr/lib/x86_64-linux-gnu/**
  </span>  
- Now Check and if need update the file <span class="nje-cmd-inline-sm">${PROJECT_SOURCE_DIR}cmake/linux.cmake</span> to update it with the include and library folders found earlier. The Items below can be found in the cmake function: **SetLinuxDirectories**.
  - <span class="nje-cmd-inline-sm">GLFW_LINUX_INCLUDE_DIR</span> Update this with the found **include** folder found (in our example:***/usr/include/GLFW*** )
  - <span class="nje-cmd-inline-sm">GLFW_LINUX_LIB_DIR  </span> Update this with the found **library** folder found (in our example:***/usr/lib/x86_64-linux-gnu/***)

<span class="nje-colored-block" style="margin-left:20px;"> <small>Be-aware: skim through the file: ${PROJECT_SOURCE_DIR}cmake/linux.cmake, it also contains linkage settings which may need to change, by default it is prepared for debug</small></span>

<div class="nje-br"> </div>

<details class="nje-remark-box">
  <summary> More general method to look for a specific library
  </summary>  
  A more general method to look for a specific library is:  
  <span class="nje-cmd-inline-sm">sudo find /usr/lib /usr/local/lib -name "libGL.so</span>
  (remember to drop the 'lib' and '.so' part when using the library in CMake\Make, just saying)
</details>
<div class="nje-br4"> </div>

---

<a id="Install the Skia library"></a>

### Install Skia library

The following Bash command assume the your inside the WSL, if not start it  with: 
<pre class="nje-cmd-one-line-sm-indent1" style="margin-top:-20px;" >wsl -d [wsl-name]   # starts it </pre>  

- Install the libraries with:
  <pre class="nje-cmd-one-line-sm-indent1">sudo apt update </pre>
  <pre class="nje-cmd-multi-line-sm-indent1"> sudo apt install build-essential git python3 pkg-config libglu1-mesa-dev libgl1-mesa-dev ninja-build \
    libfontconfig1-dev libexpat1-dev libfreetype6-dev libpng-dev libjpeg-dev libharfbuzz-dev libwebp-dev mesa-utils vulkan-tools
  </pre>

#### Install the library **depot_tools**

- Make a directory **tools/libs** in for the user home directory( <span class="nje-cmd-inline-sm">cd ~/</span>) and make sure user owns it. This is used to install the  **depot_tools** into, for example: <span class="nje-cmd-inline-sm">/home/name/tools/libs</span> and **cd** to it. Note that for our **root** user the directory is ***/root*** so create: <span class="nje-cmd-inline-sm">/root/tools/libs </span>
- In the <span class="nje-cmd-inline-sm">Libs</span> directory clone:
  <pre class="nje-cmd-one-line-sm-indent1">git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git</pre>
- Add the path to begin of the path environment (so it will have priority):  
  <pre class="nje-cmd-multi-line-sm-indent1">  echo 'export PATH="$HOME/tools/libs/depot_tools:$PATH"' >> ~/.bashrc  
    source ~/.bashrc </pre>

#### Setup amd configure Skia

- Use the new **created tools/libs** directory to install **Skia** into, thus make sure your in: <span class="nje-cmd-inline-sm"> cd $HOME/tools/libs</span>
- clone:
  <pre class="nje-cmd-one-line-sm-indent1">git clone https://skia.googlesource.com/skia.git </pre>
- Navigate to sub directory: <span class="nje-cmd-inline-sm">cd skia</span> run:
  <pre class="nje-cmd-one-line-sm-indent1">git checkout chrome/m126  # To checkout a stable build instead a the master(Use Same as on Windows!) </pre>
- Sync dependencies with, run:
   <pre class="nje-cmd-one-line-sm-indent1">python3 tools/git-sync-deps # this will install tools like ***gn*** and others </pre>
  - Check with the command:
    <pre class="nje-cmd-one-line-sm-indent1">which gn      # should display location of gn </pre>

### Creating build versions

All combinations can be found here but obvious choice is the **Shared Debug**  
The command assume your in the WSL in the directory: <span class="nje-cmd-inline-sm"> cd $HOME/tools/libs/skia</span>


- **Generate Static Release** build files with:  
  <pre class="nje-cmd-one-line-sm-indent1">./bin/gn gen out/release/static --args='is_official_build=true is_component_build=false is_debug=false skia_use_gl=true' </pre>
  - **Build it** with:  
    <pre class="nje-cmd-one-line-sm-indent1">ninja -C out/release/static </pre>

- **Generate Static Debug** build files with:  
  <pre class="nje-cmd-one-line-sm-indent1">./bin/gn gen out/debug/static --args='is_debug=true is_official_build=false is_component_build=false skia_use_gl=true'</pre>
  - **Build it** with:  
    <pre class="nje-cmd-one-line-sm-indent1">ninja -C out/debug/static </pre>

- **Generate Shared Release** build files with:
  <pre class="nje-cmd-one-line-sm-indent1">./bin/gn gen out/release/shared --args='is_debug=false is_official_build=true is_component_build=true skia_use_gl=true'</pre>
  - **Build it** with:  
    <pre class="nje-cmd-one-line-sm-indent1">ninja -C out/release/shared </pre>

- ✅**Generate Shared Debug** build files with:  
  <pre class="nje-cmd-one-line-sm-indent1">./bin/gn gen out/debug/shared --args='is_debug=true is_official_build=false is_component_build=true skia_use_gl=true' </pre>
  - **Build it** with:  
    <pre class="nje-cmd-one-line-sm-indent1">ninja -C out/debug/shared</pre>

### Check\Update ./cmake/linux.cmake file for Skia

- Now Check and if need update the file <span class="nje-cmd-inline-sm">${PROJECT_SOURCE_DIR}cmake/linux.cmake</span> to update it with the include and library folders found earlier. The Items below can be found in the cmake function: **SetLinuxDirectories**.
  - <span class="nje-cmd-inline-sm">SKIA_LINUX_CORE_INCLUDE_DIR</span> Update this with: **${ENV:HOME}/tools/libs/skia**
  - <span class="nje-cmd-inline-sm">SKIA_LINUX_LIBS_DIR  </span> Update this with: **${ENV:HOME}/tools/libs/skia/out/debug/shared**
  - Check also the <span class="nje-cmd-inline-sm">SKIA_LIBS_LOCAL</span> which specifies the use library name(s)

<span class="nje-colored-block" style="margin-left:20px;"> <small>Be-aware: skim through the file: ${PROJECT_SOURCE_DIR}cmake/linux.cmake, it also contains linkage settings which may need to change, by default it is prepared for debug</small></span>

**Use the the build documentation to build the [sample project](building_project)**


<span style="color: #6d757dff; font-size: 13px; font-style: italic;"> <br>
<i><b>License</b><br>This file is part of: **GLFW-Skia C++ Template Stack** Copyright (c) 2025-2026 Nico Jan Eelhart.This repository is [MIT licensed](../MIT-license.md) and free to use. For optional commercial support, customization, training, or long-term maintenance, see [COMMERCIAL.md](../COMMERCIAL.md).</i>
</span>

<br>
<p align="center">─── ✦ ───</p>
