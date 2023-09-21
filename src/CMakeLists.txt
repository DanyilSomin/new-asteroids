cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/sdlwrap.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/sdlwrap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/sdlassert.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/sdlassert.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/moveptr.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/font.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/font.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/surface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/surface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/texture.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sdlwrap/texture.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../res/*"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
