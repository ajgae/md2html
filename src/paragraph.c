
#include "paragraph.h"

#include <stdio.h>

void paragraph(char *start, size_t len) {
  fprintf(stdout, "<p>");
  for (size_t i = 0; i < len; ++i) {
    char c = *(start + i);
    if (c == '\n') {
      fputc(' ', stdout);
    } else {
      fputc(*(start + i), stdout);
    }
  }
  fprintf(stdout, "</p>\n");
}
