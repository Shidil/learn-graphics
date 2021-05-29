#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "./base.h"

const char* vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragment_shader_source =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
    "}\0";

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

int main() {
  GLFWwindow* window =
      init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Triangle");

  if (window == NULL) {
    printf("GL Context creation failed. No window created");
    terminate();
    return -1;
  }

  // Shader
  int success;
  char infoLog[512];
  shader vertex_shader = create_vert_shader(vertex_shader_source);
  shader fragment_shader = create_frag_shader(fragment_shader_source);
  shader_pgm shader_program = program_shader(vertex_shader, fragment_shader);

  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
    printf("Error::SHADER::VERTEX::COMPILATION_FAILED \n %s", infoLog);
  }

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
    printf("Error::SHADER::FRAGMENT::COMPILATION_FAILED \n %s", infoLog);
  }

  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
    printf("Error::SHADER::PROGRAM::LINKING_FAILED \n %s", infoLog);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  // Draw input
  float vertices[] = {
      -0.5f, -0.5f, 0.0f,  // left
      0.5f,  -0.5f,  0.0f,  // right
      0.0f,  0.5f,  0.0f,  // top
  };

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
    // input handling
    processInput(window);

    // draw stuff
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set shader to be used
    glUseProgram(shader_program);

    // Draw triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // De allocate
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shader_program);

  terminate();
  return 0;
}
