<details>
<summary>📑 Table of Contents</summary>

- [Introduction](#introduction)
- [Quick Setup](#qsetup)
- [Libraries GLFW & Skia](#lib)
- [The Template Project Architecture](#temp)
- [More Instructions](#more)

</details>

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  Docker Container</span>

<a id="introduction"></a>

## ℹ️ Introduction

This is a template C++ project using the **GLFW** and **Skia** libraries to create a cross-platform graphical user interface (GUI) for **Windows** and **Linux**.  It uses **CMake** as the build system and includes a Skia-based sample application to demonstrate integration.

The project is preconfigured with:

- **Visual Studio Code** launch and task files for streamlined development.
- A `CMakePresets.json` file for easy integration with **Visual Studio 2022** on Windows.

---

<a id="qsetup"></a>

## ⚙️🏃‍♂️ Setup Instructions

To move quickly to the installation instruction use one of the links below

<table>
<tr>
<th align="left"><strong><em>Platform</em></strong></th>
<th align="left"><strong><em>Purpose</em></strong></th>
<th align="left"><strong><em>Setup Guide</em></strong></th>
<th align="left">Agent Mode</th>
</tr>
<tr>
<td>🪟 <strong>Windows</strong></td>
<td>Native development, VS Code, debugging</td>
<td><strong><a href="./Howtos/setup_win">Windows Setup</a></strong></td>
<td>💫 <strong><a href="https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/VSC-AgentMode_win">VSC Agent Mode Windows</a></strong></td>
</tr>
<tr>
<td>🐧 <strong>WSL Linux</strong></td>
<td>Cross-platform builds, Linux testing</td>
<td><strong><a href="./Howtos/setup_linux">Linux Setup</a></strong></td>
<td>💫 <strong><a href="https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/VSC-AgentMode_lin">VSC Agent Mode Linux</a></strong></td>
</tr>
<tr>
<td colspan="4" style="font-size: 0.85em; text-align: left;"><em><sup>*</sup>Both setups work together — you'll develop on Windows but can build/test on Linux seamlessly.</em></td>
</tr>
</table>

<br>  

<table>
<tr>
<th colspan="2" align="left">📚 <strong>Other Instructions</strong> (next step)</th>
</tr>
<tr>
<th align="left"><strong><em>Document type</em></strong></th>
<th align="left"><strong><em>Location</em></strong></th>
</tr>
<tr>
<td><strong>Project Build Instruction</strong></td>
<td><strong><a href="./Howtos/building_project">Here</a></strong></td>
</tr>
</table>


---

<a id="lib"></a>

## 📦 Libraries GLFW & Skia

This project uses two complementary, cross-platform libraries: GLFW for creating windows, managing graphics contexts, and handling user input, and Skia for high-performance, hardware-accelerated 2D drawing. GLFW focuses on windowing and input management without providing graphics rendering itself, which is why Skia is used to handle all rendering of text, images, and shapes with GPU acceleration. Together, they provide a robust foundation for building responsive and visually rich applications across Windows, Linux, and macOS.

### GLFW, Windowing & Input

[GLFW](https://www.glfw.org/) is a lightweight, cross-platform library. It’s commonly used for building real-time applications like games, simulations, and custom GUI frameworks. It provides:

- **OpenG**L - OpenGL ES, and Vulkan context creation
- **Window** - creation and management
- **Input** - handling (keyboard, mouse, etc.)

#### Skia, 2D Graphics Engine

[Skia](https://skia.org/) is a high-performance 2D graphics library. It supports text rendering, vector shapes, images, gradients, and more, all with hardware acceleration. In this project, Skia handles all 2D drawing, while GLFW handles the window and input. Note that it is also used by: Google Chrome, Flutter, Mozilla Firefox (Canvas API)

- **Backend flexibility** – Unified API for CPU/GPU via OpenGL, Vulkan, Metal, or software.
- **Precision rendering** – Anti-aliased text, vector shapes, and subpixel accuracy.
- **Versatile output** – Renders to OpenGL surfaces, images, PDFs, or SVG.

<details>
<summary> 🧰 Skia Requirement:  
</summary><br>

> ### **Skia** library requires  
>
>&nbsp;&nbsp; 📚  Python 3  
>&nbsp;&nbsp; 📚  Git  
>&nbsp;&nbsp; 📚  Depot Tools  
>
>These are all installed automatically during the Windows and Linux setup procedures linked above.

</details>

<details>
<summary>⚠️ OpenGL vs Vulkan Compatibility Notes
</summary><br>

> ###  OpenGL or Vulkan
>
>Both GLFW and Skia support OpenGL or Vulkan, but they must be configured to use the same graphics API.
>
>For OpenGL, Skia uses classes like GrGLInterface, GrBackendRenderTarget, and GrDirectContext.  
>For Vulkan, Skia uses GrVkBackendContext and Vulkan-specific setup.  
>Skia’s API is mostly consistent across backends, so much of your drawing code stays the same, only the backend setup differs.
>
> **Choice**
>The sample in this project assumes you use OpenGL because it's simpler, mature, cross-platform, and well-supported by Skia and GLFW.
>
>**Converting**
>Converting from OpenGL to Vulkan in this project is doable with some effort; it mainly involves changing the graphics backend initialization and context management (GLFW). Skia’s drawing code remains unchanged.
>
>Supporting macOS is more challenging because Apple chose to not support Vulkan and instead reinvent the wheel with their own Metal API, making things harder for cross-platform developers.

</details>

---

<a id="temp"></a>

## ⚡The Template Project Architecture

This template consists of a template project for building a **GUI control** sample application based on the **GLFW** library and the **Skia** library. Supporting both **Windows**  and **Linux** (debian 12) operating systems. For Windows the **NMake** toolchain of the  Visual Studio 2022 Community edition applications is used and for Debian the **GNU Compiler Collection** is used.

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

---

<a id="more"></a>


<br>
<p align="center">
  <a href="https://nicojane.github.io/WSL-Template-Stacks-Home/">
    <img src="assets/images/WSLfooter.svg" alt="WSL Template Stacks" width="400" />
  </a>
</p>

<sub> <i>This file is part of:  **GLFW-Skia C++ Template Stack**
Copyright (c) 2025 Nico Jan Eelhart. This source code is licensed under the MIT License found in the  'LICENSE.md' file in the root directory of this source tree.</i>
</sub>

<p align="center">─── ✦ ───</p>
