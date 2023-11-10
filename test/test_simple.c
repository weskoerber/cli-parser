#include "cli/cli.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

bool found = false;
int num = -1;

void reset(void) {
  found = false;
  num = -1;
}

void test_arity_0(size_t nargs, const char *args[]) {
  found = true;
}

void test_arity_1(size_t nargs, const char *args[]) {
  cr_assert(eq(sz, 1, nargs));
  cr_assert(ne(ptr, nullptr, args));
  cr_assert(ne(ptr, nullptr, args[0]));

  num = strtol(args[0], nullptr, 10);
}

Test(cli, arity_none, .init = reset) {
  int argc = 2;
  const char *argv[] = {
    "appname",
    "-t",
  };
  ParseError err;

  cli_init();
  cli_add_option("-t", 0, test_arity_0);
  err = cli_parse(argc, argv);
  cli_cleanup();

  cr_assert(eq(int, PARSE_ERROR_NONE, err));
  cr_assert(found);
}

Test(cli, arity_1, .init = reset) {
  int argc = 3;
  const char *argv[] = {
    "appname",
    "-n",
    "42",
  };
  ParseError err;

  cli_init();
  cli_add_option("-n", 1, test_arity_1);
  err = cli_parse(argc, argv);
  cli_cleanup();

  cr_assert(eq(int, PARSE_ERROR_NONE, err));
  cr_assert(eq(int, 42, num));
}

Test(cli, multiple_args, .init = reset) {
  int argc = 4;
  const char *argv[] = {
    "appname",
    "-t",
    "-n",
    "42",
  };
  ParseError err;

  cli_init();
  cli_add_option("-t", 0, test_arity_0);
  cli_add_option("-n", 1, test_arity_1);
  err = cli_parse(argc, argv);
  cli_cleanup();

  cr_assert(eq(int, PARSE_ERROR_NONE, err));
  cr_assert(found);
  cr_assert(eq(int, 42, num));
}

Test(cli, missing_arguments, .init = reset) {
  int argc = 3;
  const char *argv[] = {
    "appname",
    "-n",
    "-t",
  };
  ParseError err;

  cli_init();
  cli_add_option("-n", 1, test_arity_1);
  err = cli_parse(argc, argv);
  cli_cleanup();

  cr_assert(eq(int, PARSE_ERROR_MISSING_ARGUMENT, err));
}

Test(cli, premature_eol, .init = reset) {
  int argc = 2;
  const char *argv[] = {
    "appname",
    "-n",
  };
  ParseError err;

  cli_init();
  cli_add_option("-n", 1, test_arity_1);
  err = cli_parse(argc, argv);
  cli_cleanup();

  cr_assert(eq(int, PARSE_ERROR_UNEXPECTED_EOL, err));
}

Test(cli, missing_required, .init = reset) {
  int argc = 2;
  const char *argv[] = {
    "appname",
    "-t",
  };
  ParseError err;

  cli_init();
  cli_add_option("-t", 0, test_arity_0);
  cli_add_required_option("-n", 1, test_arity_1);
  err = cli_parse(argc, argv);
  cli_cleanup();

  cr_assert(eq(int, PARSE_ERROR_MISSING_REQUIRED, err));
  cr_assert(found);
}
