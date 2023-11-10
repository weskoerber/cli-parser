# CLI Parser

A tiny CLI parsing library.

⚠️ **Note**: This project is not yet stable. If you decide to use this library,
expect breaking changes!

## Getting Started

### Prerequisites

- CMake version 3.27
- (Optional) [Criterion](https://github.com/snaipe/criterion)
    - Required if you want to build and run the tests

### Building

To build the library and the example application:

```shell
cmake -B build
cmake --build build
```

To build and run the tests:

```shell
cmake -B build -D TESTING=1
cmake --build build --target test
```

## Usage

Here is a simple example:

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
