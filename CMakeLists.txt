cmake_minimum_required(VERSION 3.12)

# 设置项目名字为 MXCompiler
project(MXCompiler)

# 设置编译标准为 C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



# 设置如果没有指定，默认编译模式为 release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 设置 Debug 模式下开启全部编译警告和 sanitizer
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    elseif(MSVC)
        add_compile_options(/W4 /WX)
    endif()
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL_HASH SHA256=1f357c27ca988c3f7c6b4bf68a9395005ac6761f034046e9dde0896e3aba00e4
  URL ${CMAKE_SOURCE_DIR}/deps/googletest-v1.14.0-mirror.zip
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
FetchContent_Declare(
  argparse
  URL_HASH SHA256=cd07c1208c01bef28c5173f4bad0b2df73dd7316d2f56fc80344952c400fa711
  URL ${CMAKE_SOURCE_DIR}/deps/argparse-9550b0a-mirror.zip
)
FetchContent_MakeAvailable(argparse)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)
