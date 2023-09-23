cmake_minimum_required(VERSION 3.16)

add_subdirectory(sdlw)

add_library(HFSM2 INTERFACE)
target_include_directories(HFSM2 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/HFSM2/include
)
