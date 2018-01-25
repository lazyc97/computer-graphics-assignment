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

set(link_target libfreeglut.a libfreeglut_static.a ${OPENGL_LIBRARIES})

add_executable(lab1 lab1/mainfile.cpp)
add_executable(lab2 lab2/mainfile.cpp)
add_executable(lab3 lab3/mainfile.cpp)
add_executable(lab4 lab4/mainfile.cpp)
add_executable(lab5 lab5/mainfile.cpp)
add_executable(lab6 lab6/mainfile.cpp)
add_executable(lab7 lab7/mainfile.cpp)
target_link_libraries(lab1 ${link_target})
target_link_libraries(lab2 ${link_target})
target_link_libraries(lab3 ${link_target})
target_link_libraries(lab4 ${link_target})
target_link_libraries(lab5 ${link_target})
target_link_libraries(lab6 ${link_target})
target_link_libraries(lab7 ${link_target})