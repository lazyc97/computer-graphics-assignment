cmake_minimum_required(VERSION 3.0)
project(computer_graphics_assignment)

set(CMAKE_CXX_STANDARD 11)

set(GLUT_glut_LIBRARY freeglut/lib/x64)
set(GLUT_INCLUDE_DIR freeglut/include)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARIES})
file(COPY freeglut/bin/x64/freeglut.dll DESTINATION ${CMAKE_BINARY_DIR})

add_executable(lab1 lab1/mainfile.cpp)
target_link_libraries(lab1 libfreeglut.a libfreeglut_static.a ${OPENGL_LIBRARIES})