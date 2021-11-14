#ifndef g_glfw_h
#define g_glfw_h

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

void on_key(GLFWwindow* window, int key, int scancode, int action, int mods); /* glfwSetKeyCallback */
void on_char(GLFWwindow* window, unsigned int codepoint); /* glfwSetCharCallback */
void on_resize(GLFWwindow* window, int width, int height); /* glfwSetWindowSizeCallback */
void on_mouse_button(GLFWwindow* window, int button, int action, int mods); /* glfwSetMouseButtonCallback */
void on_cursor_pos(GLFWwindow* window, double xpos, double ypos); /* glfwSetCursorPosCallback */
void on_cursor_enter(GLFWwindow* window, int entered); /* glfwSetCursorEnterCallback */

#endif // g_glfw_h