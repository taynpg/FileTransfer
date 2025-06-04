cmake_minimum_required(VERSION 3.16)

project(Util LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Util STATIC Util.cxx Util.h LocalFile.h LocalFile.cxx)
target_include_directories(Util PUBLIC ${CMAKE_CURRENT_LIST_DIR})