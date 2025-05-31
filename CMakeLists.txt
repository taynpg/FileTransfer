cmake_minimum_required(VERSION 3.16)

project(FileTransfer VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
add_compile_options(/utf-8)
endif()

if(WIN32)
execute_process(COMMAND cmd /c ver
    OUTPUT_VARIABLE VER_OUTPUT
    OUTPUT_STRIP_TRAILING_WHITESPACE)
if(VER_OUTPUT MATCHES "XP")
    message(STATUS "Windows XP platform.")
    #add_definitions(-D_WIN32_WINNT=0x0501)
else()
    message(STATUS "Windows NT platform.")
    #add_definitions(-D_WIN32_WINNT=0x0601)
endif()
endif()

set(CMAKE_DEBUG_POSTFIX "d")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/) 

add_definitions(-DFMT_HEADER_ONLY)
include_directories(3rd)
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(Information)
include_directories(ClientInterface)

add_subdirectory(Protocol)
add_subdirectory(Gui)
add_subdirectory(Util)
add_subdirectory(ClientCore)
add_subdirectory(Console)
add_subdirectory(Server)
add_subdirectory(Test)
