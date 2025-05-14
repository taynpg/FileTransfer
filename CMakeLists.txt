cmake_minimum_required(VERSION 3.16)

project(FileTransfer VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
add_compile_options(/utf-8)
endif()

set(CMAKE_DEBUG_POSTFIX "d")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/) 

include_directories(3rd)
include_directories(Information)
include_directories(ClientInterface)

add_subdirectory(Protocol)
add_subdirectory(Gui)
add_subdirectory(ClientCore)
add_subdirectory(Test)
