
#include "init.h"

void usage(char **argv) {
  fprintf(stderr,
          "Usage: %s FILENAME\n"
          "Made by " M2H_AUTHOR ".\n",
          argv[0]);
}

bool init_config(config_t *cfg, int argc, char **argv) {
  if (argc < 2) {
    usage(argv);
    return false;
  }

  cfg->file_name = argv[1];;
  return true;
}
