#include "parser.h"
#include <stdio.h>

static char *name = "NULL";

void say_hello(size_t argc, char **argv) {
  printf("Hello, world!\n");
}

void greet(size_t argc, char **argv) {
  name = argv[0];
}

void greet_many(size_t argc, char **argv) {
  printf("Hello: ");
  for (int i = 0; i < argc; i++) {
    printf("\n- %s", argv[i]);
  }
  printf("\n");
}

static const opt opts[] = {{"-h", false, 0, say_hello},
                           {"-n", false, 2, greet_many},
                           {"-g", false, 1, greet}};

int main(int argc, char **argv) {
  parser_init(argc, argv, opts, sizeof(opts) / sizeof(opts[0]));

  parser_parse_cli();

  printf("Hello, %s\n", name);

  parser_cleanup();

  return 0;
}
