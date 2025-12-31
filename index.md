---
layout: default_c
RefPages:
- setup_linux
- setup_win
- building_project


TableCont:
- Introduction
- Library Setup
- More GLFW & Skia
- Project Architecture
--- 
<br>

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  Docker Container</span>

![MIT License](https://img.shields.io/badge/License-MIT-green) ![Commercial Services Available](https://img.shields.io/badge/Services-Optional-blue)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-brightgreen)
![C++](https://img.shields.io/badge/C++-17-blue.svg)

<a id="Introduction"></a>

## ℹ️ Introduction

This is a template C++ project using the **GLFW** and **Skia** libraries (built from source) to create a cross-platform graphical user interface (GUI) for **Windows** and **Linux**.  It uses **CMake** as the build system and includes a Skia-based sample application to demonstrate integration.

The project is preconfigured with:

- **Visual Studio Code** launch and task files for streamlined development.
- A `CMakePresets.json` file for easy integration with **Visual Studio 2022/2026** on Windows.
- Build instruction for building the GLFW and Skia libraries from source.
- A sample (template) project with source using GLFW and Skia.

---

<a id="Library Setup"></a>

## ⚙️🏃‍♂️ Library Setup Instructions

⏱️ **Note:** Building GLFW and Skia from source is a comprehensive process that can take some time (especially Windows Skia). Follow the detailed setup guides below. To access the installation instructions, use one of the links below. For more details, read the rest of this document.

<table>
<tr>
<th style="text-align: left;"><strong><em>Platform</em></strong></th>
<th style="text-align: left;"><strong><em>Purpose</em></strong></th>
<th style="text-align: left;"><strong><em>Setup Guide</em></strong></th>
<th style="text-align: left;">Agent Mode (experimental)</th>
</tr>
<tr>
<td style="text-align: left;">🪟 <strong>Windows</strong></td>
<td style="text-align: left;">Native development, VS Code, debugging</td>
<td style="text-align: left;"><strong><a href="https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_win">Windows Setup</a></strong></td>
<td style="text-align: left;">💫 <strong><a href="https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/VSC-AgentMode_win">VSC Agent Mode Windows</a></strong></td>
</tr>
<tr>
<td style="text-align: left;">🐧 <strong>WSL Linux</strong></td>
<td style="text-align: left;">Cross-platform builds, Linux testing</td>
<td style="text-align: left;"><strong><a href="https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_linux">Linux Setup</a></strong></td>
<td style="text-align: left;">💫 <strong><a href="https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/VSC-AgentMode_lin">VSC Agent Mode Linux</a></strong></td>
</tr>

<tr>
<td colspan="4" style="font-size: 0.85em; text-align: left;"><em><sup>*</sup>Both setups work together — you'll develop on Windows but can build/test on Linux seamlessly.</em></td>
</tr>
</table>
<br>  

## ⚙️🏃‍♂️ Building the sample project

A sample project is included and can be used after the above libraries are set up. For build instructions, see:

<table  style="width: 43%">
<tr>
<th colspan="2" style="text-align: left;">📚 <strong>Other Instructions</strong> (next step)</th>
</tr>
<tr>
<td style="text-align: left;">Build & use the Sample Template Project</td>
<td style="text-align: left;"><strong><a href="https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/building_project">Instructions Here</a></strong></td>
</tr>
</table>

<span class="nje-br2"> </span>

<a id="More GLFW & Skia"></a>

## 📦 More about GLFW & Skia

This project uses two complementary, cross-platform libraries: GLFW for creating windows, managing graphics contexts, and handling user input, and Skia for high-performance, hardware-accelerated 2D drawing. GLFW focuses on windowing and input management without providing graphics rendering itself, which is why Skia is used to handle all rendering of text, images, and shapes with GPU acceleration. Together, they provide a robust foundation for building responsive and visually rich applications across Windows, Linux, and macOS.

### GLFW, Windowing & Input

[GLFW](https://www.glfw.org/) is a lightweight, cross-platform library. It's commonly used for building real-time applications like games, simulations, and custom GUI frameworks. It provides:

- **OpenG**L - OpenGL ES, and Vulkan context creation
- **Window** - creation and management
- **Input** - handling (keyboard, mouse, etc.)

#### Skia, 2D Graphics Engine

[Skia](https://skia.org/) is a high-performance 2D graphics library. It supports text rendering, vector shapes, images, gradients, and more, all with hardware acceleration. In this project, Skia handles all 2D drawing, while GLFW handles the window and input. Note that it is also used by: Google Chrome, Flutter, Mozilla Firefox (Canvas API)

- **Backend flexibility** – Unified API for CPU/GPU via OpenGL, Vulkan, Metal, or software.
- **Precision rendering** – Anti-aliased text, vector shapes, and subpixel accuracy.
- **Versatile output** – Renders to OpenGL surfaces, images, PDFs, or SVG.

<details class="nje-note-box">
  <summary>🧰 Skia Build Requirements:
  </summary>
  
### Skia library build requires  
  
  &nbsp;&nbsp; 📚  Python 3  
  &nbsp;&nbsp; 📚  Git  
  &nbsp;&nbsp; 📚  Depot Tools  
  &nbsp;&nbsp; 📚  Ninja build system  
  
  These dependencies must be installed and configured following the detailed setup procedures linked above. The Skia build process is comprehensive and involves cloning the repository, syncing dependencies, and building with specific configurations.
</details>
<span class="nje-br2"> </span>

<details class="nje-note-box">
<summary>⚠️ OpenGL vs Vulkan Compatibility Notes
</summary>

## OpenGL or Vulkan

Both GLFW and Skia support OpenGL or Vulkan, but they must be configured to use the same graphics API.

For OpenGL, Skia uses classes like GrGLInterface, GrBackendRenderTarget, and GrDirectContext.  
For Vulkan, Skia uses GrVkBackendContext and Vulkan-specific setup.  
Skia's API is mostly consistent across backends, so much of your drawing code stays the same, only the backend setup differs.

 **Choice**
The sample in this project assumes you use OpenGL because it's simpler, mature, cross-platform, and well-supported by Skia and GLFW.

**Converting**
Converting from OpenGL to Vulkan in this project is doable with some effort; it mainly involves changing the graphics backend initialization and context management (GLFW). Skia's drawing code remains unchanged.

Supporting macOS is more challenging because Apple chose to not support Vulkan and instead reinvent the wheel with their own Metal API, making things harder for cross-platform developers.

</details>
<span class="nje-br2"> </span>

<details class="nje-note-box">
<summary>⚠️ Common Setup Pitfalls
</summary>

**Windows-specific issues to avoid:**

- **Path length limits** – Skia builds can fail with "file name too long" errors. Use short paths like `C:\libs\skia`  
- 🚫 **ninja.exe vs ninja.bat** – Ensure the official `ninja.exe` is first in your PATH, not `depot_tools\ninja.bat`  
- 🚫 **Old environment variables** – Previous Skia builds can leave conflicting EMSDK variables  
- ⏱️ **Build time** – Skia builds can take significant time; plan accordingly  
- 🚫 **Spaces in paths** – Avoid spaces or special characters in project paths  

 See the detailed setup guides for complete troubleshooting information.

</details>
<span class="nje-br2"> </span>

---

<a id="Project Architecture"></a>

## ⚡The Template Project Architecture

This template consists of a template project for building a **GUI control** sample application based on the **GLFW** library and the **Skia** library. Supporting both **Windows**  and **Linux** (Debian 12) operating systems. For Windows, the **MSBuild** toolchain of Visual Studio 2022/2026 Community Edition is used, and for Debian the **GNU Compiler Collection** is used.

The folder structure (<small> some folders and files are not include because they are Github specific files(layout ect.) :

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

<a id="more"></a>
<details class="nje-warn-box">
  <summary>Libraries: OpenGL, OpenGL ES, and Vulkan
  </summary>
  Both GLFW and Skia support OpenGL or Vulkan, but they must be configured to use the same graphics API.
  - For OpenGL, Skia uses classes like `GrGLInterface`, `GrBackendRenderTarget`, and `GrDirectContext`.   
  - For Vulkan, Skia uses `GrVkBackendContext` and Vulkan-specific setup.  
  Skia’s **API is mostly consistent** across backends, so **much of your drawing code stays the same**, only the backend setup differs.

  **Decision in this project**  
  The sample is this project assume you use  OpenGL because it's simpler, mature, cross-platform, and  well-supported by Skia and GLFW.

  **Converting**  
  Converting from OpenGL to Vulkan in this project is doable with some effort; it mainly involves changing the graphics backend initialization and context management (GLFW). Skia's drawing code remains unchanged.  

  **MacOS specifics**  
  Supporting macOS is more challenging because **Apple** chose to not support Vulkan and instead reinvent the wheel with their own **Metal API**, making things harder for drawing cross-platform developers.

</details>
<span class="nje-br2"> </span>

---

<a id="more"></a>

<span style="color: #6d757dff; font-size: 13px; font-style: italic;"> <br>
<i><b>License</b><br>This file is part of: **GLFW-Skia C++ Template Stack** Copyright (c) 2025-2026 Nico Jan Eelhart.This repository is [MIT licensed](MIT-license.md) and free to use. For optional commercial support, customization, training, or long-term maintenance, see [COMMERCIAL.md](COMMERCIAL.md).</i>
</span>

<br>
<p align="center">─── ✦ ───</p>
