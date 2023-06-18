cmake_minimum_required(VERSION 3.15)
project(toy)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
###############################################################################
# flex && bison
execute_process(
    COMMAND bison --language=c++ -d "${CMAKE_CURRENT_SOURCE_DIR}/grammar/toy.y"
    COMMAND cp -rf "${CMAKE_CURRENT_SOURCE_DIR}/grammar/toy.tab.cc" "${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/"
    COMMAND cp -rf "${CMAKE_CURRENT_SOURCE_DIR}/grammar/toy.tab.hh" "${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/"
    COMMAND flex -+ "${CMAKE_CURRENT_SOURCE_DIR}/grammar/toy.l"
    COMMAND cp -rf "${CMAKE_CURRENT_SOURCE_DIR}/grammar/lex.yy.cc" "${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/"
)
###############################################################################
# for toy
file(GLOB ast "${CMAKE_CURRENT_SOURCE_DIR}/src/ast/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/ast/*.cpp")
file(GLOB grammar "${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/*.hh" "${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/*.cc")
source_group(ast FILES ${ast})
source_group(grammar FILES ${grammar})
add_executable(toy ${ast})
set_target_properties(toy PROPERTIES LINKER_LANGUAGE CXX)
###############################################################################
# for unittest