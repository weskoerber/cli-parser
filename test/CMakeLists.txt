add_executable(cli-test)

target_sources(cli-test PRIVATE test_simple.c)

target_include_directories(cli-test PRIVATE .)

target_link_libraries(cli-test criterion cli)
