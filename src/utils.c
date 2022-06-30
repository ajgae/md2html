#include "utils.h"

static bool out_of_bounds(context_t const *ctx, size_t offs) {
  return offs >= ctx->file_size;
}

size_t count_chars(context_t const *ctx, size_t offs, char c) {
  size_t cnt = 0;

  while (!out_of_bounds(ctx, offs + cnt) &&
         ctx->file_mmap[offs + cnt] == c) {
    cnt += 1;
  }

  return cnt;
}

size_t count_chars_until(context_t const *ctx, size_t offs, char c) {
  size_t cnt = 0;

  while (!out_of_bounds(ctx, offs + cnt) &&
         ctx->file_mmap[offs + cnt] != c) {
    cnt += 1;
  }

  return cnt;
}

bool empty_line(context_t const *ctx, size_t offs) {
  for (size_t i = 0;
       !out_of_bounds(ctx, offs + i)
         && ctx->file_mmap[offs + i] != '\n';
       ++i) {
    if (!is_whitespace(ctx->file_mmap[offs + i])) {
      return false;
    }
  }

  return true;
}

bool is_whitespace(char c) { return c == ' ' | c == '\t' | c == '\n'; }

size_t block_len_double_nl(context_t const *ctx, size_t offs) {
  size_t len = 0;

  while (!out_of_bounds(ctx, offs + len)) {
    if (ctx->file_mmap[offs + len] == '\n') {
      if (empty_line(ctx, offs + len + 1)) {
        break;
      }
    }
     len += 1;
  }

  return len;
}

