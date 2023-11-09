add_executable(cli-parser)

target_sources(cli-parser PRIVATE main.c)

target_include_directories(cli-parser PRIVATE .)

target_link_libraries(cli-parser cli)

