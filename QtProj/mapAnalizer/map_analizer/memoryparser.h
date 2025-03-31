#ifndef MEMORYPARSER_H
#define MEMORYPARSER_H

#include "defines.h"
#include <QRegularExpression>

class MemoryParser {
public:
    MemoryParser();

    QList<MemoryObject> memoryObjects; ///<список для объектов Memory Map of the image
    QList<GlobalSymbol> globalSymbols; ///<список для спаршенных глобальных переменнных
    QList<Region> listRegions;  ///<Список регионов (как они обозначены в МК)
    MemoryState memoryState; ///<переменная для информиции о состоянии памяти STM32

    void parseLine(const QString& line);
    void memoryStateCreate();
    void showMemoryState();
    void changeListRegions(const QString& name);

private:

    QList<QPair<QString,QList<Region>>> STMSettings;  ///<У каждой stm будет своё название и регион который ей соотвецтвует
    bool findGlobal = false; ///<флаг о нахождении
    /// - сайт для проверки паттернов https://regex101.com/
    /// - регулятрное выражение для паттерна для парсинга Memory Map of the image
    QRegularExpression* pattern = new QRegularExpression(
        R"(\s*(0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)\s+(\w+)\s+(\w+)\s+(\d+)\s+([\w\.\$\-]+)\s+([\w\.]+))"
        );

    /// - паттерн для поиска внутри Global Symbols
    QRegularExpression* patternForGlobSymb = new QRegularExpression(
        R"(^\s*(\S+)\s+(\-|\b0x[0-9A-Fa-f]+\b)\s+(\S+)\s*(\d+)?\s*(\S+)?\s*(.+)?$)"
        );

    /// - паттерн для получения информации о регионе Execution Region
    QRegularExpression* patternForObj = new QRegularExpression(
        R"(Execution Region (\S+) \(Exec base:\s*(0x[0-9A-Fa-f]+),\s*Load base:\s*(0x[0-9A-Fa-f]+),\s*Size:\s*(0x[0-9A-Fa-f]+),\s*Max:\s*(0x[0-9A-Fa-f]+).*\))"
        );

    /// - паттерн дял PAD(padding)
    QRegularExpression* padPattern = new QRegularExpression(
        R"(\s*(0x[0-9A-Fa-f]+)\s+(COMPRESSED|0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)\s+(\w+))"
        );

    /// - паттерн для парсинга данных IRAM
    QRegularExpression* ramPattern = new QRegularExpression(
        R"(\s*(0x[0-9A-Fa-f]+)\s+\-\s+(0x[0-9A-Fa-f]+)\s+(\w+)(?:\s+(\w+))?(?:\s+(\d+))?(?:\s+([\w\.\$\-]+))?(?:\s+([\w\.]+))?")"
        );

    /// - паттерн для парсинга внутри IRAM, если на месте LoadAddr стот -; COMPRESSED и прочие варианты строки, которые не вошли в 2 паттерна выше
    QRegularExpression* universalPattern = new QRegularExpression(
        R"(\s*(0x[0-9A-Fa-f]+)\s+(-|COMPRESSED|0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)\s+(\w+)\s+(\w+)\s+(\d+)\s+([\w\.\$\-]+(?:__AT_0x[0-9A-Fa-f]+)?)\s+([\w\.\(\)]+))"
        );


    QList<QRegularExpression*> patterns = {pattern, padPattern, ramPattern, universalPattern};  /// - набор паттернов для парсинга элементов внутри Execution Region;

};

#endif // MEMORYPARSER_H
