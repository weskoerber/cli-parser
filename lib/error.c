#include "cli.h"

const char *errors[] = {
  [PARSE_ERROR_NONE] = "No error",
  [PARSE_ERROR_UNEXPECTED_TOKEN] = "Unexpected token",
  [PARSE_ERROR_UNKNOWN_FLAG] = "Unknown flag",
  [PARSE_ERROR_MISSING_ARGUMENT] = "Missing argument",
  [PARSE_ERROR_UNEXPECTED_EOL] = "Unexpected EOL",
  [PARSE_ERROR_MISSING_REQUIRED] = "Missing required option",
};

const char *cli_strerror(ParseError err) {
  return errors[err];
}
