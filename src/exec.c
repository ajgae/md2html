
#include "exec.h"

bool exec_context(context_t *context) {
    int fd = open(context->file_name, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "Error: could not open file for reading\n");
    return false;
  }

  struct stat stat;
  if (fstat(fd, &stat) == -1) {
    fprintf(stderr, "Error: could not get file attributes\n");
    return false;
  }

  if (stat.st_blksize < stat.st_size) {
    fprintf(stderr, "Error: file too big (%ld, max %ld bytes)\n", stat.st_size,
            stat.st_blksize);
    return false;
  }

  char *file_buffer = malloc(stat.st_blksize);
  if (file_buffer == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    return false;
  }

  int bytes_read =
      read(fd, file_buffer, stat.st_size - 1); // -1 needed for null char
  if (bytes_read == -1) {
    fprintf(stderr, "Error: could not read bytes\n");
    return false;
  }
  
  printf("[file_buffer[bytes_read] = %c]\n", file_buffer[bytes_read]);
  file_buffer[bytes_read] = '\0'; // make sure it's null-terminated

  printf("[st_blksize = %ld]\n%s\n", stat.st_blksize, file_buffer);
  
  free(file_buffer);
  return true;
}
