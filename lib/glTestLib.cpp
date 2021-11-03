/*
 * Graphics Test Library
 */

#include <glTestLib.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "EGLUtils.h"

#include <utils/Log.h>

using namespace android;

void glTestPrintGLString(const char *name, GLenum s)
{
    const char *v = (const char *) glGetString(s);

    if (v == NULL) {
        printf("GL %s unknown", name);
    } else {
        printf("GL %s = %s", name, v);
    }
}

void glTestCheckEglError(const char* op, EGLBoolean returnVal)
{
    if (returnVal != EGL_TRUE) {
        printf("%s() returned %d", op, returnVal);
    }

    for (EGLint error = eglGetError(); error != EGL_SUCCESS; error = eglGetError()) {
        printf("after %s() eglError %s (0x%x)", op, EGLUtils::strerror(error), error);
    }
}

void glTestCheckGlError(const char* op)
{
    for (GLint error = glGetError(); error; error = glGetError()) {
        printf("after %s() glError (0x%x)", op, error);
    }
}

void glTestPrintEGLConfiguration(EGLDisplay dpy, EGLConfig config)
{

#define X(VAL) {VAL, #VAL}
    struct {EGLint attribute; const char* name;} names[] = {
    X(EGL_BUFFER_SIZE),
    X(EGL_ALPHA_SIZE),
    X(EGL_BLUE_SIZE),
    X(EGL_GREEN_SIZE),
    X(EGL_RED_SIZE),
    X(EGL_DEPTH_SIZE),
    X(EGL_STENCIL_SIZE),
    X(EGL_CONFIG_CAVEAT),
    X(EGL_CONFIG_ID),
    X(EGL_LEVEL),
    X(EGL_MAX_PBUFFER_HEIGHT),
    X(EGL_MAX_PBUFFER_PIXELS),
    X(EGL_MAX_PBUFFER_WIDTH),
    X(EGL_NATIVE_RENDERABLE),
    X(EGL_NATIVE_VISUAL_ID),
    X(EGL_NATIVE_VISUAL_TYPE),
    X(EGL_SAMPLES),
    X(EGL_SAMPLE_BUFFERS),
    X(EGL_SURFACE_TYPE),
    X(EGL_TRANSPARENT_TYPE),
    X(EGL_TRANSPARENT_RED_VALUE),
    X(EGL_TRANSPARENT_GREEN_VALUE),
    X(EGL_TRANSPARENT_BLUE_VALUE),
    X(EGL_BIND_TO_TEXTURE_RGB),
    X(EGL_BIND_TO_TEXTURE_RGBA),
    X(EGL_MIN_SWAP_INTERVAL),
    X(EGL_MAX_SWAP_INTERVAL),
    X(EGL_LUMINANCE_SIZE),
    X(EGL_ALPHA_MASK_SIZE),
    X(EGL_COLOR_BUFFER_TYPE),
    X(EGL_RENDERABLE_TYPE),
    X(EGL_CONFORMANT),
   };
#undef X

    for (size_t j = 0; j < sizeof(names) / sizeof(names[0]); j++) {
        EGLint value = -1;
        EGLint returnVal = eglGetConfigAttrib(dpy, config, names[j].attribute, &value);
        EGLint error = eglGetError();
        if (returnVal && error == EGL_SUCCESS) {
            printf(" %s: %d (%#x)", names[j].name, value, value);
        }
    }
    printf("");
}
