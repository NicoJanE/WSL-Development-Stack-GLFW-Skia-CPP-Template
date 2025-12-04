
/*
 ────────────────────────────────────────── License ─────────────────────────────────────────────────
 This file is part of the Stack: GLFW-Skia-CPP-Template
 Copyright (c) 2025 Nico Jan Eelhart.
 Licensed under the MIT License. See the LICENSE.md file in the root directory of  this source tree.
───────────────────────────────────────────────────────────────────────────────────────────────────── */


// ────────────────────────────────────────── General design rules ──────────────────────────────────
//
//  Please see [design and rules](./_design_glfw.md) for rules regarding GLFW implementations
//
// ──────────────────────────────────────────────────────────────────────────────────────────────────



#include "core/internal/group-common-externals.h"           // Core system includes and third-party libraries
#include "gui-control/gui/glfw/app_window.h"                // Public interface header
#include "internal/WindowImpl.h"                            // PIMPL implementation class - contains actual GLFW window logic

namespace myproject::gui::glfw 
{

// AppWindow Implementation (PIMPL Pattern)
// --------------------------------------------- CLASS -------------------------------------------------


    /// CTOR: Creates GLFW window with specified dimensions and title
    /// @param width  Window width in pixels
    /// @param height Window height in pixels  
    /// @param title  Window title string
    AppWindow::AppWindow(int width, int height, const char* title)    : impl( std::make_unique<WindowImpl>(width, height, title) ) 
    {}

    //DTOR
    AppWindow::~AppWindow() 
    {
        glfwTerminate();            // Only call if this is the main Window
    }

    WindowImpl* AppWindow::GetImpl() noexcept
    {
       return impl.get();
    }
    const WindowImpl* AppWindow::GetImpl() const noexcept
    {
        return impl.get();
    }


    // Setup GLFW callbacks (Consider virtual)
    void AppWindow::Setup_GLFW_Callbacks() 
    {    
        GetImpl()->Setup_GLFW_Callbacks();
    }

    void AppWindow::ProcessEvents(EventStrategy strategy)
    {
        GetImpl()->ProcessEvents(strategy);    
    }

    bool AppWindow::ShouldClose() const  
    { 
        return GetImpl()->ShouldClose(); 
    }

    GLFWwindow* AppWindow::GetWindowHandle()
    { 
        return GetImpl()->GetHandle(); 
    }

// -------------------------------------- ### END CLASS ### --------------------------------------------    



// ========================================= FREE FUNCTIONS ============================================
GLFWwindow*  GetWindowHandle(AppWindow&  window1)  
{  
     WindowImpl* impl=window1.GetImpl();
     return impl->GetHandle() ; 
}

// =================================== #### END FREE FUNCTIONS #### ====================================
	

} // namespace myproject::gui::glfw


