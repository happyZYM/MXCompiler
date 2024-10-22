include_directories(${CMAKE_SOURCE_DIR}/include/naivebackend)

file(GLOB NAIVE_BACKEND_SOURCES "*.cpp")
add_library(naivebackend SHARED ${NAIVE_BACKEND_SOURCES})
target_link_libraries(naivebackend PUBLIC ast)