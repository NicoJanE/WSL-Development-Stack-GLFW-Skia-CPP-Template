#include "GLFW/glfw3.h"
#define SK_GANESH
#define SK_GL
//#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/ganesh/GrBackendSurface.h"
//#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/GrDirectContext.h" //
//#include "include/gpu/gl/GrGLInterface.h"
#include "include/gpu/ganesh/gl/GrGLInterface.h"
//#include "include/gpu/gl/GrGLAssembleInterface.h"
#include "include/gpu/ganesh/gl/GrGLAssembleInterface.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"
#include "include/core/SkGraphics.h"

#include <stdio.h>
#include <stdlib.h>

//uncomment the two lines below to enable correct color spaces
//#define GL_FRAMEBUFFER_SRGB 0x8DB9
//#define GL_SRGB8_ALPHA8 0x8C43

GrDirectContext* sContext = nullptr;
SkSurface* sSurface = nullptr;

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void* glfw_proc_forwarder(void*, const char* p) {
    return (void*)glfwGetProcAddress(p);
}

void init_skia(int w, int h) {
	auto interface = GrGLMakeNativeInterface();
	if (interface == nullptr) {
		//backup plan. see https://gist.github.com/ad8e/dd150b775ae6aa4d5cf1a092e4713add?permalink_comment_id=4680136#gistcomment-4680136
		//interface = GrGLMakeAssembledInterface(
		//	nullptr, (GrGLGetProc) * [](void*, const char* p) -> void* { return (void*)glfwGetProcAddress(p); })  ; // NOT work 1
		
		//interface = GrGLMakeAssembledInterface(nullptr, get_glfw_proc);		// NOT work 2
		interface = GrGLMakeAssembledInterface(nullptr, (GrGLGetProc)glfw_proc_forwarder); // DOES works

	}
	sContext = GrDirectContexts::MakeGL(interface).release();

	GrGLFramebufferInfo framebufferInfo;
	framebufferInfo.fFBOID = 0; // assume default framebuffer
	// We are always using OpenGL and we use RGBA8 internal format for both RGBA and BGRA configs in OpenGL.
	//(replace line below with this one to enable correct color spaces) framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
	framebufferInfo.fFormat = GL_RGBA8;

	SkColorType colorType = kRGBA_8888_SkColorType;
	GrBackendRenderTarget backendRenderTarget = GrBackendRenderTargets::MakeGL(w, h,
		0, // sample count
		0, // stencil bits
		framebufferInfo);

	//(replace line below with this one to enable correct color spaces) sSurface = SkSurfaces::WrapBackendRenderTarget(sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(), nullptr).release();
	sSurface = SkSurfaces::WrapBackendRenderTarget(sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr).release();
	if (sSurface == nullptr) abort();
}

void cleanup_skia() {
	delete sSurface;
	delete sContext;
}

const int kWidth = 960;
const int kHeight = 640;


int main(void) {
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//(uncomment to enable correct color spaces) glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
	glfwWindowHint(GLFW_STENCIL_BITS, 0);
	//glfwWindowHint(GLFW_ALPHA_BITS, 0);
	glfwWindowHint(GLFW_DEPTH_BITS, 0);

	window = glfwCreateWindow(kWidth, kHeight, "Simple example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	//(uncomment to enable correct color spaces) glEnable(GL_FRAMEBUFFER_SRGB);

	init_skia(kWidth, kHeight);

	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);

	// Draw to the surface via its SkCanvas.
	SkCanvas* canvas = sSurface->getCanvas(); // We don't manage this pointer's lifetime.

	while (!glfwWindowShouldClose(window)) {
		glfwWaitEvents();
		SkPaint paint;
        paint.setColor(SK_ColorWHITE);
        canvas->drawPaint(paint);
        paint.setColor(SK_ColorBLUE);
        canvas->drawRect({100, 200, 300, 500}, paint);
        sContext->flush();

		glfwSwapBuffers(window);
	}

	cleanup_skia();

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}