cmake_minimum_required(VERSION 3.7.0)
project (todo)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_BUILD_TYPE Debug)

add_executable (todo "")
target_link_libraries (todo PUBLIC sat)

target_sources (todo
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src/application.c
  ${CMAKE_CURRENT_LIST_DIR}/src/task.c
  ${CMAKE_CURRENT_LIST_DIR}/src/main.c
)

target_include_directories (todo
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)

install (TARGETS todo DESTINATION bin)