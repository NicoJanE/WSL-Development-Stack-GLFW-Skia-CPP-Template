/*
─────────────────────────────────────────── License ─────────────────────────────────────────────────
 This file is part of the Stack: GLFW-Skia-CPP-Template
 Copyright (c) 2025 Nico Jan Eelhart.
 Licensed under the MIT License. See the LICENSE.md file in the root directory of  this source tree.
───────────────────────────────────────────────────────────────────────────────────────────────────── 
*/


// ──────────────────────────────────────────────────────────────────────────────────────────────────
//  Grouped External Library Header File
// ──────────────────────────────────────────────────────────────────────────────────────────────────
//
//  🌟 Purpose: Shared platform + foundation setup header.
//              Provides a centralized include point for third-party libraries
//              and standard C++ library headers commonly used across the project.
//
//  💫 Usage:   Include this file in implementation files or group headers that require
//              access to foundational system interfaces and external APIs.
//
//  🧩 Libraries Included:
//              🧩 GLFW    (Windowing and input)
//              🧩 OpenGL  (Graphics context + hardware acceleration)
//              🧩 Standard C++ Library (Core utilities and facilities)
//              🧩 *Optional* Skia (2D graphics abstraction)
//
//              ⚠️ Remark: Skia headers are currently grouped into sub-headers like:
//                         'group-skia_core.h' and 'group-skia_gpu.h'.
//                         These are included directly in application-specific files.
//
//                         While it is *possible* to include such group headers here,
//                         this file is intentionally kept “main and lean”.
//                         (See also Note 2)
//
//  ⚠️ Notes:
//      1. This file does not define any project-specific symbols.
//         It exists purely for convenience and consistency across modules.
//
//      2. This file may be split into more specific group headers (e.g., platform
//         vs stdlib) as the project evolves and subsystem boundaries become more
//         distinct.



#pragma once


/// GLFW Library
// ──────────────────────────────────────────────────────────────────────────────────────
#include <GLFW/glfw3.h>

/// OS specific includes and functions
// ──────────────────────────────────────────────────────────────────────────────────────
#include "os_platform.h"


/// Skia Library (see remark in top description)
// ──────────────────────────────────────────────────────────────────────────────────────


/// Standard C++ Library (core, safe subset)
// ──────────────────────────────────────────────────────────────────────────────────────
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>

#include <memory>
#include <utility>
#include <type_traits>
#include <optional>

#include <vector>
#include <array>
#include <string>
#include <type_traits>


