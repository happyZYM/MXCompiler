include_directories(${CMAKE_SOURCE_DIR}/include/opt)

file(GLOB NAIVE_BACKEND_SOURCES "*.cpp")
add_library(opt SHARED ${NAIVE_BACKEND_SOURCES})
target_link_libraries(opt PUBLIC ast)