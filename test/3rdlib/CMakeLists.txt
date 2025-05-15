cmake_minimum_required(VERSION 3.16)

project(FTEST_3rd_use LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FTEST_3rd_use main.cxx)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(FTEST_3rd_use PRIVATE ws2_32 wsock32)
endif()