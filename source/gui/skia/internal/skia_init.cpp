
/*
 ────────────────────────────────────────── License ─────────────────────────────────────────────────
 This file is part of the Stack: GLFW-Skia-CPP-Template
 Copyright (c) 2025 Nico Jan Eelhart.
 Licensed under the MIT License. See the LICENSE.md file in the root directory of  this source tree.
───────────────────────────────────────────────────────────────────────────────────────────────────── 
*/


#include "gui/skia/internal/skia_init.h"
#include "core/internal/group-common-externals.h"


namespace myproject::gui::skia 
{
	// Implementation
	// --------------------------------------------- CLASS -------------------------------------------------

		/// @brief  Dtor
		GLBackendTarget::~GLBackendTarget()
		{
		}

		
		bool GLBackendTarget::init_skia_default(int w, int h)
		{
			// 1.1 Try creating a native OpenGL interface (auto-detect platform-specific bindings)
			
			auto interface = GrGLMakeNativeInterface();
			if (interface == nullptr) 
			{		
				// 1.2 Fallback: Manually assemble OpenGL interface using glfwGetProcAddress
				interface = GrGLMakeAssembledInterface(nullptr, (GrGLGetProc)glfw_proc_forwarder);

			}

			// 2. Create Skia GPU drawing context using OpenGL backend
			sContext = GrDirectContexts::MakeGL(interface);

			// 3.1 Define framebuffer target for Skia to render into (default screen framebuffer)
			GrGLFramebufferInfo framebufferInfo;
			framebufferInfo.fFBOID =to_enum_type(BufferTarget::SCREEN); 	// FBO 0 = default screen framebuffer
			framebufferInfo.fFormat = GL_RGBA8;								// Alternative: GL_SRGB8_ALPHA8 (uses gamma-corrected sRGB format)

			// 3.2 Map the framebufferInfo(3.1) to the OpenGL(BackendTarget) 
			SkColorType colorType = kRGBA_8888_SkColorType;
			GrBackendRenderTarget backendRenderTarget = GrBackendRenderTargets::MakeGL(	w, h,
																						to_enum_type( BufferProperties::NO_SAMPLE_COUNT),
																						to_enum_type(BufferProperties::NO_STENCIL),framebufferInfo);

			// 3.3 Wrap backend target(3.2) and context(2) in a SkSurface for Skia rendering
			//	- Optional: use SkColorSpace::MakeSRGB() for sRGB color space correction (before last param)
			sSurface = SkSurfaces::WrapBackendRenderTarget(sContext.get(), backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr);			
			if (sSurface == nullptr) 
			{
				fprintf(stderr, "Failed to create Skia surface.\n");
				// abort();
				return false;
			}

			return true;
		}


		

	// -------------------------------------- ### END CLASS ### --------------------------------------------

}
// NS