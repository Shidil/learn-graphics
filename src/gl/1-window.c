#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "./base.h"

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

int main() {
  GLFWwindow* window = init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Window");

  if (window == NULL) {
    printf("GL Context creation failed. No window created");
    terminate();
    return -1;
  }

  while (!glfwWindowShouldClose(window)) {
    // input
    processInput(window);

    // draw
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  terminate();
  return 0;
}
