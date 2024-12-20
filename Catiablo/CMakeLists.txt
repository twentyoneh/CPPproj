# CMakeList.txt : CMake project for Catiablo, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.22)
project ("Catiablo")


set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH C:/cpplibs/SFML-2.6.1)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.6.1 COMPONENTS network audio graphics window system)

# Add source to this project's executable.
add_executable (Catiablo "./src/main.cpp" "./src/Game.cpp" "./inc/Game.h" "./src/Menu.cpp" "./inc/Menu.h" "./src/Map.cpp" "./inc/Map.h" "./src/Player.cpp" "./inc/Player.h" "./src/Monster.cpp" "./inc/Monster.h")

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-network sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PRIVATE src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Catiablo PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
