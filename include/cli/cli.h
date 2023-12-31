#pragma once

#include <stddef.h>

#ifndef NUM_OPTS
#  define NUM_OPTS 100
#endif

typedef enum {
  PARSE_ERROR_NONE = 0,
  PARSE_ERROR_UNEXPECTED_TOKEN,
  PARSE_ERROR_UNKNOWN_FLAG,
  PARSE_ERROR_MISSING_ARGUMENT,
  PARSE_ERROR_UNEXPECTED_EOL,
  PARSE_ERROR_MISSING_REQUIRED,
} ParseError;

void cli_init();
void cli_cleanup();

bool cli_add_option(
  const char *name,
  size_t arity,
  void (*fp)(size_t nargs, const char *args[]));

bool cli_add_required_option(
  const char *name,
  size_t arity,
  void (*fp)(size_t nargs, const char *args[]));

ParseError cli_parse(int argc, const char *argv[]);
const char *cli_strerror(ParseError err);
