/*
 ────────────────────────────────────────── License ─────────────────────────────────────────────────
 This file is part of the Stack: GLFW-Skia-CPP-Template
 Copyright (c) 2025 Nico Jan Eelhart.
 Licensed under the MIT License. See the LICENSE.md file in the root directory of  this source tree.
───────────────────────────────────────────────────────────────────────────────────────────────────── */


// ──────────────────────────────────────────────────────────────────────────────────────────────────
//  Grouped Skia Core Header File
// ──────────────────────────────────────────────────────────────────────────────────────────────────
//
//  Library     : Skia
//  Module      : Core
//
//  💫 Usage    : Include this file in application headers or implementation files
//                that need access to Skia's core drawing APIs — such as SkCanvas,
//                SkSurface, and reference-counted infrastructure.
//
//  ⚠️ Notes:
//      - This file does not define any symbols of its own.
//        It exists purely to simplify and centralize external includes.
//
//      - For GPU-accelerated rendering, prefer including group-skia_gpu.h instead.
//        That header provides access to Ganesh and OpenGL integration.


#pragma once

#include "include/core/SkCanvas.h"
#include "include/core/SkRefCnt.h"
#include "include/core/SkSurface.h"
#include "include/core/SkColorSpace.h"
//#include "include/core/SkGraphics.h"  // for what




