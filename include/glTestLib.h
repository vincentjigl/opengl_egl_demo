#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "EGLUtils.h"

void glTestPrintGLString(const char *name, GLenum s);
void glTestCheckEglError(const char* op, EGLBoolean returnVal = EGL_TRUE);
void glTestCheckGlError(const char* op);
void glTestPrintEGLConfiguration(EGLDisplay dpy, EGLConfig config);
