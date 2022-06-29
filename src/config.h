#pragma once

#include <stdbool.h>

typedef struct _config_t config_t;

struct _config_t {
  char *file_name;
};

bool init_config(config_t *cfg, int argc, char **argv);

