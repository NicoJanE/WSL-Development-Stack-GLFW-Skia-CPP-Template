
/*
 ────────────────────────────────────────── License ─────────────────────────────────────────────────
 This file is part of the Stack: GLFW-Skia-CPP-Template
 Copyright (c) 2025 Nico Jan Eelhart.
 Licensed under the MIT License. See the LICENSE.md file in the root directory of  this source tree.
───────────────────────────────────────────────────────────────────────────────────────────────────── */
#pragma once


/* ──────────────────────────────────────────────────────────────────────────────────────────────────
 🧠 PURPOSE:    Declares internal (non-public) GLFW window implementation details for the 
                application/library. This includes the WindowImpl class and private callback functions 
                used by AppWindow.

 📄 Description: 
     - Contains the PIMPL implementation of AppWindow.
     - Provides platform-specific configuration for native window access.
     - Declares internal GLFW callback functions for window events.
     - Not intended for direct use outside the GUI module implementation.
 ────────────────────────────────────────────────────────────────────────────────────────────────── */


#include "core/internal/group-common-externals.h"
#include <queue>    // FOR ProcessEvents BEGIN
#include <variant> // FOR ProcessEvents BEGIN


#define GL_FRAMEBUFFER_SRGB 0x8DB9
#define GL_SRGB8_ALPHA8 0x8C43


// Forwards
enum class EventStrategy; 

namespace myproject::gui::glfw 
{

    // FOR ProcessEvents BEGIN
   // Define (or move to a header) your internal event structures
    struct KeyEvent {
        int key;
        int scancode;
        int action;
        int mods;
    };
    struct CharEvent {
        unsigned int codepoint;
    };

    using WindowEvent = std::variant<KeyEvent, CharEvent>;
    // FOR ProcessEvents end

// Implementation class for App_Window (GLFW)
// --------------------------------------------- CLASS -------------------------------------------------

    class WindowImpl 
    {
        public:
            WindowImpl(int width, int height, const char* title);   // CTOR
            ~WindowImpl();                                          // DTOR     

            // Delete the copy move CTORS (rule of 5)
            WindowImpl( const WindowImpl&   right )         = delete;   // Copy Ctor
            WindowImpl( WindowImpl&&        right )         = delete;   // Move Ctor
            WindowImpl& operator=(const WindowImpl& right)  = delete;   // Assignment copy 
            WindowImpl& operator=(WindowImpl&&      right)  = delete;   // Assignment move


            inline  GLFWwindow* GetHandle() const noexcept      { return handle; }
            inline  bool        ShouldClose() const noexcept    { return glfwWindowShouldClose(handle); }


            void    Setup_GLFW_Callbacks(); 
            void    ProcessEvents(EventStrategy strategy);

        private:
            GLFWwindow* handle {nullptr};
            std::queue<WindowEvent> eventQueue;     // Event queue  // Helper to push events // FOR ProcessEvents

            // Helper to push events // FOR ProcessEvents
         inline void enqueue(WindowEvent ev) 
         {
            eventQueue.push(std::move(ev));
         }
         public:
         inline void OnKey(int key, int action, int mods) { eventQueue.push(KeyEvent{key, action, mods}); }
          // Helper to push events // FOR ProcessEvents END

    };

// -------------------------------------- ### END CLASS ### --------------------------------------------
	

// ========================================= FREE FUNCTIONS ============================================


    void error_callback(int error, const char* description);

    /// Key events for the main window, Hot keys, function keys, etc.
    void clb_MainWindow_KeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// Character input callback for the main window, get user input text
    void clb_MainWindow_CharsEvents(GLFWwindow* window, unsigned int codepoint);

// =================================== #### END FREE FUNCTIONS #### ====================================




} // namespace myproject::gui::glfw
