cmake_minimum_required(VERSION 3.16)

project(ClientCore LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
ClientCore.cxx
ClientCore.h
)

add_library(ClientCore STATIC ${SOURCES})
target_link_libraries(ClientCore PRIVATE Protocol)
