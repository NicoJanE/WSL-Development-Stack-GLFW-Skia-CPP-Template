/*
 ────────────────────────────────────────── License ─────────────────────────────────────────────────
 This file is part of the Stack: GLFW-Skia-CPP-Template
 Copyright (c) 2025 Nico Jan Eelhart.
 Licensed under the MIT License. See the LICENSE.md file in the root directory of  this source tree.
───────────────────────────────────────────────────────────────────────────────────────────────────── */


// ──────────────────────────────────────────────────────────────────────────────────────────────────
//  Grouped Skia GPU Header File
// ──────────────────────────────────────────────────────────────────────────────────────────────────
//
//  Library :   Skia
//  Module  :   gpu
//  Usage   :   Skia GPU context, wrapping OpenGL integration
//  Avoid   :   Use in modules that only draw to SkSurface via software 
//              rasterization, use group-skia_core.h instead.
//
//  This header groups together commonly used Skia GPU-related headers,
//  primarily from the Ganesh rendering backend.
//
//  Include this in your application-specific headers or implementation files
//  when you need access to GPU-accelerated rendering via Skia, such as
//  SkSurface (GPU-backed), GrDirectContext, or GL backend interfaces.
//
//  Note:
//      - This file does not define any symbols of its own.
//        It exists purely to simplify and centralize external includes.
//
//      - Skia's GPU interface is under active transition (Ganesh → Graphite),
//        and the include paths and build flags may vary across milestones.
//
//      - As of Skia M126 (mid-2025), the Ganesh backend is still used by default,
//        even if `skia_enable_gpu = false` is set in the build configuration.
//
//      - For `skia_enable_gpu = true`, some headers may move or change — see
//        Skia's release notes or BUILD.gn for up-to-date paths.
//
// See also: 'Ganesh Migration Notes' at the end of this file


#pragma once

// Skia GPU interfaces (Ganesh, GL-backed)
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/gpu/gl/GrGLAssembleInterface.h"

// Ganesh-specific headers (used in both GPU-disabled and enabled builds as of M126)
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"

// Note: In older or custom Skia builds, these may live in different paths:
//       #include "include/gpu/ganesh/GrBackendSurface.h"
//       #include "include/gpu/ganesh/GrDirectContext.h"
//       #include "include/gpu/ganesh/gl/GrGLInterface.h"
//       #include "include/gpu/ganesh/gl/GrGLAssembleInterface.h"






// ──────────────────────────────────────────────────────────────────────────────────────────────────
//  Ganesh Migration Notes (Skia GPU Backend Evolution)
// ──────────────────────────────────────────────────────────────────────────────────────────────────
//
//  ⚠️ Skia GPU support is currently in transition toward modular rendering backends.
//     Ganesh is still the default in most builds as of Milestone 126.
//
//  📦 Headers:
//      - Ganesh-related includes now live in `include/gpu/ganesh/`.
//      - Older paths (e.g., `include/gpu/GrDirectContext.h`) are stubs or aliases.
//
//  ⚙️ Build Implications:
//      - Without GPU support (`skia_enable_gpu = false`), some headers become no-ops.
//      - With GPU support enabled, use `ganesh/` paths explicitly.
//      - In some versions, enabling `skia_enable_gpu = true` may cause build errors.
//
//  💡 Tips:
//      - Refer to `gn/gn_args.gn` and `BUILD.gn` in your Skia checkout.
//      - Chromium M126+ may include fixes for Ganesh build issues.
//
//  🧠 Background: What is the “Ganesh Train”?
//
//      Ganesh is the traditional GPU backend for Skia (OpenGL/Vulkan/Metal).
//      Skia is migrating this backend to a more modular design:
//      
//          - Ganesh is being isolated into its own include path and namespace.
//          - New backends like Graphite (modern, Vulkan-style) are being developed.
//          - This modularity allows you to build Skia with only the backends you need.
//
//      In practical terms:
//          - Future Skia versions may *require* you to use ganesh/ headers directly.
//          - Legacy headers in `include/gpu/` will eventually be removed.
//          - Ganesh and Graphite can coexist in the same Skia build.
//
// ──────────────────────────────────────────────────────────────────────────────────────────────────

