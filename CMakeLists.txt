cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "60vfs")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME}
    60vfs.cpp
)

include(FetchContent)
FetchContent_Declare(SimZip
        GIT_REPOSITORY https://github.com/L-Super/SimZip.git
        GIT_TAG "main")
FetchContent_MakeAvailable(SimZip)

target_link_libraries(${PROJECT_NAME} SimZip)
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

