#pragma once

#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h> // open
#include <stdio.h>
#include <sys/stat.h> // stat
#include <sys/mman.h> // mmap

#include "init.h"
#include "context.h"

// Iterate over all the chars in `ctx->map` and print out the
// converted result to stdout.
bool parse(context_t *ctx);
// Print an opening tag for the specified block and update context
// accordingly.
void open_block(context_t *ctx, enum block_element block);
// Calls `open_block` with the right type of block according to
// `num_hash`, the number of hash signs preceding the header.
void open_header(context_t *ctx, size_t num_hash);
// Print a closing tag for currently open block and update context
// accordingly.
void close_block(context_t *ctx);
// Update the current block of `ctx` and its previous block
// accordingly.
static void update_curr_block(context_t *ctx, enum block_element new_block);
// Warn about any still open inline styles and append closing tags for them,
// updating context accordingly.
static void close_inline_styles(context_t *ctx);
// Count successive occurences of `c`, starting at ctx->offs. Can
// return 0.
//
// TODO make the second argument a function pointer that determines
// whether a char must be counted or not
size_t count_successive_chars(context_t *ctx, char c);
// Count whitespace characters until a `\n` or non-whitespace
// character is encountered, starting at ctx->offs. Can return 0.
size_t count_ws_until_lf_or_nonws(context_t *ctx);
