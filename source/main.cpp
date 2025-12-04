//
// ────────────────────────────────────────── License ────────────────────────────────────────────────
//  This file is part of the Stack: GLFW-Skia-CPP-Template
//  Copyright (c) 2025 Nico Jan Eelhart.
//  Licensed under the MIT License. See the LICENSE.md file in the root directory of this source tree.
// ─────────────────────────────────────────────────────────────────────────────────────────────────── 


// Rendering backend selection
// ───────────────────────────────────────────────────────────────────────────────────────────────────
// Define one or more of the following:
//   - SK_GANESH   → Enable Skia GPU (Ganesh) backend
//   - SK_GL       → Enable OpenGL support
//
// ⚠️ Alternatively, you can define these in CMake:
//   add_compile_definitions(GLFW_INCLUDE_NONE SK_GL SK_GANESH)
#define SK_GANESH		
#define SK_GL


// Dependencies (external umbrella headers)
// ───────────────────────────────────────────────────────────────────────────────────────────────────
// This file depends on grouped headers for external libraries and rendering backends.
// See:
//   - `group-common-externals.h`	→ shared system/Skia/GL includes
//   - `group-skia_gpu.h`          	→ Ganesh/OpenGL integration
//	 - `group-skia_core.h`			→ Drawing APIs such as SkCanvas, SkSurface and others
//
//
// Project guidelines and dependency rules:
// 	- `code-structure.md`         → project layout, layering, and dependency rules


// External umbrella headers
#include "gui/skia/internal/group-skia_core.h"
#include "gui/skia/internal/group-skia_gpu.h"

// Internal headers for application implementation
#include "gui/glfw/internal/WindowImpl.h"
#include "gui/skia/internal/skia_init.h"

// Public API headers for the application update
#include "gui-control/gui/glfw/app_window.h"


// Convenience namespace aliases here.
namespace glfw = myproject::gui::glfw;	
namespace skia = myproject::gui::skia;	


// Using double buffering, which is the default in GLFW
// - Front buffer → the image currently shown on screen (owned by OpenGL)
// - Back buffer  → off-screen buffer where rendering happens (owned by OpenGL)
//	 Skia draws into the current OpenGL back buffer (exposed here as GLBackendTarget)
// - By default, glfwSwapBuffers will wait for the monitor’s refresh cycle 
//   if glfwSwapInterval(1) is set. This avoids tearing but may introduce frame pacing.
int main(void) 
{
	// GLFW initialization
	glfw::AppWindow windowMain(1800, 1600, "My Window");  
	windowMain.Setup_GLFW_Callbacks();
	
	// Setup Skia to render into the OpenGL back buffer via SkCanvas
	skia::GLBackendTarget backendTarget{};
	backendTarget.init_skia(800, 600);						
	
	auto* canvas = backendTarget.getCanvas(); 				// Skia owns this pointer, do not free
	while (!windowMain.ShouldClose() )   
	{
		// Process events. poll => without blocking.wait =>  blocks execution until an event occurs
		windowMain.ProcessEvents(EventStrategy::Wait);

		// TODO should be part of: skiaBackend
		SkPaint paint;
        paint.setColor(SK_ColorWHITE);
        canvas->drawPaint(paint);
        paint.setColor(SK_ColorBLUE);
        canvas->drawRect({100, 200, 300, 500}, paint);
        backendTarget.flush();								// Submit Skia’s draw commands to the OpenGL back buffer

		// Swap buffers: display the back buffer (now with Skia's rendering)
        // and make the old front buffer the new back buffer
		glfwSwapBuffers( windowMain.GetWindowHandle() );	
	
	}


	glfwDestroyWindow( windowMain.GetWindowHandle() ); 
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
