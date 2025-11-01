---
layout: default_c

RefPages:
- setup_linux
- setup_win
- building_project
---  

<br>

# Project Structure and Header Usage Guide

------------------------------------------------------------------------------

## Directory Layout

<pre><code>
📁 include  
├─📂myproject                         ➜ <small><i>Project name</i></small>
│  └─📂gui                            ➜ <small><i>Related domain (Graphical User Interface)</i></small>
│     ├─📂glfw                        ➜ <small><i>domain library GLFW</i></small>
│     │  ├─📦app_glfw.h               ➜ <small><i>Public headers for glfw domain   </i></small>
│     │  └─📦app_Window.h             ➜ <small><i>More project specific, include in glfw.h</i></small>
│     └─📂skia                        ➜ <small><i>Domain library Skia</i></small>
│        ├─📦app_skia.h               ➜ <small><i>Public headers for skia domain</i> </small>
│        ├─📦app_canvas.h             ➜ <small><i>More project specific include in skia.h</i></small>
├─📂source                            ➜ <small><i>GLFW and Skia sample source</i></small>
│  ├─📂core                           ➜ <small><i>Core C++ implementation</i></small>
│  │ ├─📄Others.cpp                   ➜ <small><i>Many <b>project</b> specific <b>implementation</b> files </i></small>
│  │ └─📂internal                     ➜ <small><i><b>private core header files </b>inline's and templates   </i></small>
│  │    ├─📦group-common-externals.h  ➜ <small><i>Centralized include or third-party libraries and C++</i></small>
│  └─📂gui                            ➜ <small><i>Domain<sup>*1</sup></i></small>
│  │   ├─📂glfw                       ➜ <small><i>Domain implementation glfw<sup>*2</sup> </i></small>
│  │   │  ├─📄*.c                     ➜ <small><i>Many other project specific glfw <b>implementation</b> files</i></small>
│  │   │  └─📂internal                ➜ <small><i><b>private header files </b> inline's and templates   </i></small>
│  │   └─📂skia                       ➜ <small><i>Domain implementation skia </i></small>
│  │      ├─📄*.cpp                   ➜ <small><i>Many other project specific skia <b>implementation</b> files </i></small>
│  │      └─📂internal                ➜ <small><i><b>private header files </b> inline's and templates   </i></small>
│  │         ├─📦group-skia_core.h    ➜ <small><i>Grouped header files skia core<sup>*3</sup></i></small>
│  │         └─📦group-skia_*.h       ➜ <small><i>Other grouped header files related to skia<sup>*3</sup> </i></small>
│  └─⚡main.cpp                       ➜ <small><i>Main entry point</i></small>
└
</code></pre>

***Foot notes***

<sup>1</sup><small><b>Make sure to add these </b> to your intellisens setting (*c_cpp_properties.json* for VSC):  
<span class="nje-ident"></span>***include/***  
<span class="nje-ident"></span>***source/***  
and to your compiler include directories (CMake or your IDE) So internal headers like  these can be resolved:  
&nbsp;&nbsp;&nbsp;&nbsp; ***#include "core/internal/group-common-externals.h"***  (via source)  
&nbsp;&nbsp;&nbsp;&nbsp; ***#include "gui/glfw/internal/*.h"***  (via source)  
&nbsp;&nbsp;&nbsp;&nbsp; ***#include "myproject/gui/glfw/app_glfw.h.h"***  (via public include)

<sup>2</sup><small><b>Other domains.</b> You can of course add other folder domains like `skia` and `glf` in the same way </small>

<sup>3</sup><small>**Wrapper header file** that groups related domain headers into one header for convenience. Optionally apply to other libraries if required (e.g., GLFW).</small><br>

<br>

## Purpose and Usage

- `include/myproject/[gui/glfw]` This for example, includes contains **public headers** defining the application API regarding GLFW functionality.

- `source/core/internal` or `source/gui/skia/internal` for example contains all implementation code and private headers. headers are organized into subdirectories (e.g., gui/glfw/, gui/skia/) that mirror the namespace structure.

- Internal headers such as `glfw_helpers.h` :
    - should be placed inside `source/gui/glfw/internal/` folder for organization
    - When you make sure you have `source` in your compiler include path you can include it with: `#include gui/glfw/internal/glfw_helpers.h` <br><br>
    - ⚠️ **Avoid including `internal/` headers from outside their domain** unless absolutely necessary. These are tightly scoped to their own implementation folders.

- Public headers should **not expose raw backend types**
  (e.g., `GLFWwindow*`, Skia types). Use clean abstractions or the **PIMPL idiom** (*hide implementation from public headers, Reduce compile-time dependencies,Improve encapsulation/binary compatibility* ).

- Folder structure mirrors the C++ namespace:
  `myproject::gui::glfw::Window` → `include/myproject/gui/glfw/window.h`


## CMake Integration

In CMakeLists.txt (main)

- Add `include/` to the **include path**:
- Add `source/` to the **include path**:
  
```
    ...
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)  # Define the search path for headers
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/source)  # Define the search path for internal headers

```