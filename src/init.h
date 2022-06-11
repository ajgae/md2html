#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define M2H_AUTHOR "ajgae"

typedef struct _context_t context_t;

struct _context_t {
  char *file_name;
};

void usage(char **argv);
context_t *init_context(int argc, char **argv);
