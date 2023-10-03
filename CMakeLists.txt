cmake_minimum_required(VERSION 3.27)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(cli-parser)

add_subdirectory(src)

if(${TESTING})
    add_subdirectory(test)
endif()
