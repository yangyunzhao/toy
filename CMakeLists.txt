cmake_minimum_required(VERSION 3.10)

# 设置项目名和使用的 C++ 标准
project(toy LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加编译选项
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra)
endif()

# 添加 include 目录
include_directories(include)

# 执行 Python 脚本并移动生成的文件
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/parser/TokenKind.h ${CMAKE_CURRENT_SOURCE_DIR}/include/parser/TriviaKind.h
  COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/syntax_gen.py
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/TokenKind.h ${CMAKE_CURRENT_SOURCE_DIR}/include/parser/TokenKind.h
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/TriviaKind.h ${CMAKE_CURRENT_SOURCE_DIR}/include/parser/TriviaKind.h
  COMMENT "Generating TokenKind.h and TriviaKind.h"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_custom_target(run_python_script ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/parser/TokenKind.h ${CMAKE_CURRENT_SOURCE_DIR}/include/parser/TriviaKind.h)

# 添加静态库
file(GLOB PARSER_SRC "src/parser/*.cpp")
file(GLOB PARSER_HDR "include/parser/*.h")
add_library(parser STATIC ${PARSER_SRC} ${PARSER_HDR})
add_dependencies(parser run_python_script)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PARSER_SRC} ${PARSER_HDR})

# 添加主程序
file(GLOB DRIVER_SRC "src/driver/*.cpp")
file(GLOB DRIVER_HDR "include/driver/*.h")
add_executable(toy ${DRIVER_SRC} ${DRIVER_HDR})
target_link_libraries(toy PRIVATE parser)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${DRIVER_SRC} ${DRIVER_HDR})

# 添加单元测试程序
enable_testing()
file(GLOB_RECURSE TEST_SRC "src/unittests/*.cpp")
file(GLOB_RECURSE TEST_HDR "include/unittests/*.h")
add_executable(unittests ${TEST_SRC} ${TEST_HDR})
target_link_libraries(unittests PRIVATE parser)
add_test(NAME unittests COMMAND unittests)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_SRC} ${TEST_HDR})

# 在 Windows 下设置 toy 为默认启动项
if(MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT toy)
endif()