#include "cli.h"
#include "cli_internal.h"

opt opts[NUM_OPTS];
size_t num_opts = 0;

bool cli_add_option_internal(
  const char *name,
  bool required,
  size_t arity,
  void (*fp)(size_t nargs, const char *args[]));

bool cli_add_option(
  const char *name,
  size_t arity,
  void (*fp)(size_t nargs, const char *args[])) {
  return cli_add_option_internal(name, false, arity, fp);
}

bool cli_add_required_option(
  const char *name,
  size_t arity,
  void (*fp)(size_t, const char **)) {
  return cli_add_option_internal(name, true, arity, fp);
}

bool cli_add_option_internal(
  const char *name,
  bool required,
  size_t arity,
  void (*fp)(size_t nargs, const char *args[])) {
  if (num_opts >= NUM_OPTS) {
    return false;
  }

  if (name == nullptr) {
    return false;
  }

  if (fp == nullptr) {
    return false;
  }

  opts[num_opts] = (opt) {
    .opt = name,
    .required = required,
    .found = false,
    .args = arity,
    .fp = fp,
  };

  num_opts++;

  return true;
}
