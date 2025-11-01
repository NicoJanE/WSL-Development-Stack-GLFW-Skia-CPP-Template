---
layout: default_c
RefPages:
- setup_linux
- setup_win
- building_project
--- 
<br>

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  WSL Setup & Usage Guide</span>

## ℹ️ Introduction

This is a template C++ project using the ***GLFW*** library to create a **Graphical User Interface control** for both Windows and Linux. It uses **CMake** as the build system.

> The **GLFW** library is based on OpenGL, OpenGL ES, and Vulkan. It provides an API for creating windows, handling input, and managing events.  
> For more information, [see the official GLFW website](https://www.glfw.org/).

> The Library **Skia**
> Skia is a 2D graphics library used for rendering. It provides APIs for drawing text, shapes, images, and more.
> It is the core graphics engine behind Chrome, Flutter, and Firefox (Canvas). [website](https://skia.org/)

---

## ▶️ GLFW vs Skia,  Roles and Usage

- **GLFW** is used for **creating windows**, managing **OpenGL or Vulkan contexts**, and handling **input events** (keyboard, mouse, etc.).
- **Skia** is used for **high-level 2D drawing**, including **text, images, shapes**, and **anti-aliased graphics**.
- They serve complementary roles with **minimal overlap**: *GLFW* provides the **platform and context**; *Skia* does the **drawing**.
- In this project, GLFW handles windowing and input, while Skia handles all drawing operations.

> **Be-aware**⚠️  
>Both GLFW and Skia support OpenGL or Vulkan, but they must be configured to use the same graphics API.
>
>>For OpenGL, Skia uses classes like `GrGLInterface`, `GrBackendRenderTarget`, and `GrDirectContext`.  
>> For Vulkan, Skia uses `GrVkBackendContext` and Vulkan-specific setup.  
>
>Skia’s **API is mostly consistent** across backends, so **much of your drawing code stays the same**, only the backend setup differs.
> <br>
 
> **Decision** <br>
><small>
>The sample is this project assume you use  OpenGL because it's simpler, mature, cross-platform, and  well-supported by Skia and GLFW.
> </small>

> **Converting** <br>
><small>
>Converting from OpenGL to Vulkan in this project is doable with some effort; it mainly involves changing the graphics backend initialization and context management (GLFW). Skia’s drawing code remains unchanged.  
> </small>

> **MacOS** <br>
><small>
>Supporting macOS is more challenging because **Apple** chose to not support Vulkan and instead reinvent the wheel with their own **Metal API**, making things harder for drawing cross-platform developers.
> </small> <br>  

---

## 📚  The Template Project Architecture

This template provides a project structure for building a GUI control sample application using the **GLFW** and **Skia** libraries. It supports both Windows and Linux (Debian 12) operating systems. On Windows, the project uses the **NMake** toolchain from Visual Studio 2022 Community Edition. On Debian, it uses the **GNU Make**, tool provided by GNU Compiler Collection (GCC) via WSL.


The folder structure (<small>some folders and files are not include because they are Github specific files(layout ect.) :

<pre><code>
📁 Project  
├──📂.vscode                    ➜ <i>VSC Tasks & Launchers </i>
├──📂_README                    ➜ <i>Documentation </i>
│   └──🧾 README.md             ➜ <i>The readme instruction file (<b>this file</b>)</i>
├──📂cmake                      ➜ <i>Specialized, customizable, CMake files for Windows and Linux </i>
│   ├──📦CMakeLists_Init-env.bat➜ <i>Path to env variables for MS VC compiler(<b>vcvars64.bat</b>)</i>
│   ├──📦CMakeLists_start.sh.in ➜ <i>Creates startup app logic in Linux builds  </i>
│   ├──📦linux.cmake            ➜ <i>The file to <b>customize for Linux</b> builds  </i>
│   ├──📦linux_utilities.cmake  ➜ <i>Linux utilities to display hard/software info.  </i>
│   └──📦windows.cmake          ➜ <i>The file to <b>customize for Windows</b> builds  </i>
├──📂dependencies/win           ➜ <i>Dependent libraries needed for the source like <b>GLFW</b> & <b>Skia</b></i>
│   ├──📂win                    ➜ <i>Windows location for specialized libs </i>
│   │   └──📂Your Lib           ➜ <i>Add libraries you need here </i>
│   └──📂linux                  ➜ <i>Linux location for specialized libs </i>
│       └──📂Your Lib           ➜ <i>Add libraries you need here </i>
├──📂src                        ➜ <i>GLFW and Skia sample source</i>
├──⚡build.ps1                  ➜ <i>Windows script to invoke the build</i>
├──⚡build.sh                   ➜ <i>Linux script to invoke the build</i>
├──📦CMakeLists.txt             ➜ <i>Main CMake file</i>
├──📦CMakePresets.json          ➜ <i>Used to load the project in Visual Studio 2022</i>

</code></pre>

The **GLFW** library is used to create a canvas and to provide events and input.  
The **Skia** library is used for building core GUI components. Skia requires:  
&nbsp;&nbsp; 📚  Python 3  
&nbsp;&nbsp; 📚  Git  
&nbsp;&nbsp; 📚  Depot Tools  

---

## ⚙️More Instructions

**Build Environment Setup** instructions can be found here:

- [For Linux](./Howtos/setup_linux)
- [For Window](./Howtos/setup_win)

> *Note:*{: style="color: black;font-size:14px; "} <br>
> <small>Both( Linux and Windows) use the same project source folder to build (Linux is build from the WSL Windos mount)  <br></small>

**Project build instruction** instructions for building the app with the  VSC or Visual Studio or via the consol can be found [here](./Howtos/building_project)

<sub> This file is part of:  **GLFW-Skia C++ Template Stack**
Copyright (c) 2025 Nico Jan Eelhart. This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.
</sub>

<p align="center">─── ✦ ───</p>
