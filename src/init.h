#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define M2H_AUTHOR "ajgae"

typedef struct _config_t config_t;

struct _config_t {
  char *file_name;
};

void usage(char **argv);
config_t *init_config(int argc, char **argv);
