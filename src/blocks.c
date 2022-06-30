
#include "blocks.h"

#include <stdio.h>

#include "helpers.h"
#include "header.h"
#include "paragraph.h"
#include "utils.h"

bool blocks(context_t *ctx) {
  // initialize offset to start of memory-mapped file
  size_t offs = 0;
  // incorrect because the newline chars inside block elements are not
  // counted
  size_t line_num = 0;

  while (offs < ctx->file_size) {
    // eat empty lines
    while (ctx->file_mmap[offs] == '\n') {
      offs += 1; // goto the start of the next line
      line_num += 1; // increase line num
      // if it's an empty line, skip it
      if (empty_line(ctx, offs)) {
        // FIXME empty_line already counts chars until newline, use
        // that result somehow
        offs += count_chars_until(ctx, offs, '\n');
      }
    }

    switch (ctx->file_mmap[offs]) {
    // header
    case '#': {
      size_t num_hash = count_chars(ctx, offs, '#');
      offs += num_hash;
      // count len after advancing offs!
      size_t len = count_chars_until(ctx, offs, '\n');
      // header takes care of the internals of the header block
      // element
      header(ctx->file_mmap + offs, len, num_hash);
      offs += len;
      if (!empty_line(ctx, offs + 1)) {
        M2H_NOTE("line %lu: no empty line after header", line_num);
      }
      break;
    }
    default: {
      size_t len = block_len_double_nl(ctx, offs);
      paragraph(ctx->file_mmap + offs, len);
      offs += len;
      break;
    }
    }

    // at this point offs should index the newline character ending
    // whatever block was just processed
  }

  return true;
}
