include_directories(${CMAKE_SOURCE_DIR}/include/IR)
file(GLOB IR_SOURCES "*.cpp")

add_library(IR STATIC ${IR_SOURCES})
target_link_libraries(IR PUBLIC ast)