
#include "block.h"
#include "context.h"
#include "inline.h"
#include <sys/mman.h>
#include <unistd.h>
#include <ctype.h> // isalnum

bool parse(context_t *ctx) {
  // iterate over all chars of the file
  //
  // IMPORTANT: the offset is not automatically incremented by 1, each
  // subunit must increase it according to its operations (skipping
  // over characters, etc.)
  while (ctx->offs < ctx->filesize) {
    // defer line incrementation to the end for correct logging;
    // num_lf must be inced here because it counts consecutive lfs and
    // is used for internal logic
    bool increment_line = false;
    if (ctx->map[ctx->offs] == '\n') {
      increment_line = true;
      ctx->lf_cnt += 1;
    }

    // this case handles opening new blocks (because it means we are
    // not currently in a block). Cases for each block type take care
    // of ending themselves, outputting characters, etc. Could be
    // moved to its own function
    if (ctx->curr_block == BLOCK_NONE) {
      switch (ctx->map[ctx->offs]) {
      case '\n': {
        ctx->offs += 1;
        // do nothing
      } break;

      case '#': {
        size_t j = count_successive_chars(ctx, '#');
        // skip over '#' chars
        ctx->offs += j;

        size_t k = count_ws_until_lf_or_nonws(ctx);
        if (k == 0 && ctx->map[ctx->offs] != '\n') {
          // header text directly after '#' chars
          fprintf(stderr, "Warning [%lu]: no space after last '#' in header\n",
                  ctx->line);
          open_header(ctx, j);
        } else if (ctx->map[ctx->offs + k] == '\n') {
          // empty header
          ctx->offs += k;
          fprintf(stderr, "Warning [%lu]: empty header, ignoring\n", ctx->line);
        } else {
          // skip over whitespace
          ctx->offs += k;
          open_header(ctx, j);
        }
      } break;

      case '*':
      case '-':
      case '_': {
        size_t j = count_successive_chars(ctx, ctx->map[ctx->offs]);
        if (j >= 3) {
          // possibly a <hr>; check if there is only whitespace on the rest of the line
          int k = count_ws_until_lf_or_nonws(ctx);
          if (ctx->map[ctx->offs + j + k] == '\n') {
            // it's indeed a <hr>
            if (ctx->lf_cnt < 2) {
              fprintf(stderr,
                      "Warning [%lu]: no empty line before horizontal rule\n",
                      ctx->line);
            }
            // do not use open_block because hr is not really a block
            printf("<hr>\n");
            // reset lf count
            ctx->lf_cnt = 0;
            // skip over characters that make up the hr, and trailing
            // whitespace characters
            ctx->offs += j + k;
            break;
          } else {
            // it's not a <hr>; dont break; don't offset; goto
            // default. FIXME not very clean is it? in order to
            // default all other cases to opening a paragraph
          }
        }
      }
      default:
        open_block(ctx, BLOCK_P);
        break;
      }
    }

    // These next cases take care of ending their own blocks /
    // outputting characters. Could be moved to their own function.
    if (ctx->curr_block == BLOCK_H1 || ctx->curr_block == BLOCK_H2 ||
        ctx->curr_block == BLOCK_H3 || ctx->curr_block == BLOCK_H4 ||
        ctx->curr_block == BLOCK_H5 || ctx->curr_block == BLOCK_H6) {
      switch (ctx->map[ctx->offs]) {
      case '\n':
        close_block(ctx);
        ctx->offs += 1;
        break;
      default:
        inline_output(ctx);
        break;
      }
    } else if (ctx->curr_block == BLOCK_P) {
      switch (ctx->map[ctx->offs]) {
      case '\n':
        // FIXME check for an empty line after rather than for just a
        // '\n'
        if (ctx->offs < ctx->filesize - 1 && ctx->map[ctx->offs + 1] == '\n') {
          close_block(ctx);
          ctx->offs += 1;
        } else {
          putc(' ', stdout);
          ctx->offs += 1;
        }
        break;
      default:
        inline_output(ctx);
        break;
      }
    } else /*if (...)*/ {
      // other possible blocks
    }

    if (increment_line) {
      ctx->line += 1;
    }
  }

  return true;
}

void open_block(context_t *ctx, enum block_element block) {
  if (ctx->lf_cnt < 2) {
    fprintf(stderr, "Warning [%lu]: no empty line before new block\n",
            ctx->line);
  }
  char *tag;
  // TODO define static array addressable using the enum
  switch (block) {
  case BLOCK_H1:
    tag = "<h1>";
    break;
  case BLOCK_H2:
    tag = "<h2>";
    break;
  case BLOCK_H3:
    tag = "<h3>";
    break;
  case BLOCK_H4:
    tag = "<h4>";
    break;
  case BLOCK_H5:
    tag = "<h5>";
    break;
  case BLOCK_H6:
    tag = "<h6>";
    break;
  case BLOCK_P:
    tag = "<p>";
    break;
  default:
    // SHOULD NEVER HAPPEN (all cases but BLOCK_NONE should be handled
    // above), WILL CAUSE NULL PTR DEREFERENCE
    tag = NULL;
    break;
  }
  printf("%s", tag);
  update_curr_block(ctx, block);
}

void open_header(context_t *ctx, size_t num_hash) {
  if (num_hash <= 6) {
    open_block(ctx, BLOCK_H1 + num_hash - 1);
  } else {
    open_block(ctx, BLOCK_H6);
    fprintf(stderr, "Warning [%lu]: more than 6 '#', defaulting to '<h6>'\n",
            ctx->line);
  }
}

void close_block(context_t *ctx) {
  close_inline_styles(ctx);

  switch (ctx->curr_block) {
  case BLOCK_NONE:
    break; // simply do nothing
  case BLOCK_H1:
    printf("</h1>\n");
    break;
  case BLOCK_H2:
    printf("</h2>\n");
    break;
  case BLOCK_H3:
    printf("</h3>\n");
    break;
  case BLOCK_H4:
    printf("</h4>\n");
    break;
  case BLOCK_H5:
    printf("</h5>\n");
    break;
  case BLOCK_H6:
    printf("</h6>\n");
    break;
  case BLOCK_P:
    printf("</p>\n");
    break;
  }

  update_curr_block(ctx, BLOCK_NONE);
  ctx->lf_cnt = 1; // FIXME possible source of error; is this value
                   // correct?
}

static void update_curr_block(context_t *ctx, enum block_element new_block) {
  ctx->prev_block = ctx->curr_block;
  ctx->curr_block = new_block;
}

static void close_inline_styles(context_t *ctx) {
  if (ctx->inline_styles.strong) {
    fprintf(stderr,
            "Warning [%lu]: strong style not closed at end of block element, "
            "closing automatically\n",
            ctx->line);
    printf("</strong>");
    ctx->inline_styles.strong = false;
  }
  if (ctx->inline_styles.em) {
    fprintf(
        stderr,
        "Warning [%lu]: em style not closed at end of block element, closing "
        "automatically\n",
        ctx->line);
    printf("</em>");
    ctx->inline_styles.em = false;
  }
}

size_t count_successive_chars(context_t *ctx, char c) {
  size_t cnt = 0;
  while (ctx->offs + cnt < ctx->filesize && ctx->map[ctx->offs + cnt] == c) {
    ++cnt;
  }
  return cnt;
}

size_t count_ws_until_lf_or_nonws(context_t *ctx) {
  size_t cnt = 0;
  while (ctx->offs + cnt < ctx->filesize &&
         isspace(ctx->map[ctx->offs + cnt]) &&
         ctx->map[ctx->offs + cnt] != '\n') {
    ++cnt;
  }
  return cnt;
}

