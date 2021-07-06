#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>

#include "stb/stb_image.h"

typedef struct {
  int width, height, nrChannels;
  unsigned int texId;
} Texture;

Texture load_texture_from_file(const char* path) {
  Texture tex;

  unsigned char* data =
      stbi_load(path, &tex.width, &tex.height, &tex.nrChannels, 0);

  if (data) {
    // generate gl texture
    glGenTextures(1, &tex.texId);
    glBindTexture(GL_TEXTURE_2D, tex.texId);

    // repeat texture along x and y axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    // texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.width, tex.height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  // free image file data
  stbi_image_free(data);

  return tex;
}

void unload_texture(Texture tex) {}

void use_texture(Texture tex) { glBindTexture(GL_TEXTURE_2D, tex.texId); }
