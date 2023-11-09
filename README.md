# CLI Parser

A tiny CLI parsing library.

## Usage

```c
#include "cli/cli.h"

#include <stdio.h>
#include <stdlib.h>

int num;

void get_num(size_t nargs, char *argv[]) {
    if (nargs != 1) {
        return;
    }

    num = strtol(argv[0], NULL, 10);
}

int main(int argc, char *argv[]) {
    // Initialize the parser
    cli_init();

    // Adds an optional flag with 1 argument
    cli_add_option("-n", 1, get_num);

    // Adds a required flag with 1 argument
    // cli_add_required_option("--number", 1, get_num);

    // parse the input
    cli_parse(argc, argv);

    // Cleanup the parser
    cli_cleanup();

    printf("num: %d\n", num);
}
```
