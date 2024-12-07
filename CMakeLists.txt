cmake_minimum_required(VERSION 3.10)
project(GHJSON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCES
main.cpp
json/json.cpp
json/parser.cpp
)

# include_directories(json)
# 为了分行确定输出内容
message("======================================")
message("1. NONE")
message(NOTICE "2. NOTICE")
message(STATUS "3. STATUS")
message(VERBOSE "9. VERBOSE")
message(DEBUG "10. DEBUG")
message(TRACE "11. TRACE")
message("======================================")



add_executable(GHJSON ${SOURCES})