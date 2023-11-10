#include "cli.h"
#include "cli_internal.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  flag,
  param,
} parse_state;

static const char *states[] = {
  [flag] = "flag",
  [param] = "param",
};

opt *find_opt(const char *token, opt *const opts);
void exec_opt_fp(const opt *const opt, const char *arg_start[]);

ParseError cli_parse(int argc, const char *argv[]) {
  const char *token = NULL;
  const char **flag_arg_start = NULL;
  parse_state state = flag;
  size_t params = 0;
  opt *current_opt = NULL;
  ParseError err = PARSE_ERROR_NONE;

  for (size_t i = 1; i < argc; i++) {
    token = argv[i];

    switch (state) {
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

        current_opt->found = true;
        params = current_opt->args;
        if (params) {
          state = param;
          flag_arg_start = NULL;
        } else {
          state = flag;
          exec_opt_fp(current_opt, flag_arg_start);
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
          state = flag;
          exec_opt_fp(current_opt, flag_arg_start);
        }
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
  }

  if (err == PARSE_ERROR_NONE && params != 0) {
    err = PARSE_ERROR_UNEXPECTED_EOL;
  } else {
    for (size_t i = 0; i < num_opts; i++) {
      if (opts[i].required && !opts[i].found) {
        err = PARSE_ERROR_MISSING_REQUIRED;
      }
    }
  }

  return err;
}

opt *find_opt(const char *token, opt *const opts) {
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
