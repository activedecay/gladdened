#include "o_shaders.h"

const GLchar * read_shader(const char *filename) {
#ifdef WIN32
  FILE* infile;
  fopen_s( &infile, filename, "rb" );
#else
  FILE *infile = fopen(filename, "rb");
#endif // WIN32

  if (!infile) {
#ifdef _DEBUG
    fprintf(stderr, "Unable to open file %s", filename);
#endif /* _DEBUG */
    return NULL;
  }

  fseek(infile, 0, SEEK_END);
  long len = ftell(infile);
  fseek(infile, 0, SEEK_SET);

  GLchar *source = malloc(len + 1);

  fread(source, 1, len, infile);
  fclose(infile);

  source[len] = 0;

  return source;
}

GLuint load_shaders(ShaderInfo *shaders) {
  if (shaders == NULL) { return 0; }

  GLuint program = glCreateProgram();

  ShaderInfo *entry = shaders;
  while (entry->type != GL_NONE) {
    GLuint shader = glCreateShader(entry->type);

    entry->shader = shader;

    const GLchar *source = read_shader(entry->filename);
    if (source == NULL) {
      for (entry = shaders; entry->type != GL_NONE; ++entry) {
        glDeleteShader(entry->shader);
        entry->shader = 0;
      }

      return 0;
    }

    glShaderSource(shader, 1, &source, NULL);
    free((void *) source);

    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
#ifdef _DEBUG
      GLsizei len;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
      GLchar *log = malloc(len + 1);
      glGetShaderInfoLog(shader, len, &len, log);
      fprintf(stderr, "Shader compilation failed %s", log);
      free(log);
#endif /* _DEBUG */

      return 0;
    }

    glAttachShader(program, shader);

    ++entry;
  }

  glLinkProgram(program);

  GLint linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);
  if (!linked) {
#ifdef _DEBUG
    GLsizei len;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

    GLchar *log = malloc(len + 1);
    glGetProgramInfoLog(program, len, &len, log);
    fprintf(stderr, "Shader linking failed: %s", log);
    free(log);
#endif /* _DEBUG */

    for (entry = shaders; entry->type != GL_NONE; ++entry) {
      glDeleteShader(entry->shader);
      entry->shader = 0;
    }

    return 0;
  }

  return program;
}
