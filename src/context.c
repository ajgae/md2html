
#include "context.h"

void init_context(context_t *context) {
  context->num_lf = 0;
  context->curr_block = BLOCK_NONE;
  context->curr_line = 1;
  context->curr_char = 0;
}

