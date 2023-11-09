#include "parser.h"

#include "cli.h"
#include "cli_internal.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  start,
  flag,
  param,
  done,
} parse_state;

const opt *find_opt(const char *token, const opt *const opts);
void exec_opt_fp(const opt *const opt, const char *arg_start[]);

ParseError cli_parse(int argc, const char *argv[]) {
  const char *token = NULL;
  const char **flag_arg_start = NULL;
  parse_state state = start;
  size_t params = 0;
  const opt *current_opt = NULL;
  ParseError err = PARSE_ERROR_NONE;

  for (size_t i = 0; i < argc; i++) {
    token = argv[i];

    switch (state) {
      case start:
        state = flag;
        break;
      case flag:
        if (token[0] != '-') {
          fprintf(stderr, "Error: expected flag, got '%s'\n", token);
          err = PARSE_ERROR_UNEXPECTED_TOKEN;
          break;
        }
        current_opt = find_opt(token, opts);
        if (current_opt == NULL) {
          fprintf(stderr, "Error: Unrecognized flag: '%s'\n", token);
          err = PARSE_ERROR_UNKNOWN_FLAG;
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
          err = PARSE_ERROR_MISSING_ARGUMENT;
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
        err = PARSE_ERROR_UNEXPECTED_TOKEN;
        break;
    }

    // Stop processing immediately if input is invalid
    if (err != PARSE_ERROR_NONE) {
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

  if (err != PARSE_ERROR_NONE) {
    fprintf(stderr, "DEBUG: Parsing completed with error\n");
  }

  return err;
}

const opt *find_opt(const char *token, const opt *const opts) {
  for (size_t i = 0; i < num_opts; i++) {
    if (strcmp(token, opts[i].opt) == 0) {
      return &opts[i];
    }
  }

  return NULL;
}

void exec_opt_fp(const opt *const opt, const char *arg_start[]) {
  opt->fp(opt->args, arg_start);
}
