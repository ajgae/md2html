
#include "init.h"

#include "common.h"

void usage(char **argv) {
  fprintf(stderr,
          "Usage: %s FILENAME\n"
          "Made by " M2H_AUTHOR ".\n",
          argv[0]);
}

config_t *init_config(int argc, char **argv) {
  if (argc < 2) {
    usage(argv);
    return NULL;
  }

  config_t *config = malloc(sizeof(config_t));
  config->file_name = argv[1];;

  return config;
}
