cmake_minimum_required(VERSION 3.16)

project(ClientCore LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
ClientCore.cxx
ClientCore.h
)

add_library(ClientCore STATIC ${SOURCES})
target_link_libraries(ClientCore PRIVATE Protocol Util)
target_include_directories(ClientCore PUBLIC ${CMAKE_CURRENT_LIST_DIR})
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(ClientCore PRIVATE ws2_32 wsock32)
endif()