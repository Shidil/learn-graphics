#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "files.h"

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500

typedef unsigned int shader;
typedef unsigned int shader_pgm;

const char* basic_vert_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* basic_frag_shader_source =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
    "}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

GLFWwindow* create_window(int width, int height, char* title) {
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

shader link_shader(shader vert, shader frag) {
  shader program = glCreateProgram();

  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);

  return program;
}

shader_pgm create_shader_pgm(const char* vert_source, const char* frag_source) {
  int success;
  char infoLog[512];

  shader vertex_shader = create_vert_shader(vert_source);
  shader fragment_shader = create_frag_shader(frag_source);

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

  shader_pgm shader_program = link_shader(vertex_shader, fragment_shader);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
    printf("Error::SHADER::PROGRAM::LINKING_FAILED \n %s", infoLog);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return shader_program;
}

shader_pgm load_shader_from_file(const char* vert_shader_file,
                                 const char* frag_shader_file) {
  File vert_file = read_from_file(vert_shader_file);
  File frag_file = read_from_file(frag_shader_file);

  // TODO check errors and validate

  shader_pgm shader = create_shader_pgm(vert_file.contents, frag_file.contents);
  unload_file(vert_file);
  unload_file(frag_file);

  return shader;
}

shader_pgm get_basic_shader() {
  return create_shader_pgm(basic_vert_shader_source, basic_frag_shader_source);
}

void terminate() { glfwTerminate(); }
