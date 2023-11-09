add_library(
    cli
    ${CMAKE_SOURCE_DIR}/lib/error.c
    ${CMAKE_SOURCE_DIR}/lib/init.c
    ${CMAKE_SOURCE_DIR}/lib/option.c
    ${CMAKE_SOURCE_DIR}/lib/parser.c
)

target_include_directories(
    cli
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/cli/
    ${CMAKE_SOURCE_DIR}/lib/
    INTERFACE
    ${CMAKE_SOURCE_DIR}/include/
)
