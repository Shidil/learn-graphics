#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define WINDOW_HEIGHT 450
#define WINDOW_WIDTH 800

typedef unsigned int shader;
typedef unsigned int shader_pgm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

GLFWwindow* init_window(int width, int height, char* title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

  if (window == NULL) {
    printf("Failed to create GLFW Window");
    return NULL;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD");

    return NULL;
  }

  return window;
}

shader create_vert_shader(const char* source) {
  shader shader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  return shader;
}

shader create_frag_shader(const char* source) {
  shader shader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  return shader;
}

shader_pgm program_shader(shader vert, shader frag) {
  shader_pgm program = glCreateProgram();

  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);

  return program;
}

void terminate() { glfwTerminate(); }
