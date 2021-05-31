#include <stdio.h>
#include <stdlib.h>

#define FILE_OK 0
#define FILE_READ_ERROR 1

typedef struct {
  char* contents;
  int error;
  size_t size;
} File;

/**
 * Read entire file contents as string in memory
 */
File read_from_file(const char* file_path) {
  char* buffer = 0;
  size_t length;
  FILE* f = fopen(file_path, "r");

  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);

    buffer = (char*)malloc(length + 1);

    if (buffer) {
      fread(buffer, 1, length, f);
    }

    fclose(f);
  }

  // file opened and read successfully
  // return \0 terminated string buffer
  if (buffer) {
    buffer[length] = '\0';

    return (File){
        buffer,
        FILE_OK,
        length,
    };
  }

  return (File){
      NULL,
      FILE_READ_ERROR,
      0,
  };
}

void unload_file(File f) { free(f.contents); }
