#include "gladdened.h"

/* vertex array objects */
enum VAO_IDs {
  Triangles, NumVAOs
};
enum Buffer_IDs {
  VertexBuffer, NumBuffers
};
GLuint VAOs[NumVAOs];

/* texture objects */
enum TO_IDs {
  Fonts, NumTOs
};
enum Texture_IDs {
  FontBuffer, NumTextures
};
GLuint TOs[NumTOs];

enum Attrib_IDs {
  vPosition = 0
};


/** buffers reserved with glCreateBuffers (empty/reserved)
 *  increase buffer count with Buffer_IDs
 *  enum values are names of buffers to use
 *  to allocate storage with
 *  glNamedBufferStorage
 *  or if these two calls are chained together
 *  glBindBuffer glBufferStorage
 */
GLuint Buffers[NumBuffers];
GLuint Textures[NumTextures];


int main() {
  if (!glfwInit()) {
    fprintf(stderr, "can't init glfw");
    exit(EXIT_FAILURE);
  }
  bool fullscreen = false;

  int width = 444, height = 444;
  const char *title = "0";
  GLFWmonitor *monitor = fullscreen ? glfwGetPrimaryMonitor()
                         /* otherwise */ : 0;
  GLFWwindow *window;

  window = glfwCreateWindow(width,
                            height,
                            title,
                            monitor,
                            0);
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);

  glfwSetKeyCallback(window, on_key);
  glfwSetCharCallback(window, on_char);
  glfwSetWindowSizeCallback(window, on_resize);
  glfwSetMouseButtonCallback(window, on_mouse_button);
  glfwSetCursorPosCallback(window, on_cursor_pos);
  glfwSetCursorEnterCallback(window, on_cursor_enter);




/* todo an attempt was made to create a texture

  GLfloat *texture;
  int textureSize = 4096 * 8;
  int e = posix_memalign((void **) &texture, 4096, textureSize);
  if (e)
    error(1, errno, "could not alloc texture");

  glGenTextures(NumTextures, TOs);
  glBindTexture(GL_TEXTURE_BUFFER, TOs[FontBuffer]);

  glCreateTextures(NumTextures, Textures);
  glNamedBufferStorage(Textures[FontBuffer], textureSize, texture, GL_DYNAMIC_STORAGE_BIT);
*/






  glGenVertexArrays(NumVAOs, VAOs);
  glBindVertexArray(VAOs[Triangles]);

  /* draw geometry across the whole screen until
   * todo figure out how to generate geometry without
   *  packing some pixel buffer with data we know is always
   *  trying to fill the whole window, or we can use this as
   *  some kind of margin thing. */

  GLfloat vertices[6][2] = {
    {-1.f, -1.f},
    {1.f,  -1.f},
    {-1.f, 1.f},  // Triangle 1
    {1.f,  -1.f},
    {1.f,  1.f},
    {-1.f, 1.f}   // Triangle 2
  };

  /* todo why do we need vertices at all?
  uint cellWidth = 100, cellHeight = 150;
  uint cellCountX = width / cellWidth;
  uint cellCountY = height / cellHeight;
  GLfloat vertices[cellCountX * cellCountY * 4];*/

  glCreateBuffers(NumBuffers, Buffers);
  glBindBuffer(GL_ARRAY_BUFFER, Buffers[VertexBuffer]);
  glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

  ShaderInfo shaders[3] = {{GL_VERTEX_SHADER,   "shaders/triangle.vert"},
                           {GL_FRAGMENT_SHADER, "shaders/triangle.frag"},
                           {0}};
  GLuint program = load_shaders(shaders);
  glUseProgram(program);

  glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                        GL_FALSE, 0, BUFFER_OFFSET(0));
  glEnableVertexAttribArray(vPosition);

  do {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);

    glfwPollEvents();
  } while (!glfwWindowShouldClose(window));
  glfwDestroyWindow(window);
}

void on_key(GLFWwindow *window, int key, int scancode, int action, int mods) {}

void on_char(GLFWwindow *window, unsigned int codepoint) {
  glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void on_resize(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void on_mouse_button(GLFWwindow *window, int button, int action, int mods) {}

void on_cursor_pos(GLFWwindow *window, double xpos, double ypos) {}

void on_cursor_enter(GLFWwindow *window, int entered) {}
