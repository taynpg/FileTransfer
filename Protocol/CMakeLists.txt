cmake_minimum_required(VERSION 3.16)

project(Protocol VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
Protocol.cxx
Protocol.h
)

add_library(Protocol STATIC ${SOURCES})
target_include_directories(Protocol PUBLIC ${CMAKE_CURRENT_LIST_DIR})
