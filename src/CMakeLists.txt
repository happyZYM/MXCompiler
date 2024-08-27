add_subdirectory(ast)
add_subdirectory(semantic)
add_subdirectory(IR)
add_subdirectory(naivebackend)
add_executable(zmxcc main.cpp)
target_link_libraries(zmxcc semantic argparse IR naivebackend)
set_target_properties(zmxcc PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)