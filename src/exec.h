#pragma once

#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h> // open
#include <stdio.h>
#include <stdlib.h> // free
#include <sys/stat.h> // stat

#include "init.h"

bool exec_context(context_t *context);
