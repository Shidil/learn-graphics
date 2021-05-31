#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base.h"

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

int main(void) {
  GLFWwindow* window =
      create_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Shaders");

  // resources
  shader_pgm shader = load_shader_from_file("../shaders/basic-vertex.glsl",
                                            "../shaders/basic-fragment.glsl");

  // Data for drawing
  float vertices[] = {
      -0.5f, 0.5f,  0.0f,  // top left
      -0.5f, -0.5f, 0.0f,  // bottom left
      0.5f,  -0.5f, 0.0f,  // bottom right
      0.5f,  0.5f,  0.0f,  // top right
  };
  unsigned int indices[] = {
      0, 1, 2,  // first triangle
      0, 3, 2   // second triangle
  };

  unsigned int VBO, VAO, EBO;

  // Bind vertex array object
  glGenVertexArrays(1, &VAO);

  // Copy vertices in array buffer for use by OpenGL
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Set indices array in element buffer
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // Set vertex attribute pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Unbind buffers and array objects
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // input handling
    processInput(window);

    // draw stuff
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set shader to be used
    glUseProgram(shader);

    // Draw triangle
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // De allocate
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shader);

  terminate();
  return 0;
}
