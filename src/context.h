#pragma once

#include <unistd.h> // size_t
#include <stdbool.h> // bool

#include "config.h"

typedef struct _context_t context_t;
struct _context_t {
  char *file_mmap;
  size_t file_size;
};

// Initialize the context from the given config.
bool init_context(context_t *ctx, config_t const *cfg);

