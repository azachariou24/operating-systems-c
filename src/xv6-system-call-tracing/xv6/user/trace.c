#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(2, "Usage: trace <trace_flag> <command> [args...]\n");
    exit(1);
  }

  int trace_flag = atoi(argv[1]);

  trace(trace_flag);

  exec(argv[2], &argv[2]);

  fprintf(2, "trace: exec failed\n");
  exit(1);
}
