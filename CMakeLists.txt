cmake_minimum_required(VERSION 3.20)
project(gladdened)
set(CMAKE_C_STANDARD 99)

file(GLOB out shaders/*)
foreach (o ${out})
    message("${o} was copied to shaders")
    file(COPY ${o} DESTINATION shaders)
endforeach ()

add_subdirectory(glad/cmake)
add_subdirectory(glfw)

glad_add_library(soGlad PUBLIC STATIC API gl:compatibility=4.5)

add_executable(a
        main.c
        opengl.c)
target_link_libraries(a PRIVATE soGlad glfw)
target_link_directories(a PRIVATE soGlad)
target_include_directories(a PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_compile_definitions(a PRIVATE _DEBUG)