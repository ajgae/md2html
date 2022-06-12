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
  // pointer to the memory-mapped file
  char *map;
  // filesize of file to be converted
  size_t filesize;
  // count of consecutive '\n' chars encountered
  size_t lf_cnt;
  // type of the block element we're currently in
  enum block_element curr_block;
  enum block_element prev_block;
  // current line in the file
  size_t line;
  // char offset in the file
  size_t offs;

  // defines what inline styles are
  struct {
    bool em;
    bool strong;
  } inline_styles;
};

void init_context(context_t *context);

