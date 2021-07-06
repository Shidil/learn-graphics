// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "base.h"
// clang-format on

int main() {
  GLFWwindow* window =
      create_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Texture");

  // origin (0, 0) at center
  float vertices[] = {
      -0.5f, -0.5f, 0.0f,  // left
      0.5f,  -0.5f, 0.0f,  // right
      0.0f,  0.5f,  0.0f   // top
  };

  // origin (0, 0) at bottom left
  float texCoords[] = {
      0.0f, 0.0f,  // left
      1.0f, 0.0f,  // right
      0.5f, 1.0f   // top
  };

  unsigned int VBO, VAO;

  unsigned int VBO, VAO;

  // Bind vertex array object
  glGenVertexArrays(1, &VAO);

  // Copy vertices in array buffer for use by OpenGL
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Set vertex attribute pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Unbind buffers and array objects
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // draw stuff
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set shader to be used
    // glUseProgram(shader);

    // Draw triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  terminate();
  return 0;
}
