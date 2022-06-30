#pragma once

#include <stddef.h> // size_t

#include "context.h"

// Returns the consecutive number of the given character starting at
// offs in the context's file mmap . If len is the return value of
// this function, (offs+len) will index the first occurrence of
// a non-c character that was encountered.
size_t count_chars(context_t const *ctx, size_t offs, char c);

// Returns the number of characters in the context's file mmap from
// offs until c is encountered. If len is the return value of this
// function, (offs+len) will index the occurrence of c encountered.
//
// TODO maybe return different value if character was not found until
// end of file
size_t count_chars_until(context_t const *ctx, size_t offs, char c);

// Returns true if and only if there are only whitespace characters
// until the first newline character is met after offs in the
// context's file mmap. Will also return true if the end of file is
// reached and only whitespace characters have been encountered.
bool empty_line(context_t const *ctx, size_t offs);

// Returns true if c is considered whitespace (the newline character
// is considered to be whitespace).
bool is_whitespace(char c);

// Returns the amount of characters until a double-newline is
// encountered.
size_t block_len_double_nl(context_t const *ctx, size_t offs);

