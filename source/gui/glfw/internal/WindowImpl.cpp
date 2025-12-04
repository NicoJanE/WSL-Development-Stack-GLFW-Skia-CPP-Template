/*
 ────────────────────────────────────────── License ─────────────────────────────────────────────────
 This file is part of the Stack: GLFW-Skia-CPP-Template
 Copyright (c) 2025 Nico Jan Eelhart.
 Licensed under the MIT License. See the LICENSE.md file in the root directory of  this source tree.
───────────────────────────────────────────────────────────────────────────────────────────────────── */



#include "core/internal/group-common-externals.h"       // Project-defined common internal umbrella headers 
#include "gui/glfw/internal/WindowImpl.h"               // Internal headers for application implementation
                                                        // Public API headers for the application
#include "gui-control/gui/glfw/app_window.h"            // TODO Currently only for EventStrategy  REFACTOR ? (specific header in public include)


namespace myproject::gui::glfw 

{

// Implementation
// --------------------------------------------- CLASS -------------------------------------------------

    // CTOR creating the internal handle (GLFWwindow*)
    WindowImpl::WindowImpl(int width, int height, const char* title)
    {            
            if (!glfwInit()) {
                // Handle init failure, maybe throw or exit
                std::cerr << "Failed to initialize GLFW\n";
                std::exit(EXIT_FAILURE);
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_STENCIL_BITS, 0);
            glfwWindowHint(GLFW_DEPTH_BITS, 0);

            handle= glfwCreateWindow(width, height, title, nullptr, nullptr);
            if (!handle) {
                glfwTerminate();
                std::cerr << "Failed to create GLFW window\n";
                std::exit(EXIT_FAILURE);
            }

            glfwMakeContextCurrent(handle);
            glfwSwapInterval(1);
            
            // CRUCIAL: store pointer so callbacks can map window -> instance FOR ProcessEvents BEGIN
            glfwSetWindowUserPointer(handle, this);
            
            
            // Enable sRGB framebuffer if you want:
            // glEnable(GL_FRAMEBUFFER_SRGB);

    }

    // DTOR, destroying the internal handle(GLFWwindow*)
    WindowImpl::~WindowImpl()
    { 
        if (handle)
        {
            glfwDestroyWindow(handle);
            handle= nullptr;
        }
    }

    // =================================== GLFW CALLBACK SETUP ===================================
    // WindowImpl::Setup_GLFW_Callbacks
    //
    // Notes on callback styles:
    //
    // 1) Free C-style function (always works)
    //    - Fully compatible with C libraries.
    //    - Use glfwGetWindowUserPointer to map back to the instance:
    //      auto* impl = static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
    //
    // 2) Static member function
    //    - Encapsulated in the class, keeps namespace clean.
    //    - Still compatible with GLFW C function pointer signature.
    //    - Must use glfwGetWindowUserPointer to access instance state.
    //
    // 3) Inline lambda (NO captures!)
    //    - Convenient for small, local callback logic.
    //    - Cannot capture local variables because GLFW expects a plain function pointer.
    //    - Example:
    //      glfwSetCharCallback(handle, [](GLFWwindow* w, unsigned int c) {
    //          auto* impl = static_cast<WindowImpl*>(glfwGetWindowUserPointer(w));
    //          if (impl) impl->OnCharInput(c);
    //      });
    //
    // Practical disadvantages:
    // - Free function: lives outside the class (less OO-friendly)
    // - Static member: slightly more verbose than free function
    // - Lambda: cannot capture local variables; repeated logic is harder to reuse
    //
    // =========================================================================================
    //
    /// @brief Callbacks for GLFW
    void WindowImpl::Setup_GLFW_Callbacks() 
    {    
        glfwSetErrorCallback(error_callback);
        glfwSetKeyCallback(handle, clb_MainWindow_KeyEvents);
        glfwSetCharCallback(handle, clb_MainWindow_CharsEvents);  


        // Inline lambda alternative (uncomment to use):
        // glfwSetCharCallback(handle, [](GLFWwindow* w, unsigned int c){
        //     auto* impl = static_cast<WindowImpl*>(glfwGetWindowUserPointer(w));
        //     if (impl) impl->OnCharInput(c);
        // });
    }


