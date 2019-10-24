#ifndef __SHADER_COMPILE_H__
#define __SHADER_COMPILE_H__

#include <epoxy/gl.h>

GLuint shader_compile(GLuint type, const GLchar *source, GLint length);

#endif
