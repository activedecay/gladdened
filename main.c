#include <stdlib.h>
#include <stdio.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main() {
  if (!glfwInit()) {
    fprintf(stderr, "can't init glfw");
    exit(EXIT_FAILURE);
  }
}