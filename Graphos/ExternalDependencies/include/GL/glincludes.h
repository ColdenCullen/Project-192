#ifndef __GLINCLUDES
#define __GLINCLUDES

// GL include files
#if !( defined(__gl_h_) || defined(__GL_H__) || defined(__X_GL_H) || defined(__glext_h_) || defined(__GLEXT_H_) )
 #include <GL/glew.h>
#endif//__GL_H__/__GLEXT_H_

#if defined( _WIN32 )
 #include <GL/wglew.h>
 #include <GL/GL.h>
#elif defined( __APPLE__ )
 //#include <GL/glxew.h>
 #include <OpenGL/GL.h>
//#include <AppKit/NSOpenGL.h>
#endif//_WIN32

#endif//__GLINCLUDES

// Platform specific typedefs
#if defined( _WIN32 )
 typedef HDC GLDeviceContext;
 typedef HGLRC GLRenderContext;
#elif defined( __APPLE__ )
 //typedef NSOpenGLContext GLRenderContext;
 typedef unsigned int GLRenderContext;
#endif