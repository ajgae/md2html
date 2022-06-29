
#include <stdio.h>
#include <sys/mman.h> // mmap syscall

#include "config.h"
#include "blocks.h"
#include "common.h"

void usage(char **argv) {
  fprintf(stderr,
          "Usage: %s FILENAME\n"
          "Made by " M2H_AUTHOR ".\n",
          argv[0]);
}

int main(int argc, char **argv) {
  config_t cfg;
  if (!init_config(&cfg, argc, argv)) {
    usage(argv);
    return M2H_RETVAL_INITFAIL;
  }

  context_t ctx;
  if (!init_context(&ctx, &cfg)) {
    return M2H_RETVAL_INITFAIL;
  }

  // call parse, where everything happens
  if (!blocks(&ctx)) {
    return M2H_RETVAL_EXECFAIL;
  }

  // TODO move to a context-related function
  munmap(ctx.file_mmap, ctx.file_size);
  return M2H_RETVAL_SUCCESS;
}

