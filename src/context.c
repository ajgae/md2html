
#include "context.h"

#include <stdio.h>
#include <sys/fcntl.h> // open syscall
#include <sys/stat.h> // fstat syscall
#include <sys/mman.h> // mmap syscall

bool init_context(context_t *ctx, config_t const *cfg) {
  int fd = open(cfg->file_name, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "Error: could not open file for reading\n");
    return false;
  }

  // get file attributes
  struct stat stat;
  if (fstat(fd, &stat) == -1) {
    fprintf(stderr, "Error: could not get file attributes\n");
    return false;
  }
  ctx->file_size = stat.st_size;

  // memory map the file for reading
  char *map = mmap(NULL, ctx->file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (map == MAP_FAILED) {
    fprintf(stderr, "Error: could not memory map file\n");
    return false;
  }
  ctx->file_mmap = map;

  if (close(fd) == -1) {
    fprintf(stderr, "Error: could not close file\n");
    return false;
  }

  return true;
}

