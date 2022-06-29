
#include "config.h"

bool init_config(config_t *cfg, int argc, char **argv) {
  if (argc < 2 || argc > 3) {
    return false;
  }

  cfg->file_name = argv[1];
  return true;
}
