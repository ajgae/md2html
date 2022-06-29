
#include "blocks.h"

#include "utils.h"
#include "header.h"

bool blocks(context_t const *ctx) {
  // initialize offset to start of memory-mapped file
  char offs = 0;
  
  switch (ctx->file_mmap[offs]) {
  // header
  case '#': {
    size_t len = count_chars_not(ctx, offs, '\n');
    size_t num_hash = count_chars(ctx, offs, '#');
    offs += num_hash;
    // call header which takes care of the internals of the header
    // block element
    header(ctx->file_mmap + offs, len, num_hash);
    offs += len; // offs now indexes newline character that ends the
                 // header
    break;
  }
  }

  return true;
}

