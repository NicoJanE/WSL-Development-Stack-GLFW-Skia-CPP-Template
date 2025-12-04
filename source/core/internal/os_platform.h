/*
─────────────────────────────────────────── License ─────────────────────────────────────────────────
 This file is part of the Stack: GLFW-Skia-CPP-Template
 Copyright (c) 2025 Nico Jan Eelhart.
 Licensed under the MIT License. See the LICENSE.md file in the root directory of  this source tree.
───────────────────────────────────────────────────────────────────────────────────────────────────── 
*/

#pragma once

// ────────────────────────────────────────────────────────────────────────────────────────────────────
//  Cross-Platform Native Window & Graphics Context Abstraction
// ────────────────────────────────────────────────────────────────────────────────────────────────────
//
//  🌟 Purpose: Provides unified access to OS-specific window handles and graphics contexts across
//              different platforms. Abstracts platform differences between Windows, Linux, and macOS
//              for windowing system integration.
//
//  💫 Usage:   Convert windowing library handles to native OS handles for platform-specific operations:
//              
//              Windows:  HWND hwnd = GetNativeWindowHandleAs<HWND>(windowHandle);
//              Linux:    Window xwin = GetNativeWindowHandleAs<Window>(windowHandle);  
//              macOS:    NSWindow* nswin = GetNativeWindowHandleAs<NSWindow*>(windowHandle);
//
//  🧩 Features:
//              ✓ Template-based type-safe conversion
//              ✓ Compile-time platform detection
//              ✓ Centralized OS-specific includes (OpenGL, native window APIs)
//              ✓ Extensible design for multiple (windowing) libraries
//              ✓ Static assertion for pointer type safety
//
//  🔧 Current Implementation:
//              Currently supports GLFW as the windowing library backend.
//              Future versions may add support for SDL, native APIs, or other libraries.
//                        
//  ⚠️ Notes:
//      1. Only pointer types are supported for template parameters
//      2. Returns nullptr on unsupported platforms
//      3. Requires linking with platform-specific libraries (user32.dll, X11, Cocoa)
//      4. OpenGL headers may conflict with other GL loaders - include this file first
//      5. Implementation details are abstracted - see source for current backend
//


#if defined(_WIN32)
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
    #include <GL/gl.h>

#elif defined(__linux__)
    #define GLFW_EXPOSE_NATIVE_X11
    #include <GLFW/glfw3native.h>
    #include "/usr/include/GL/gl.h"    // OpenGL Library
    
#elif defined(__APPLE__)
    #define GLFW_EXPOSE_NATIVE_COCOA
    #include <GLFW/glfw3native.h>
    #include <OpenGL/gl3.h>            // OpenGL on macOS, in version:14 from 2023 was still available but already for long tiome deprecated (2018)

#endif

#include <type_traits>
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ TEMPLATES ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

/// Sample Call Windows: HWND hwnd = GetNativeWindowHandleAs<HWND>( GLFWwindow* win );
template<typename T>
T GetNativeWindowHandleAs(GLFWwindow* handle)
{
    static_assert(std::is_pointer<T>::value, "T must be a pointer type");

    #if defined(_WIN32)
        return static_cast<T>(glfwGetWin32Window(handle));
    #elif defined(__linux__)
        return static_cast<T>(glfwGetX11Window(handle));
    #elif defined(__APPLE__)
        return static_cast<T>(glfwGetCocoaWindow(handle));
    #else
        return nullptr;
    #endif
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ #### END TEMPLATES #### ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■