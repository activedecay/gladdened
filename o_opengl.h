#ifndef o_opengl_h
#define o_opengl_h

#include "gladdened.h"

#define BUFFER_OFFSET(a) ((void*)(a))

typedef struct {
  GLenum type;
  const char *filename;
  GLuint shader;
} ShaderInfo;

GLuint load_shaders(ShaderInfo *);
static const GLchar *read_shader(const char *filename);


#endif // o_opengl_h