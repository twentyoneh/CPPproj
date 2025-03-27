#ifndef DEFINES_H
#define DEFINES_H
#include <QString>
#include <QList>


struct MemoryRegion /// - структура для региона
{
    QString execAddr;
    QString loadAddr;
    QString size;
    QString type;
    QString accessRights;
    QString index;
    QString sectionName;
    QString objectName;
};

struct MemoryObject /// - структура для объекта региона
{
    QString name;
    uint32_t execAddr;
    uint32_t loadAddr;
    uint32_t size;
    uint32_t maxSize;
    QList<MemoryRegion>* memReg;
};

struct GlobalSymbol /// - стурктура для глобальных символов
{
    QString symbolName;
    QString value;
    QString type = "none";
    QString size = "none";
    QString object = "none";
};

struct Region
{
    QString name;
    uint32_t left, right;
    uint32_t availableSpace = right - left + 1;
    uint32_t freeSpace = availableSpace;
    QList<GlobalSymbol> globalSymbols;
};

struct MemoryState /// - структура для состояния памяти
{
    uint32_t codeSize = 0;
    uint32_t ROSize = 0;
    uint32_t RWSize = 0;
    uint32_t ZISize = 0;

    uint32_t ROMSize = 0;
    uint32_t ROMFree = 0;
    uint32_t ROMOccupied = 0;

    uint32_t RAMSize = 0;
    uint32_t RAMFree = 0;
    uint32_t RAMOccupied = 0;
};

#endif // DEFINES_H
