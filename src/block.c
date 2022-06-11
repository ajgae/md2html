
#include "block.h"
#include "inline.h"

bool run(config_t *config) {
  context_t context;
  init_context(&context);

  int fd = open(config->file_name, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "Error: could not open file for reading\n");
    return false;
  }

  // get file attributes
  struct stat stat;
  if (fstat(fd, &stat) == -1) {
    fprintf(stderr, "Error: could not get file attributes\n");
    return false;
  }
  context.filesize = stat.st_size;

  // memory map the file for reading
  char *map = mmap(NULL, context.filesize, PROT_READ, MAP_PRIVATE, fd, 0);
  if (close(fd) == -1) {
    fprintf(stderr, "Error: could not close file\n");
    return false;
  }

  for (; context.curr_char < context.filesize; ++(context.curr_char)) {
    if (map[context.curr_char] == '\n') {
      context.curr_line += 1;
    }

    switch (context.curr_block) {

    case BLOCK_NONE:
      switch (map[context.curr_char]) {
      case '\n':
        break;
      case '#': {
        size_t j = 1;
        for (; context.curr_char + j < context.filesize &&
               map[context.curr_char + j] == '#';
             ++j)
          ;
        switch (j) {
        case 1:
          printf("<h1>");
          context.curr_block = BLOCK_H1;
          break;
        case 2:
          printf("<h2>");
          context.curr_block = BLOCK_H2;
          break;
        case 3:
          printf("<h3>");
          context.curr_block = BLOCK_H3;
          break;
        case 4:
          printf("<h4>");
          context.curr_block = BLOCK_H4;
          break;
        case 5:
          printf("<h5>");
          context.curr_block = BLOCK_H5;
          break;
        case 6:
          printf("<h6>");
          context.curr_block = BLOCK_H6;
          break;
        default:
          fprintf(stderr,
                  "Warning [%lu]: more than 6 '#', defaulting to '<h6>'\n",
                  context.curr_line);
          printf("<h6>");
          context.curr_block = BLOCK_H6;
          break;
        }
        context.curr_char += j;
        break;
      }
      default:
        printf("<p>");
        context.curr_block = BLOCK_P;
        inline_output(&context, map);
        break;
      }
      break;

    case BLOCK_H1:
    case BLOCK_H2:
    case BLOCK_H3:
    case BLOCK_H4:
    case BLOCK_H5:
    case BLOCK_H6:
      switch (map[context.curr_char]) {
      case '\n':
        if (context.curr_char < context.filesize - 1 &&
            map[context.curr_char + 1] != '\n') {
          fprintf(stderr, "Warning [%lu]: no empty line after title\n",
                  context.curr_line);
        }
        close_block(&context);
        break;
      default:
        inline_output(&context, map);
        break;
      }
      break;

    case BLOCK_P:
      switch (map[context.curr_char]) {
      case '\n':
        if (context.curr_char < context.filesize - 1 &&
            map[context.curr_char + 1] == '\n') {
          printf("</p>\n");
          context.curr_block = BLOCK_NONE;
        } else {
          putc(' ', stdout);
        }
        break;
      default:
        inline_output(&context, map);
        break;
      }
      break;
    }
  }

  munmap(map, context.filesize);
  return true;
}

void close_block(context_t *context) {
  close_inline_styles(context);

  switch (context->curr_block) {
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

  context->curr_block = BLOCK_NONE;
}

// Closes all inline styles and emits warnings if some are still
// active
void close_inline_styles(context_t *context) {
  if (context->inline_styles.strong) {
    fprintf(stderr,
            "Warning [%lu]: strong style not closed at end of paragraph, "
            "closing automatically...\n",
            context->curr_line);
    printf("</strong>");
    context->inline_styles.strong = false;
  }
  if (context->inline_styles.em) {
    fprintf(stderr,
            "Warning [%lu]: em style not closed at end of paragraph, closing "
            "automatically\n",
            context->curr_line);
    printf("</em>");
    context->inline_styles.em = false;
  }
}
