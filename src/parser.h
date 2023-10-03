#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  const char *opt;
  bool found;
  size_t args;
  void (*fp)(char **);
} opt;

void parser_init(int, char **, const opt *, size_t);
void parser_parse_cli();
void parser_cleanup();
