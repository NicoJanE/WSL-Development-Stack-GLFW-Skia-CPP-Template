
/*
 ────────────────────────────────────────── License ─────────────────────────────────────────────────
 This file is part of the Stack: GLFW-Skia-CPP-Template
 Copyright (c) 2025 Nico Jan Eelhart.
 Licensed under the MIT License. See the LICENSE.md file in the root directory of  this source tree.
──────────────────────────────────────────────────────────────────────────────────────────────────── */


 /* ─────────────────────────────────────────────────────────────────────────────────────────────────
 🧠 PURPOSE: Implements internal (non-public) Skia initialization and backend setup for the
             application's OpenGL rendering pipeline. This includes SkiaBackendGL methods for
             creating and managing GPU contexts and render surfaces.

 📄 Description:
     - Provides platform-specific OpenGL procedure resolution using GLFW.
     - Implements SkiaBackendGL initialization for both managed (smart pointer) and raw contexts.
     - Configures GrDirectContext, framebuffer targets, and SkSurface wrapping for Skia rendering.
     - Intended for use only within the GUI/Skia module; not part of the public API.
 ─────────────────────────────────────────────────────────────────────────────────────────────────── */

#pragma once
#include "core/internal/group-common-externals.h"
#include "gui/skia/internal/group-skia_core.h"
#include "gui/skia/internal/group-skia_gpu.h"

//TODO NAMESPACE
namespace myproject::gui::skia 
{

    // ********************************************* ENUMS *************************************************

    enum class BufferTarget :unsigned int
    {
        SCREEN = 0,
    };

    enum class BufferProperties :unsigned int
    {
        NO_SAMPLE_COUNT = 0,
        NO_STENCIL = 0,
    };

    // **************************************** #### END ENUMS #### ****************************************


    // ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ TEMPLATES ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

    template <typename E>
    constexpr auto to_enum_type(E e) noexcept 
    {
        static_assert(std::is_enum<E>::value, "to_underlying requires an enum type");
        return static_cast< std::underlying_type_t<E> >(e);
    }

    // ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ #### END TEMPLATES #### ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■


    // Implementation
    // --------------------------------------------- CLASS -------------------------------------------------


        // ───────────────────────────────────────────────────────────────────────────────────────────────────
        // Initialize Skia backends for different Drawing libraries (OpenGL, vulkan)  
        // ───────────────────────────────────────────────────────────────────────────────────────────────────
        //
        // ───────────────────────────────────────────────────────────────────────────────────────────────────
        //  CLASS: SkiaBackendGL
        //  This class builds a Skia backend for GPU-accelerated rendering via OpenGL. All GPU objects, such 
        //  as GrDirectContext and SkSurface — are created inside its methods using Skia's factory functions
        //
        //  PURPOSE:
        //      Builds and manages a Skia GPU backend for OpenGL rendering.
        //      Owns all GPU objects created via Skia factory functions (e.g., MakeGL(),
        //      WrapBackendRenderTarget()) and ensures their proper destruction.
        //
        //  OWNERSHIP MODEL:
        //      - By default, GPU objects are stored in sk_sp<> smart pointers for automatic reference
        //        counting and safe memory management.
        //      - The raw-pointer variant (init_skia_raw) exists only for:
        //          1. Integration with legacy C APIs or third-party libraries that do not accept sk_sp<>.
        //          2. Performance-critical cases where profiling shows sk_sp<> overhead is significant.
        //
        //  NOTES:
        //      - Retrieving an object pointer (e.g., getCanvas()) does not require smart pointer ownership.
        //      - This class is internal; it should not be included in public headers.
        // ───────────────────────────────────────────────────────────────────────────────────────────────────
        class GLBackendTarget
        {
            public:
            
            //CTORS & DTORS
            GLBackendTarget()  {}
            ~GLBackendTarget();
            
            GLBackendTarget(const GLBackendTarget&   right)             = delete;
            GLBackendTarget(GLBackendTarget&& right )                   = delete;
            GLBackendTarget& operator=(const GLBackendTarget& right)    = delete;
            GLBackendTarget& operator=(GLBackendTarget&& right)         = delete;



            // Public (internal) methods ??
            bool        init_skia(int w, int h)      { return  init_skia_default(w,h); }
            SkCanvas*   getCanvas()                  { return sSurface->getCanvas(); }  // TODO null check
            
            void        flush()                      { sContext->flush();} // TODO null check

            
            private:

            bool init_skia_default(int w, int h);
            bool init_skia_raw(int w, int h);                       // Only use the Raw pointer method if you must
            void cleanRaw();


        
            sk_sp<GrDirectContext>  sContext;
            sk_sp<SkSurface>        sSurface;

            // Raw pointers for init_skia_raw
            GrDirectContext*    sContext_raw {nullptr};
            SkSurface*          sSurface_raw {nullptr};



        };

    // -------------------------------------- ### END CLASS ### --------------------------------------------    


    // ========================================= FREE FUNCTIONS ============================================


        inline void* glfw_proc_forwarder(void*, const char* p) 
        {
        return (void*)glfwGetProcAddress(p);
        }


    // =================================== #### END FREE FUNCTIONS #### ====================================
	
}