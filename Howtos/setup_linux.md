---
layout: default_c

RefPages:
- setup_linux
- setup_win
- building_project
--- 

<br>

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  Linux Setup Instruction</span>

## Introduction

This template is intended for use with a **WSL** (Windows Subsystem for Linux) distribution running on a **Windows 11** host.
This section explains how to configure a Linux environment to build your GLFW/Skia project under WSL. **Check** the **three steps** below and use the side notes / instructions when appropriate 

## Graphics Engine Used

**This GLFW-Skia C++ Template uses WSLg by default** - Microsoft's built-in graphics subsystem for WSL2 that provides native OpenGL support up to version 4.6.

### Two Graphics Options Available:

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

**💫 New Setup with VSC Agent [See here](VSC-AgentMode_lin)**

---

## Setup Instructions

### Preparations

Start your WSL, or create one first alternatively you can import a default one if you have an exported version, in that case use a command like:

<pre class="nje-cmd-multi-line-sm-indent0">
# From project root, import new WSL based on existing exported WSL.
wsl --import NewDist  .\_wsl_data\NewDist\ D:\WSL\WSL-Exports\Debian-clean.tar

# This command creates the directory `NewDist` automatically
# Note that '_wsl_data' must exist
</pre>

When you need to create a new WSL from scratch you use this recommend  **manually installation** instructions, see [**here**](#manual-wsl) in the sub paragraph [***WSL Notes & Background Information***](#notes-warnings-background) which contains more additional information.

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

When starting the WSL make sure you use a WSL user that you hve created, **don't** use root account! Again see side note; [***Notes, Warnings & Background Information***](#notes-warnings-background) for instructions when needed
Throughout the rest of this document, we will use `apt install` to install the required packages, supported Linux distributions  ar mentioned in the above given link.
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

#### WSL Notes & Background Information {#notes-warnings-background}

This paragraph contains some background information in case your are less familiar with this project.

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
wsl [name] -d           # starts it
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

---

### Install GLFW library

- Install these libraries with:
  <pre class="nje-cmd-one-line-sm-indent1">sudo apt update </pre>
  <pre class="nje-cmd-one-line-sm-indent1">sudo apt install cmake g++ libglfw3-dev libgl1-mesa-dev libx11-dev gdb libxkbcommon-dev libxinerama-dev libxcursor-dev libxi-dev </pre>
- Find the  the include folder:
  <pre class="nje-cmd-one-line-sm-indent1">dpkg -L libglfw3-dev | grep '\.h$' </pre>
- Find the  the lib folder:
  <pre class="nje-cmd-one-line-sm-indent1">dpkg -L libglfw3-dev | grep '\.so' </pre> <div class="nje-br3"> </div>

  <details class="nje-remark-box">
  <summary> More general method to look for a specific library
  </summary>
   A more general method to look for a specific library is:  
   `sudo find /usr/lib /usr/local/lib -name "libGL.so`  
   (remember to drop the 'lib' and '.so' part when using the library in CMake\Make, just saying)
  </details><br>

- **Check\Update** the `cmake/linux.cmake` file with the include folder an library folder of GLFW, see function: **SetLinuxDirectories**.
- **Check\Update** the `GLFW_LIBS_LOCAL` which specifies the use library name(s) use for GLFW (and for some general libraries used)

---

### Install Skia library

- Install the libraries with:
  <pre class="nje-cmd-one-line-sm-indent1">sudo apt update` </pre>
  <pre class="nje-cmd-multi-line-sm-indent1">  sudo apt install build-essential git python3 pkg-config libglu1-mesa-dev libgl1-mesa-dev ninja-build
    libfontconfig1-dev libexpat1-dev libfreetype6-dev libpng-dev libjpeg-dev libharfbuzz-dev libwebp-dev mesa-utils vulkan-tools
  </pre>

### Install the library **depot_tools**

- Make a directory in for the user home directory(make sure user owns it) to install **depot_tools** into, for example: `/home/name/tools/libs` and **cd** to it
- clone:
  <pre class="nje-cmd-one-line-sm-indent1">git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git</pre>
- Add the path to begin of the path environment (so it will have priority):  
  <pre class="nje-cmd-multi-line-sm-indent1">  echo 'export PATH="$HOME/tools/libs/depot_tools:$PATH"' >> ~/.bashrc  
    source ~/.bashrc </pre>

### Setup amd configure Skia

- Use the new created  home directory to install **Skia** into, thus make sure your in: `/home/name/tools/libs/`
- clone:
  <pre class="nje-cmd-one-line-sm-indent1">git clone https://skia.googlesource.com/skia.git </pre>
- Navigate to: `cd skia` run:
  <pre class="nje-cmd-one-line-sm-indent1">git checkout chrome/m126`  # To checkout a stable build instead a the master(Use Same as on Windows!) </pre>
- Sync dependencies with, run:
   <pre class="nje-cmd-one-line-sm-indent1">python3 tools/git-sync-deps` # this will install tools like ***gn*** and others </pre>
  - Check with the command:
    <pre class="nje-cmd-one-line-sm-indent1">which gn      # should display location of gn </pre>

### Creating build versions

All combinations can be found here but obvious choice is the **Shared Debug**

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

For the Skia  include folder an library folder set the variables, see function: SetLinuxDirectories  

- For example set:
  <pre class="nje-cmd-one-line-sm-indent1"> set(SKIA_LINUX_CORE_INCLUDE_DIR "/home/name/tools/skia" CACHE PATH "SKIA include dir") </pre>
  <pre class="nje-cmd-one-line-sm-indent1">`set(SKIA_LINUX_LIBS_DIR "/home/name/tools/skia/out/debug/shared" CACHE PATH "SKIA Lib dir")</pre>

- Check also the `SKIA_LIBS_LOCAL` which specifies the use library name(s)

**Use the the build documentation to build the [sample project](building_project)**

<sub><i> This file is part of: GLFW-Skia C++ Template Stack Copyright (c) 2025 Nico Jan Eelhart. This source code is licensed under the MIT License found in the 'LICENSE.md' file in the root directory of this source tree.</i>
</sub>

<p align="center">─── ✦ ───</p>