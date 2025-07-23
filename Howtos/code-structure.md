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

    include/
      myproject/                # Public headers (API-facing)
        gui/
          glfw/
            window.h            # Public wrapper for GLFW window
          skia/
            canvas.h            # Public wrapper for Skia rendering

    src/
      core/                     # Business logic (app/game/backend logic)
      gui/
        glfw/
          window.cpp            # Implements GUI::GLFW::Window
          internal_helpers.h    # Internal header, private to GLFW backend
          internal/             # OR    
            helpers.h           # Internal header, private to GLFW backend
        skia/
          canvas.cpp            # Implements GUI::Skia::Canvas
          internal/             # Optional: subdir for private headers

------------------------------------------------------------------------------

## Purpose and Usage

- `include/myproject/` contains **public headers** defining the external API.
  These are meant to be used by the rest of the project or by external users if this becomes a library.

- `src/` contains all implementation code and private headers.
  Internal files should not be exposed to consumers of the library/application. **This folder typically does not contain any files**,  headers are organized into subdirectories (e.g., gui/glfw/, gui/skia/) that mirror the namespace structure.

- Internal headers such as `internal_helpers.h` should be placed in `src/`:
    - Either directly alongside the `.cpp` that uses them
    - Or inside an `internal/` folder for organization

- Public headers should **not expose raw backend types**
  (e.g., `GLFWwindow*`, Skia types). Use clean abstractions or the **PIMPL idiom** (*hide implementation from public headers, Reduce compile-time dependencies,Improve encapsulation/binary compatibility* ).

- Folder structure mirrors the C++ namespace:
  `myproject::gui::glfw::Window` → `include/myproject/gui/glfw/window.h`

------------------------------------------------------------------------------

## CMake Integration

- Add `include/` to the **public include path**:
  
  ```
  cmake
  target_include_directories(my_target PUBLIC ${CMAKE_SOURCE_DIR}/include)
  target_include_directories(my_target PRIVATE ${CMAKE_SOURCE_DIR}/src)
  ```