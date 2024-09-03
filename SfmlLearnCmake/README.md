2d шутер вид - сверху 

SfmlLearnCmake/
├── CMakeLists.txt          # Файл конфигурации CMake (если используете CMake)
├── .gitignore              # Файл для исключения из системы контроля версий
├── assets/                 # Папка для всех игровых ресурсов
│   ├── images/             # Изображения (текстуры)
│   ├── sounds/             # Звуковые эффекты и музыка
│   ├── fonts/              # Шрифты
│   └── levels/             # Уровни и другая игровая логика (например, файлы карт)
├── build/                  # Директория для сборки (добавляется в .gitignore)
├── include/                # Заголовочные файлы проекта
│   ├── Game.hpp            # Основной игровой класс
│   ├── Player.hpp          # Класс игрока
│   ├── Enemy.hpp           # Класс врагов
│   ├── Bullet.hpp          # Класс пули
│   ├── Level.hpp           # Класс уровня
│   ├── ResourceManager.hpp # Класс управления ресурсами (текстуры, звуки и т.д.)
│   └── Utils.hpp           # Вспомогательные функции и утилиты
├── src/                    # Исходные файлы проекта
│   ├── main.cpp            # Главный файл с точкой входа в программу
│   ├── Game.cpp            # Реализация основного игрового класса
│   ├── Player.cpp          # Реализация класса игрока
│   ├── Enemy.cpp           # Реализация класса врагов
│   ├── Bullet.cpp          # Реализация класса пули
│   ├── Level.cpp           # Реализация класса уровня
│   ├── ResourceManager.cpp # Реализация управления ресурсами
│   └── Utils.cpp           # Реализация вспомогательных функций и утилит
└── README.md               # Описание проекта

Детали структуры
assets/: Эта папка содержит все ресурсы, которые нужны для игры. Она может быть разделена на подкаталоги, такие как images для изображений, sounds для звуков, fonts для шрифтов и levels для данных уровней.

include/: Здесь находятся все заголовочные файлы проекта. Каждый основной класс или компонент игры имеет свой заголовочный файл. Это помогает в структурировании кода и его повторном использовании.

src/: Содержит все исходные файлы (.cpp). Каждый файл обычно соответствует заголовочному файлу из папки include/. Например, Game.cpp реализует методы, определенные в Game.hpp.

CMakeLists.txt: Если вы используете CMake для сборки проекта, здесь будет находиться файл конфигурации CMake, который описывает, как собирать проект. Если вы используете другой инструмент сборки, такой как Makefile, его можно также разместить в корневой директории.

build/: Директория для выходных файлов сборки. Эта директория, как правило, добавляется в .gitignore и не хранится в системе контроля версий.

.gitignore: Файл для исключения файлов и папок из системы контроля версий (например, build/, временные файлы и т. д.).

README.md: Файл с описанием проекта. В этом файле можно указать информацию о проекте, инструкции по установке и запуску, зависимостях и т.д.

```Game.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Level.hpp"
#include "ResourceManager.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    sf::RenderWindow window;			//Само окно
    Player player;						//Игрок
    std::vector<Enemy> enemies;			//Враги
    std::vector<Bullet> bullets;		//Пули
    Level currentLevel;					//На каком уровне находится игрок
    ResourceManager resourceManager;	//Загрузка шрифтов && музыки и прочего 
};

```

```ResourceManager.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    // Загружает текстуру из файла, если она еще не загружена
    sf::Texture& loadTexture(const std::string& name, const std::string& filename);
    
    // Возвращает ссылку на загруженную текстуру
    sf::Texture& getTexture(const std::string& name);

private:
    // Контейнер для хранения текстур
    std::unordered_map<std::string, sf::Texture> textures;
};

```