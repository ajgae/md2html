
#include "inline.h"

// Output characters inside a block. Inline styling is handled here.
// This function should be called in a context where
// map[context->curr_char] cannot be a newline character (handle that
// case before calling this function).
void inline_output(context_t *ctx) {
  char c = ctx->map[ctx->offs];
  switch (c) {
  case '*':
    // TODO avoid weird behaviours and inserting multiple opening and
    // closing tags when more than three '*' are present in a row
    if (ctx->offs + 1 < ctx->filesize &&
        ctx->map[ctx->offs + 1] == '*') {
      // bold
      ctx->offs += 1; // account for extra '*'
      if (!ctx->inline_styles.strong) {
        printf("<strong>");
        ctx->inline_styles.strong = true;
      } else {
        printf("</strong>");
        ctx->inline_styles.strong = false;
      }
    } else {
      // em
      if (!ctx->inline_styles.em) {
        printf("<em>");
        ctx->inline_styles.em = true;
      } else {
        printf("</em>");
        ctx->inline_styles.em = false;
      }
    }
    break;
  default:
    putc(c, stdout);
    break;
  }

  ctx->offs += 1;
}
