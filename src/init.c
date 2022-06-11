
#include "init.h"

#include "common.h"

void usage(char **argv) {
  fprintf(stderr,
          "Usage: %s FILENAME\n"
          "Made by " M2H_AUTHOR ".\n",
          argv[0]);
}

context_t *init_context(int argc, char **argv) {
  if (argc < 2) {
    usage(argv);
    return NULL;
  }

  context_t *context = malloc(sizeof(context_t));
  context->file_name = argv[1];;

  return context;
}
