cmake_minimum_required(VERSION 3.10)

# 设置项目名和使用的 C++ 标准
project(toy LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置默认构建类型为 Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug FORCE)
endif()

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
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc)

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

# 添加静态库
file(GLOB PARSER_SRC "src/parser/*.cpp")
file(GLOB PARSER_HDR "include/parser/*.h")
add_library(parser STATIC ${PARSER_SRC} ${PARSER_HDR})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PARSER_SRC} ${PARSER_HDR})

# 添加静态库
file(GLOB UTIL_SRC "src/util/*.cpp")
file(GLOB TEXT_SRC "src/text/*.cpp")
file(GLOB UTIL_HDR "include/util/*.h")
file(GLOB TEXT_HDR "include/text/*.h")
add_library(core STATIC ${UTIL_SRC} ${TEXT_SRC} ${UTIL_HDR} ${TEXT_HDR})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UTIL_SRC} ${TEXT_SRC} ${UTIL_HDR} ${TEXT_HDR})

# 添加主程序
file(GLOB DRIVER_SRC "src/driver/*.cpp")
file(GLOB DRIVER_HDR "include/driver/*.h")
add_executable(toy ${DRIVER_SRC} ${DRIVER_HDR})
target_link_libraries(toy PRIVATE parser core spdlogd)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${DRIVER_SRC} ${DRIVER_HDR})

# 添加单元测试程序
enable_testing()
file(GLOB_RECURSE TEST_SRC "src/unittests/*.cpp")
file(GLOB_RECURSE TEST_HDR "include/unittests/*.h")
add_executable(unittests ${TEST_SRC} ${TEST_HDR})
target_link_libraries(unittests PRIVATE parser core spdlogd)
add_test(NAME unittests COMMAND unittests)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_SRC} ${TEST_HDR})

# 在 Windows 下设置 toy 为默认启动项
if(MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT toy)
endif()

# 添加 clang-format 自定义目标
file(GLOB_RECURSE ALL_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
)
execute_process(
  COMMAND clang-format
  -i
  ${ALL_SRC}
)

# 检查是否安装了Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND)
    # 设置Doxyfile.in和Doxyfile的路径
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/doc)
    set(DOXYGEN_FILE ${DOXYGEN_OUT}/Doxyfile)

    # 请求CMake配置Doxyfile
    configure_file(${DOXYGEN_IN} ${DOXYGEN_FILE} @ONLY)

    # 添加一个目标来生成API文档
    execute_process(
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILE}
        WORKING_DIRECTORY ${DOXYGEN_OUT})
else(DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)

# 执行 Python 脚本并移动生成的文件
execute_process(
  COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/syntax_gen.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts
)
