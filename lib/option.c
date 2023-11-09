#include "cli.h"
#include "cli_internal.h"

opt opts[NUM_OPTS];
size_t num_opts = 0;

bool cli_add_option(
  const char *name,
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
    .args = arity,
    .fp = fp,
  };

  num_opts++;

  return true;
}
