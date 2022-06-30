
#include <stdio.h>

#include "header.h"

void header(char *start, size_t len, size_t num_hash) {
  int header_type = num_hash < 7 ? num_hash : 6;
  fprintf(stdout, "<h%d>", header_type);
  for (size_t i = 0; i < len; ++i) {
    fputc(*(start + i), stdout);
  }
  fprintf(stdout, "</h%d>\n", header_type);
}

