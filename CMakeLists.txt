cmake_minimum_required(VERSION 3.1)

project (cpp_project LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
link_libraries(${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra")
endif()

include_directories("include/")

add_executable(sorting_visualizer app/sorting_visualizer.cpp lib/colour.cpp)

install(TARGETS sorting_visualizer DESTINATION bin)

install(PROGRAMS demo DESTINATION bin)
