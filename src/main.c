#include "cli/cli.h"

#include <stdarg.h>
#include <stdio.h>

static const char *name = "NULL";

void say_hello(size_t nargs, const char *args[]) {
  printf("Hello, world!\n");
}

void greet(size_t nargs, const char *args[]) {
  name = args[0];
}

void greet_many(size_t argc, const char *argv[]) {
  printf("Hello: ");
  for (int i = 0; i < argc; i++) {
    printf("\n- %s", argv[i]);
  }
  printf("\n");
}

int main(int argc, const char *argv[]) {
  cli_init();

  cli_add_option("-h", 0, say_hello);
  cli_add_required_option("-g", 1, greet);
  cli_add_option("-n", 2, greet_many);
  cli_add_option("--name", 1, greet);

  ParseError err = cli_parse(argc, argv);
  if (err != PARSE_ERROR_NONE) {
    printf("ParseError: %s\n", cli_strerror(err));
    return -1;
  }

  printf("Hello, %s\n", name);

  cli_cleanup();

  return 0;
}
