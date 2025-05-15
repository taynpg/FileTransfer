cmake_minimum_required(VERSION 3.16)

project(FileTransferConsole LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
Console.h
Console.cxx
main.cxx
)

add_executable(FileTransferConsole ${SOURCES})