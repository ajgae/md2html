
#include "init.h"
#include "block.h"

#define M2H_RETVAL_SUCCESS 0
#define M2H_RETVAL_EXECFAIL 1
#define M2H_RETVAL_INITFAIL 2

int main(int argc, char **argv) {
  config_t cfg;
  if (!init_config(&cfg, argc, argv)) {
    return M2H_RETVAL_INITFAIL;
  }

  context_t ctx;
  init_context(&ctx);

  int fd = open(cfg.file_name, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "Error: could not open file for reading\n");
    return M2H_RETVAL_EXECFAIL;
  }

  // get file attributes
  struct stat stat;
  if (fstat(fd, &stat) == -1) {
    fprintf(stderr, "Error: could not get file attributes\n");
    return M2H_RETVAL_EXECFAIL;
  }
  ctx.filesize = stat.st_size;

  // memory map the file for reading
  char *map = mmap(NULL, ctx.filesize, PROT_READ, MAP_PRIVATE, fd, 0);
  if (map == MAP_FAILED) {
    fprintf(stderr, "Error: could not memory map file\n");
    return M2H_RETVAL_EXECFAIL;
  }
  ctx.map = map;

  if (close(fd) == -1) {
    fprintf(stderr, "Error: could not close file\n");
    return M2H_RETVAL_EXECFAIL;
  }

  // call parse, where everything happens
  if (!parse(&ctx)) {
    return M2H_RETVAL_EXECFAIL;
  }

  munmap(map, ctx.filesize);
  return M2H_RETVAL_SUCCESS;
}