    /// @brief Process GLFW events using the specified strategy.
    /// @param strategy Determines whether to poll or wait for events:
    ///        - EventStrategy::Poll : Non-blocking, returns immediately after processing all pending events.
    ///        - EventStrategy::Wait : Blocking, waits until at least one event is available.
    ///
    /// @note To add a new event:
    ///       1) Define a GLFW callback (e.g., key, mouse, character, window resize) in WindowImpl or as a free function.
    ///       2) Set the callback using the appropriate glfwSet*Callback function in Setup_GLFW_Callbacks().
    ///       3) Optionally, within the callback, forward the event to higher-level code (e.g., parent class) or store it for processing here.
    ///       4) If you want custom processing inside ProcessEvents(), you could iterate over a queue of stored events after polling:
    ///          ```cpp
    ///          while (!eventQueue.empty()) {
    ///              auto ev = eventQueue.front();
    ///              eventQueue.pop();
    ///              HandleEvent(ev); // your own event handler
    ///          }
    ///          ```
    void    WindowImpl::ProcessEvents(EventStrategy strategy)
    {
        strategy == EventStrategy::Poll ? glfwPollEvents() : glfwWaitEvents();

        /*
        If you don’t use a queue, your callbacks (OnKey, OnChar, etc.) are executed immediately when GLFW dispatches an event.
        (inside the GLFW event loop see main.)

        By queuing, you defer handling until ProcessEvents() runs.
        That means:
            Callbacks only record events (push into queue).
            ProcessEvents() is the single place where you handle them.
            queue determins th order
            This gives you full control: you can process events at the right time in your game loop, in order, maybe even replay them later, or filter/transform them.    
        */

        // FOR ProcessEvents BEGIN
        // Process queued events
        while (!eventQueue.empty())
        {
            auto ev = eventQueue.front();
            eventQueue.pop();

            if (std::holds_alternative<KeyEvent>(ev))
            {
                const KeyEvent& e = std::get<KeyEvent>(ev);
                std::cout << "Key event: key=" << e.key
                        << " action=" << e.action
                        << " mods=" << e.mods << "\n";
            }
            else if (std::holds_alternative<CharEvent>(ev))
            {
                const CharEvent& e = std::get<CharEvent>(ev);
                std::cout << "Char event: " << static_cast<char>(e.codepoint) << "\n";
            }
            // else if (std::holds_alternative<std::monostate>(ev)) { } // ignore
        }
        // FOR ProcessEvents END
    }

// -------------------------------------- ### END CLASS ### --------------------------------------------

    

// ========================================= FREE FUNCTIONS ============================================


    // Error callback for GLFW
    // This function will be called by GLFW when an error occurs.
    void error_callback(int error, const char* description) 
    {
	    fputs(description, stderr);
    }

    // Key events for the main window, Hot keys, function keys, etc.
    void clb_MainWindow_KeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods) 
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

         //NJE HERE
        //auto* impl = static_cast<WindowImpl*>(glfwGetWindowUserPointer(window)); //WHY is impl nullptr ?
        //if (impl) impl->OnKey(key, action, mods);
    }


    // Character input callback for the main window, get user input text
    void clb_MainWindow_CharsEvents(GLFWwindow* window, unsigned int codepoint)
    {
        static char text_buffer[256];
        static int text_index = 0;

        if (text_index < sizeof(text_buffer) - 1) {
            text_buffer[text_index++] = (char)codepoint;        
            std::cout << "Text so far: " << text_buffer << std::endl;
        }
    }

// =================================== #### END FREE FUNCTIONS #### ====================================


}   // End namespace