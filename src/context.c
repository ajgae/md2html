
#include "context.h"

void init_context(context_t *context) {
  context->filesize = 0;
  context->lf_cnt = 0;
  context->curr_block = BLOCK_NONE;
  context->prev_block = BLOCK_NONE;
  context->line = 1;
  context->offs = 0;
  context->inline_styles.em = false;
  context->inline_styles.strong = false;
}

