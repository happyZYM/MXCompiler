include_directories(${CMAKE_SOURCE_DIR}/include/ast)
file(GLOB AST_SOURCES "*.cpp")
add_library(ast STATIC ${AST_SOURCES})