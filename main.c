
#include "init.h"
#include "exec.h"

#define M2H_RETVAL_SUCCESS 0
#define M2H_RETVAL_EXECFAIL 1
#define M2H_RETVAL_INITFAIL 2

int main(int argc, char **argv) {
  context_t *context = init_context(argc, argv);
  if (context == NULL) {
    return M2H_RETVAL_INITFAIL;
  }

  if (!exec_context(context)) {
    return M2H_RETVAL_EXECFAIL;
  }

  free(context);
  return M2H_RETVAL_SUCCESS;
}
