#pragma once

#include <stddef.h> // size_t

#include "context.h"

size_t count_chars(context_t const *ctx, size_t offs, char c);
size_t count_chars_not(context_t const *ctx, size_t offs, char c);

