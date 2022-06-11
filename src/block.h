#pragma once

#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h> // open
#include <stdio.h>
#include <sys/stat.h> // stat
#include <sys/mman.h> // mmap

#include "init.h"
#include "context.h"

bool run(config_t *config);
void close_block(context_t *context);
void close_inline_styles(context_t *context);
