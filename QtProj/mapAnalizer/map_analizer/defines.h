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

struct MemoryState /// - структура для состояния памяти
{
    uint32_t codeSize;
    uint32_t ROSize;
    uint32_t RWSize;
    uint32_t ZISize;

    uint32_t ROMSize;
    uint32_t ROMFree;
    uint32_t ROMOccupied;

    uint32_t RAMSize;
    uint32_t RAMFree;
    uint32_t RAMOccupied;
};

#endif // DEFINES_H
