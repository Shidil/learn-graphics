// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "files.h"

// clang-format on

typedef unsigned int shader;
typedef unsigned int shader_pgm;

shader create_vert_shader(const char* source);
shader create_frag_shader(const char* source);
shader link_shader(shader vert, shader frag);
shader_pgm create_shader_pgm(const char* vert, const char* frag);

shader_pgm load_shader_from_file(const char* vert, const char* frag);

void unload_shader(shader_pgm shader);

void use_shader(shader_pgm shader);
void set_uniform_float(shader_pgm shader, const char* name, float value);

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

shader_pgm link_shader(shader vert, shader frag) {
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
  // if file.errors ? then

  shader_pgm shader = create_shader_pgm(vert_file.contents, frag_file.contents);

  // cleanup
  unload_file(vert_file);
  unload_file(frag_file);

  return shader;
}

void unload_shader(shader_pgm shader) { glDeleteProgram(shader); }

void use_shader(shader_pgm shader) { glUseProgram(shader); }

void set_uniform_float(shader_pgm shader, const char* name, float value) {
  int location = glGetUniformLocation(shader, name);
  glUniform1f(location, value);
}
