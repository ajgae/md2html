#pragma once

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

enum block_element {
  BLOCK_NONE = 0,
  BLOCK_H1,
  BLOCK_H2,
  BLOCK_H3,
  BLOCK_H4,
  BLOCK_H5,
  BLOCK_H6,
  BLOCK_P,
};

typedef struct _context_t context_t;
struct _context_t {
  // filesize of file to be converted
  size_t filesize;
  // number of consecutive '\n' chars encountered
  size_t num_lf;
  // type of the block element we're currently in
  enum block_element curr_block;
  // current line in the file
  size_t curr_line;
  // byte offset in the file
  size_t curr_char;

  // defines what inline styles are
  struct {
    bool em;
    bool strong;
  } inline_styles;
};

void init_context(context_t *context);

