# CMakeList.txt : CMake project for SfmlLearmCmake, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.22)
project(SfmlLearnCmake)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH C:/cpplibs/SFML-2.6.1)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.6.1 COMPONENTS network audio graphics window system)

#set(PROJ_SRC src/SfmlLearnCmake.cpp src/SfmlLearnCmake.h)
# Add source to this project's executable.
add_executable (${PROJECT_NAME} "src/main.cpp" "src/Game.cpp" "src/Player.cpp" "src/Enemy.cpp" "src/Bullet.cpp" "src/Level.cpp" "src/ResourceManager.cpp" "src/Utils.cpp" "src/Entity.cpp")
include_directories(${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-network sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PRIVATE src)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SfmlLearnCmake PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
