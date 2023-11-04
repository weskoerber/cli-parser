#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  start,
  flag,
  param,
  done,
} parse_state;

static int argc = 0;
static char **argv = NULL;
static const opt *opts = NULL;
static size_t num_opts = 0;

const opt *find_opt(const char *token, const opt *const opts);
void exec_opt_fp(const opt *const opt, char **arg_start);

void parser_init(int t_argc, char **t_argv, const opt *t_opts,
                 size_t t_num_opts) {
  argc = t_argc;
  argv = t_argv;
  num_opts = t_num_opts;
  opts = t_opts;
}

void parser_cleanup() {
}

void parser_parse_cli() {
  bool invalid = false;
  char *token = NULL;
  char **flag_arg_start = NULL;
  parse_state state = start;
  size_t params = 0;
  const opt *current_opt = NULL;

  for (size_t i = 0; i < argc; i++) {
    token = argv[i];

    switch (state) {
    case start:
      state = flag;
      break;
    case flag:
      if (token[0] != '-') {
        fprintf(stderr, "Error: expected flag, got '%s'\n", token);
        invalid = true;
        break;
      }
      current_opt = find_opt(token, opts);
      if (current_opt == NULL) {
        fprintf(stderr, "Error: Unrecognized flag: '%s'\n", token);
        invalid = true;
        break;
      }

      params = current_opt->args;
      if (params) {
        state = param;
        flag_arg_start = NULL;
      } else {
        state = done;
      }
      break;
    case param:
      if (token[0] == '-') {
        fprintf(stderr, "Error: expected argument, got '%s'\n", token);
        invalid = true;
        break;
      }

      if (flag_arg_start == NULL) {
        flag_arg_start = &argv[i];
      }

      if (--params == 0) {
        state = done;
      }

      break;
    case done:
      exec_opt_fp(current_opt, flag_arg_start);
      state = flag;
      break;
    default:
      fprintf(stderr, "Error: Invalid token: '%s'\n", token);
      invalid = true;
      break;
    }

    // Stop processing immediately if input is invalid
    if (invalid) {
      break;
    }

    // If flag parsing completes on last element in argv, the function pointer
    // won't be called, as the bound on argc causes the for loop to exit. There
    // may be a better solution to this problem, but for now this works.
    if (state == done) {
      exec_opt_fp(current_opt, flag_arg_start);
      state = flag;
    }
  }

  if (invalid) {
    fprintf(stderr, "DEBUG: Parsing completed with error\n");
  }
}

const opt *find_opt(const char *token, const opt *const opts) {
  for (size_t i = 0; i < num_opts; i++) {
    if (strcmp(token, opts[i].opt) == 0) {
      return &opts[i];
    }
  }

  return NULL;
}

void exec_opt_fp(const opt *const opt, char **arg_start) {
  opt->fp(opt->args, arg_start);
}
