cmake_minimum_required(VERSION 3.16)

project(FileTransferRelay LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
Server.h
Server.cxx
main.cxx
)

add_executable(FileTransferRelay ${SOURCES})