add_subdirectory(ast)
add_subdirectory(semantic)
add_executable(zmxcc main.cpp)
target_link_libraries(zmxcc semantic argparse)
set_target_properties(zmxcc PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)