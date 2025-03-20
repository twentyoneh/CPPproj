#ifndef MEMORYPARSER_H
#define MEMORYPARSER_H

#include "defines.h"
#include <QRegularExpression>

class MemoryParser {
public:
    MemoryParser();

    QList<MemoryObject> memoryObjects;
    QList<GlobalSymbol> globalSymbols;
    MemoryState memoryState;
    void ParseLine(const QString& line);
    void MemoryStateCreate();
    void ShowMemoryState();

private:
    bool findGlobal = false;

    QRegularExpression* patternForGlobSymb = new QRegularExpression( /// - паттерн для нахожденеия глобальных символов
        R"(^\s*(\S+)\s+(\-|\b0x[0-9A-Fa-f]+\b)\s+(\S+)\s*(\d+)?\s*(\S+)?\s*(.+)?$)"
        );
    QRegularExpression* patternForObj = new QRegularExpression(
        R"(Execution Region (\S+) \(Exec base:\s*(0x[0-9A-Fa-f]+),\s*Load base:\s*(0x[0-9A-Fa-f]+),\s*Size:\s*(0x[0-9A-Fa-f]+),\s*Max:\s*(0x[0-9A-Fa-f]+).*\))"
        );

    QRegularExpression* pattern = new QRegularExpression(
        R"(\s*(0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)\s+(\w+)\s+(\w+)\s+(\d+)\s+([\w\.\$\-]+)\s+([\w\.]+))"
        );

    QRegularExpression* padPattern = new QRegularExpression(
        R"(\s*(0x[0-9A-Fa-f]+)\s+(COMPRESSED|0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)\s+(\w+))"
        );

    QRegularExpression* ramPattern = new QRegularExpression(
        R"(\s*(0x[0-9A-Fa-f]+)\s+\-\s+(0x[0-9A-Fa-f]+)\s+(\w+)(?:\s+(\w+))?(?:\s+(\d+))?(?:\s+([\w\.\$\-]+))?(?:\s+([\w\.]+))?")"
        );

    QRegularExpression* universalPattern = new QRegularExpression(
        R"(\s*(0x[0-9A-Fa-f]+)\s+(-|COMPRESSED|0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)\s+(\w+)\s+(\w+)\s+(\d+)\s+([\w\.\$\-]+(?:__AT_0x[0-9A-Fa-f]+)?)\s+([\w\.\(\)]+))"
        );


};

#endif // MEMORYPARSER_H
