cmake_minimum_required(VERSION 3.20)
project(gladdened)
set(CMAKE_C_STANDARD 99)

add_subdirectory(glad/cmake)
add_subdirectory(glfw)

glad_add_library(soGlad PUBLIC STATIC API gl:compatibility=4.5)

add_executable(a main.c)
target_link_libraries(a LINK_PUBLIC soGlad glfw)
target_link_directories(a PRIVATE soGlad)

target_include_directories (a PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
