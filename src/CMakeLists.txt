add_executable(cli-parser)

target_sources(cli-parser PRIVATE main.c parser.c)

target_include_directories(cli-parser PRIVATE .)
