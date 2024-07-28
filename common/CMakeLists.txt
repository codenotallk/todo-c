add_library (common "")
# target_link_libraries (todo PUBLIC sat)

target_sources (common
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/common.c
)

target_include_directories (common
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/
)