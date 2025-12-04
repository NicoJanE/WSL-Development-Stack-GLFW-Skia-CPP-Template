/*
 ────────────────────────────────────────── License ─────────────────────────────────────────────────
 This file is part of the Stack: GLFW-Skia-CPP-Template
 Copyright (c) 2025 Nico Jan Eelhart.
 Licensed under the MIT License. See the LICENSE.md file in the root directory of  this source tree.
──────────────────────────────────────────────────────────────────────────────────────────────────── */

#pragma once

enum class EventStrategy { Poll, Wait };


 /* ──────────────────────────────────────────────────────────────────────────────────────────────────
 🧠 PURPOSE:  Declares the AppWindow class and related functions that form the application's
              public interface for managing a GLFW window.

 📄 Description This header exposes the C++ interface for creating, controlling, and querying
                GLFW windows within the application/library. It includes both the AppWindow
                class and free functions for window handle access.
 ───────────────────────────────────────────────────────────────────────────────────────────────────── */

namespace myproject::gui::glfw 
{

  // ⚡ Forward declaration source/gui/glfw/WindowImpl.h (in our namespace)
  class WindowImpl;  


  class AppWindow 
  {
    public:
      AppWindow(int width, int height, const char* title);
      ~AppWindow();


      const WindowImpl* GetImpl() const  noexcept ;
      WindowImpl*       GetImpl() noexcept;

      /// Add GLFW callbacks here
      void Setup_GLFW_Callbacks();

      /// Process event using PollEvents or WaitEvents
      ///   - poll (PollEvents) => without blocking.
      ///   - wait (WaitEvents) => blocks execution until an event occurs
      void  ProcessEvents(EventStrategy strategy = EventStrategy::Poll);
      
      bool  ShouldClose() const;
     
      GLFWwindow* GetWindowHandle();

    private:
      std::unique_ptr<WindowImpl>  impl = nullptr;  // PIMPL
  };


// Free Functions
// -------------------------------------------------------------------------------------------------------------------------------

// Get the GLFWwindow handler
GLFWwindow*  GetWindowHandle(const AppWindow&  window);



} // namespace myproject::gui::glfw


