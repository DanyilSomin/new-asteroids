cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sdlw::sdlw
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../res/*"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
