#include "utils.h"

// Returns the consecutive number of the given character starting at
// offs in the context's file mmap . If len is the return value of
// this function, (offs+len) will index the first occurrence of
// a non-c character that was encountered.
size_t count_chars(context_t const *ctx, size_t offs, char c) {
  size_t cnt = 0;
  while (offs + cnt < ctx->file_size
         && ctx->file_mmap[offs + cnt] == c) {
    ++cnt;
  }
  return cnt;
}

// Returns the number of characters in the context's file mmap from
// offs until c is encountered. If len is the return value of this
// function, (offs+len) will index the occurrence of c encountered.
//
// TODO maybe return different value if character was not found until
// end of file
size_t count_chars_not(context_t const *ctx, size_t offs, char c) {
  size_t cnt = 0;
  while (offs + cnt < ctx->file_size
         && ctx->file_mmap[offs + cnt] != c) {
    ++cnt;
  }
  return cnt;
}

