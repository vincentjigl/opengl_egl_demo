#ifndef OPENGL_TESTS_WINDOWSURFACE_H
#define OPENGL_TESTS_WINDOWSURFACE_H

#include <gui/SurfaceControl.h>

#include <EGL/egl.h>

namespace android {

/*
 * A window that covers the entire display surface.
 *
 * The window is destroyed when this object is destroyed, so don't try
 * to use the surface after that point.
 */
class WindowSurface {
public:
    // Creates the window.
    WindowSurface();

    // Retrieves a handle to the window.
    EGLNativeWindowType getSurface() const;

private:
    WindowSurface(const WindowSurface&);
    WindowSurface& operator=(const WindowSurface&);

    sp<SurfaceControl> mSurfaceControl;
};

} // namespace android

#endif /* OPENGL_TESTS_WINDOWSURFACE_H */
