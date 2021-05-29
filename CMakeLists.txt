cmake_minimum_required(VERSION 2.8.12)
project (graphics)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)

#Bring the headers, such as Student.h into the project
include_directories(libs/glad/include)

#The file(GLOB...) allows for wildcard additions:
file(GLOB APP_SOURCES "src/**/*.c")
file(GLOB GLAD_SOURCES "libs/glad/src/*.c")

find_package(OpenGL REQUIRED)

# Create an executable for each program in src
foreach( source_file ${APP_SOURCES} )
    # Get file name without ext
    file(RELATIVE_PATH source_file_name ${CMAKE_CURRENT_SOURCE_DIR}/src ${source_file})
    string( REPLACE ".c" "" source_file_bin ${source_file_name} )
    string( REPLACE "/" "-" source_file_bin ${source_file_bin} )

    add_executable( ${source_file_bin} ${source_file} ${GLAD_SOURCES})

    # Make sure YourLib is linked to each app
    target_link_libraries( ${source_file_bin} ${OPENGL_gl_LIBRARY} glfw )
endforeach( source_file ${APP_SOURCES} )
