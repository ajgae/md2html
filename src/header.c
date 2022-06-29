
#include <stdio.h>

#include "header.h"

void header(char *start, size_t len, size_t num_hash) {
  for (size_t i = 0; i < len; ++i) {
    fputc(*(start + i), stdout);
  }
}

