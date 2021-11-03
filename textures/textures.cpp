#include <stdlib.h>
#include <stdio.h>

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>

#include <WindowSurface.h>
#include <EGLUtils.h>

using namespace android;

int main(int argc, char** argv)
{
    EGLint configAttribs[] = {
         EGL_DEPTH_SIZE, 0,
         EGL_NONE
     };
     
     EGLint majorVersion;
     EGLint minorVersion;
     EGLContext context;
     EGLConfig config;
     EGLSurface surface;
     EGLint w, h;
     EGLDisplay dpy;

     WindowSurface windowSurface;
     EGLNativeWindowType window = windowSurface.getSurface();
     
     dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
     eglInitialize(dpy, &majorVersion, &minorVersion);
          
     status_t err = EGLUtils::selectConfigForNativeWindow(
             dpy, configAttribs, window, &config);
     if (err) {
         fprintf(stderr, "couldn't find an EGLConfig matching the screen format\n");
         return 0;
     }

     surface = eglCreateWindowSurface(dpy, config, window, NULL);
     context = eglCreateContext(dpy, config, NULL, NULL);
     eglMakeCurrent(dpy, surface, surface, context);   
     eglQuerySurface(dpy, surface, EGL_WIDTH, &w);
     eglQuerySurface(dpy, surface, EGL_HEIGHT, &h);
     GLint dim = w<h ? w : h;


     GLint crop[4] = { 0, 4, 4, -4 };
     glBindTexture(GL_TEXTURE_2D, 0);
     glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_CROP_RECT_OES, crop);
     glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
     glEnable(GL_TEXTURE_2D);
     glColor4f(1,1,1,1);

     // packing is always 4
     uint8_t t8[]  = { 
             0x00, 0x55, 0x00, 0x55, 
             0xAA, 0xFF, 0xAA, 0xFF,
             0x00, 0x55, 0x00, 0x55, 
             0xAA, 0xFF, 0xAA, 0xFF  };

     uint16_t t16[]  = { 
             0x0000, 0x5555, 0x0000, 0x5555, 
             0xAAAA, 0xFFFF, 0xAAAA, 0xFFFF,
             0x0000, 0x5555, 0x0000, 0x5555, 
             0xAAAA, 0xFFFF, 0xAAAA, 0xFFFF  };

     uint16_t t5551[]  = { 
             0x0000, 0xFFFF, 0x0000, 0xFFFF, 
             0xFFFF, 0x0000, 0xFFFF, 0x0000,
             0x0000, 0xFFFF, 0x0000, 0xFFFF, 
             0xFFFF, 0x0000, 0xFFFF, 0x0000  };

     uint32_t t32[]  = { 
             0xFF000000, 0xFF0000FF, 0xFF00FF00, 0xFFFF0000, 
             0xFF00FF00, 0xFFFF0000, 0xFF000000, 0xFF0000FF, 
             0xFF00FFFF, 0xFF00FF00, 0x00FF00FF, 0xFFFFFF00, 
             0xFF000000, 0xFFFF00FF, 0xFF00FFFF, 0xFFFFFFFF
     };


     glClear(GL_COLOR_BUFFER_BIT);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 4, 4, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, t8);
     glDrawTexiOES(0, 0, 0, dim/2, dim/2);

     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, t16);
     glDrawTexiOES(dim/2, 0, 0, dim/2, dim/2);

     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, t16);
     glDrawTexiOES(0, dim/2, 0, dim/2, dim/2);

     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, t32);
     glDrawTexiOES(dim/2, dim/2, 0, dim/2, dim/2);

     eglSwapBuffers(dpy, surface);

     sleep(2);      // so you have a chance to admire it
     return 0;
}
