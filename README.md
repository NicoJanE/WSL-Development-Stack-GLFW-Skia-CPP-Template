# What

This is a template C++ project using the ***GLFW*** library to create a **Graphical User Interface control** for both Windows and Linux. It uses **CMake** as the build system.

> The **GLFW** library is based on OpenGL, OpenGL ES, and Vulkan. It provides an API for creating windows, handling input, and managing events.  
> For more information, [see the official GLFW website](https://www.glfw.org/).


> The Library **Skia**
> Skia is a 2D graphics library used for rendering. It provides APIs for drawing text, shapes, images, and more.
> It is the core graphics engine behind Chrome, Flutter, and Firefox (Canvas). [website](https://skia.org/) 


#### Quick links

1. [Environment instructions For Linux](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_linux)
    - [💫 New VSC Agent Setup](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/VSC-AgentMode_lin)    
1. [Environment instructions For Window](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_win)    
    - [💫 New VSC Agent Setup](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/VSC-AgentMode_win)    
1. [Build project](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/building_project)

<br>
📧 NicoJanE@ziggo.nl

<br>

## 1. GLFW vs Skia,  Roles and Usage

- **GLFW** is used for **creating windows**, managing **OpenGL or Vulkan contexts**, and handling **input events** (keyboard, mouse, etc.).
- **Skia** is used for **high-level 2D drawing**, including **text, images, shapes**, and **anti-aliased graphics**.
- They serve complementary roles with **minimal overlap**: *GLFW* provides the **platform and context**; *Skia* does the **drawing**.
- In this project, GLFW handles windowing and input, while Skia handles all drawing operations.

>⚠️ **Be-aware**  
>Both GLFW and Skia support OpenGL or Vulkan, but they must be configured to use the same graphics API.

>- For OpenGL, Skia uses classes like `GrGLInterface`, `GrBackendRenderTarget`, and `GrDirectContext`.
>- For Vulkan, Skia uses `GrVkBackendContext` and Vulkan-specific setup.
>
>Skia’s **API is mostly consistent** across backends, so **much of your drawing code stays the same**, only the backend setup differs.
> <br> <br>
 
> **Choice** <br>
><small>
>The sample is this project assume you use  OpenGL because it's simpler, mature, cross-platform, and  well-supported by Skia and GLFW.
> </small>
>
> **Converting** <br>
><small>
>Converting from OpenGL to Vulkan in this project is doable with some effort; it mainly involves changing the graphics backend initialization and context management (GLFW). Skia’s drawing code remains unchanged.  
>
>Supporting macOS is more challenging because **Apple** chose to not support Vulkan and instead reinvent the wheel with their own **Metal API***, making things harder for cross-platform developers.
> </small> <br>  

<br>

## 2. The Template Project Architecture

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

The **GLFW** library is used to create a canvas and to provide events and input.  
The **Skia** library is used for building core GUI components. Skia requires:  
&nbsp;&nbsp; 📚  Python 3  
&nbsp;&nbsp; 📚  Git  
&nbsp;&nbsp; 📚  Depot Tools  

<br>

## 3. Future instructions

**Build Environment Setup** instructions can be found here:

- [For Linux](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_linux)
- [For Window](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_win)

Note that both use the same project source folder to build (Linx is build from the WSL WWindos mount )

**Project build instruction** instructions for building the app with the  VSC or Visual Studio or via the consol can be found [here](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/building_project)

<br>
