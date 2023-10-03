#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int argc = 0;
static char **argv = NULL;
static opt *opts = NULL;
static size_t num_opts = 0;

void parser_init(int t_argc, char **t_argv, const opt *t_opts,
                 size_t t_num_opts) {
  argc = t_argc;
  argv = t_argv;
  num_opts = t_num_opts;

  size_t size = sizeof(opt) * t_num_opts;
  opts = malloc(size);
  memcpy(opts, t_opts, size);
}

void parser_parse_cli() {
  // CLI parsing
  for (size_t o = 0; o < num_opts; o++) {
    for (size_t a = 1; a < argc; a++) {
      if (!opts[o].found && strcmp(argv[a], opts[o].opt) == 0) {
        opts[o].found = true;

        if (opts[o].args) {
          if (opts[o].args < argc - a) {
            opts[o].fp(&argv[a + 1]);
          } else {
            fprintf(stderr, "Error: Missing argument\n");
            parser_cleanup();
            exit(1);
          }
        } else {
          opts[o].fp(NULL);
        }
      }
    }
  }
}

void parser_cleanup() {
  free(opts);
}
