# CMakeList.txt : CMake project for sfmlSnake, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.22)

project ("sfmlSnake")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH C:/cpplibs/SFML-2.6.1)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.6.1 COMPONENTS network audio graphics window system)

add_executable (${PROJECT_NAME} "main.cpp" "snake.h" "snake.cpp")

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-network sfml-window sfml-system)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sfmlSnake PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
