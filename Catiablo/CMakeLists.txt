cmake_minimum_required(VERSION 3.12)

# Установите имя проекта и стандарт C++
project(Catiablo)
set(CMAKE_CXX_STANDARD 17)

# Установите путь к библиотекам SFML
set(CMAKE_PREFIX_PATH "C:/cpplibs/SFML-2.6.1")
set(SFML_STATIC_LIBRARIES TRUE)

# Найдите пакеты SFML
find_package(SFML 2.6.1 COMPONENTS network audio graphics window system REQUIRED)

# Добавьте исходные файлы к исполняемому файлу проекта
add_executable(Catiablo
    "./src/main.cpp"
    "./src/Game.cpp" "./inc/Game.h"
    "./src/Menu.cpp" "./inc/Menu.h"
    "./src/Map.cpp" "./inc/Map.h"
    "./src/Player.cpp" "./inc/Player.h"
    "./src/Monster.cpp" "./inc/Monster.h"
)

# Укажите библиотеки для линковки
target_link_libraries(Catiablo sfml-graphics sfml-audio sfml-network sfml-window sfml-system)

# Укажите директории для включения заголовочных файлов
target_include_directories(Catiablo PRIVATE "./inc")