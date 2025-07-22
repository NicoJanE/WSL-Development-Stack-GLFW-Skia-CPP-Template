<details>
<summary>📑 Table of Contents</summary>

- [1 Overview](#1-overview)
  - [1.1 Key Libraries Used](#11-key-libraries-used)
  - [1.2 Quick Setup Links](#12-quick-setup-links)
- [2 GLFW vs Skia](#2-glfw-vs-skia-roles-and-usage)
- [3 Template Project Architecture](#3-the-template-project-architecture)
- [4 Future Instructions](#4-future-instructions)

</details>



# 1 Overview

This is a template C++ project using the **GLFW** and **Skia** libraries to create a cross-platform graphical user interface (GUI) for **Windows** and **Linux**.  It uses **CMake** as the build system and includes a Skia-based sample application to demonstrate integration.

The project is preconfigured with:
- **Visual Studio Code** launch and task files for streamlined development.
- A `CMakePresets.json` file for easy integration with **Visual Studio 2022** on Windows.


### 1.1 Quick Setup Links

1. [Manual instructions For Linux](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_linux)
    - 💫 [VSC Agent Mode (WSL)](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/VSC-AgentMode_lin)    
1. [Manual instructions For Windows](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_win)    
    - 💫 [VSC Agent Mode (Windows)](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/VSC-AgentMode_win)    
1. [Build the sample project](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/building_project)

<br>

## 2. Libraries GLFW & Skia
This project uses two complementary, cross-platform libraries: GLFW for creating windows, managing graphics contexts, and handling user input, and Skia for high-performance, hardware-accelerated 2D drawing. GLFW focuses on windowing and input management without providing graphics rendering itself, which is why Skia is used to handle all rendering of text, images, and shapes with GPU acceleration. Together, they provide a robust foundation for building responsive and visually rich applications across Windows, Linux, and macOS.

#### GLFW, Windowing & Input

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
</summary>

<br>

> ### **Skia** library requires:  
>
>&nbsp;&nbsp; 📚  Python 3  
>&nbsp;&nbsp; 📚  Git  
>&nbsp;&nbsp; 📚  Depot Tools  
>
>These are all installed automatically during the Windows and Linux setup procedures linked above.

</details>

<details>
<summary>⚠️ OpenGL vs Vulkan Compatibility Notes
</summary>

<br>

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

<br>

## 3. The Template Project Architecture

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

<br>

## 4. Future instructions

**Build Environment Setup** manual instructions can be found here (see also the **Quick Configurations links** at the top):

- [For Linux](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_linux)
- [For Windows](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_win)

>Note that both use the same project source folder to build (Linux is build from the WSL Windows mount )

**Project build instruction** instructions for building the Sample with the VSC or Visual Studio or via the console can be found [here](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/building_project)

<br>


*Contact & Remarks*  
📧 NicoJanE@ziggo.nl
