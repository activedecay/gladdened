#ifndef __o_shaders_h
#define __o_shaders_h

#include "gladdened.h"

#define BUFFER_OFFSET(a) ((void*)(a))

typedef struct {
  GLenum type;
  const char *filename;
  GLuint shader;
} ShaderInfo;

GLuint load_shaders(ShaderInfo *);
static const GLchar *read_shader(const char *filename);

#endif // __o_shaders_h
