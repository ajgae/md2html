
#include "inline.h"

// Output characters inside a block. Inline styling is handled here.
// This function should be called in a context where
// map[context->curr_char] cannot be a newline character (handle that
// case before calling this function).
void inline_output(context_t *context, char *map) {
  char c = map[context->curr_char];
  switch (c) {
  case '*':
    // TODO avoid weird behaviours and inserting multiple opening and
    // closing tags when more than three '*' are present in a row
    if (context->curr_char + 1 < context->filesize &&
        map[context->curr_char + 1] == '*') {
      // bold
      context->curr_char += 1; // account for extra '*'
      if (!context->inline_styles.strong) {
        printf("<strong>");
        context->inline_styles.strong = true;
      } else {
        printf("</strong>");
        context->inline_styles.strong = false;
      }
    } else {
      // em
      if (!context->inline_styles.em) {
        printf("<em>");
        context->inline_styles.em = true;
      } else {
        printf("</em>");
        context->inline_styles.em = false;
      }
    }
    break;
  default:
    putc(c, stdout);
  }
}
