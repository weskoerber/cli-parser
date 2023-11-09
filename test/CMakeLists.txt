add_executable(cli-test)

target_sources(cli-test PRIVATE test_simple.c)

target_include_directories(cli-test PRIVATE .)

target_link_libraries(cli-test criterion cli)

add_custom_target(
  test
  COMMAND
  cli-test
  WORKING_DIRECTORY
  $<TARGET_FILE_DIR:cli-test>
  DEPENDS
  $<TARGET_FILE:cli-test>
)

