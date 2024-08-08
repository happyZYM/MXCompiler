add_subdirectory(ast)
add_subdirectory(semantic)
add_executable(code main.cpp)
target_link_libraries(code semantic argparse)
set_target_properties(code PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)