
Overview source code

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
&nbsp;&nbsp;&nbsp;&nbsp; ***#include "gui/glfw/internal/\*.h"***  (via source)  
&nbsp;&nbsp;&nbsp;&nbsp; ***#include "myproject/gui/glfw/app_glfw.h.h"***  (via public include) </small>

<sup>2</sup><small><b>Other domains.</b> You can of course add other folder domains like `skia` and `glf` in the same way </small>

<sup>3</sup><small>**Wrapper header file** that groups related domain headers into one header for convenience. Optionally apply to other libraries if required (e.g., GLFW).</small><br><br>

<small><small><small>version 0.2</small> </small></small>