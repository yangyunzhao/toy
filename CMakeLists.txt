cmake_minimum_required(VERSION 3.10)

# 设置项目名和使用的 C++ 标准
project(toy LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加编译选项
if(MSVC)
  add_compile_options(/W3 /MP /utf-8)
else()
  add_compile_options(-Wall -Wextra)
endif()

# 添加 include 目录
include_directories(include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/catch2/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog-1.13.0/include)

# 添加 lib 目录
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog-1.13.0/lib)

# 创建 bin 和 log 目录（如果不存在）
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/log)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

# 在添加目标之前，为所有配置类型设置统一的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endforeach()

# 执行 Python 脚本并移动生成的文件
execute_process(
  COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/syntax_gen.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts
)

# 添加静态库
file(GLOB PARSER_SRC "src/parser/*.cpp")
file(GLOB PARSER_HDR "include/parser/*.h")
add_library(parser STATIC ${PARSER_SRC} ${PARSER_HDR})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PARSER_SRC} ${PARSER_HDR})

# 添加主程序
file(GLOB DRIVER_SRC "src/driver/*.cpp")
file(GLOB DRIVER_HDR "include/driver/*.h")
add_executable(toy ${DRIVER_SRC} ${DRIVER_HDR})
target_link_libraries(toy PRIVATE parser spdlogd)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${DRIVER_SRC} ${DRIVER_HDR})

# 添加单元测试程序
enable_testing()
file(GLOB_RECURSE TEST_SRC "src/unittests/*.cpp")
file(GLOB_RECURSE TEST_HDR "include/unittests/*.h")
add_executable(unittests ${TEST_SRC} ${TEST_HDR})
target_link_libraries(unittests PRIVATE parser spdlogd)
add_test(NAME unittests COMMAND unittests)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_SRC} ${TEST_HDR})

# 在 Windows 下设置 toy 为默认启动项
if(MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT toy)
endif()
