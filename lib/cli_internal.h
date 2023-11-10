#pragma once

#include "cli.h"

typedef struct {
  const char *opt;
  bool required;
  bool found;
  size_t args;
  void (*fp)(size_t count, const char *args[]);
} opt;

extern opt opts[];
extern size_t num_opts;
