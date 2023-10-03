#include "parser.h"
#include <stdio.h>

static char *name = NULL;

void say_hello(char **args) {
  printf("Hello, world!\n");
}

void greet(char **args) {
  name = args[0];
}

static const opt opts[] = {{"-h", false, 0, say_hello},
                           {"-g", false, 1, greet}};

int main(int argc, char **argv) {
  // Parse the CLI input
  parser_init(argc, argv, opts, sizeof(opts) / sizeof(opts[0]));
  parser_parse_cli();

  // Run the application with the parsed input
  printf("Hello, %s!\n", name);

  // Clean up the parser
  parser_cleanup();
}
