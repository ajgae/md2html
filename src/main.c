
#include "init.h"
#include "block.h"

#define M2H_RETVAL_SUCCESS 0
#define M2H_RETVAL_EXECFAIL 1
#define M2H_RETVAL_INITFAIL 2

int main(int argc, char **argv) {
  config_t *config = init_config(argc, argv);
  if (config == NULL) {
    return M2H_RETVAL_INITFAIL;
  }

  if (!run(config)) {
    return M2H_RETVAL_EXECFAIL;
  }

  free(config);
  return M2H_RETVAL_SUCCESS;
}
