#include "memoryparser.h"

MemoryParser::MemoryParser()
{
    STMSettings.append({
        "STM32H743IIK6",
        {
            {"Flash memory bank 1", 0x08000000, 0x080FFFFF},
            {"Flash memory bank 2", 0x08100000, 0x081FFFFF},
            {"DTCM", 0x20000000, 0x2001FFFF},
            {"AXI SRAM", 0x24000000, 0x2407FFFF},
            {"SRAM1", 0x30000000, 0x3001FFFF},
            {"SRAM2", 0x30020000, 0x3003FFFF},
            {"SRAM3", 0x30040000, 0x30047FFF}
        }
    });

    STMSettings.append({
        "STM32F103C8T6",
        {
            {"Flash memory bank 1", 0x08000000, 0x080FFFFF},
            {"Flash memory bank 2", 0x08100000, 0x081FFFFF},
            {"DTCM", 0x20000000, 0x2001FFFF},
            {"AXI SRAM", 0x24000000, 0x2407FFFF},
            {"SRAM1", 0x30000000, 0x3001FFFF}
        }
    });

    changeListRegions("STM32H743IIK6");

}

void MemoryParser::parseLine(const QString& line)
{
    static MemoryObject* currentObj = nullptr;

    if(findGlobal)  /// - парсинг всех данных которые находятся ниже Global Symbols;
    {
        if(QRegularExpressionMatch match = patternForGlobSymb->match(line); match.hasMatch())   /// если внутри строчки есть линия которая соответствует регулярному выражению;
        {
            GlobalSymbol globObj;   /// - создать объект GlobalSymbol, заполняем объект соотвецтвующими полями;
            globObj.symbolName = match.captured(1);

            if(match.captured(2)=="-")
            {
                globObj.value = "- Undefined Weak Reference";
                globalSymbols.append(globObj);
                return;
            }

            globObj.value = match.captured(2);
            globObj.type = match.captured(3);

            if(match.captured(3) == "Thumb")
            {
                globObj.type = "Thumb Code";
                QStringList tmpStr = match.captured(6).split(' ', Qt::SkipEmptyParts);
                globObj.size = tmpStr[0];
                globObj.object = tmpStr[1];
                globalSymbols.append(globObj);
                for (Region& region : listRegions) {
                    if (globObj.value.toUInt(nullptr,16) >= region.left && globObj.value.toUInt(nullptr,16) <= region.right) {
                        region.globalSymbols.append(globalSymbols.last());
                        region.freeSpace -= globObj.size.toUInt();
                        return;
                    }
                }
                return;
            }

            globObj.size = match.captured(4);
            globObj.object = match.captured(5);

            globalSymbols.append(globObj);

            for (Region& region : listRegions) {
                if (globObj.value.toUInt(nullptr,16) >= region.left && globObj.value.toUInt(nullptr,16) <= region.right) {
                    region.globalSymbols.append(globalSymbols.last());
                    region.freeSpace -= globObj.size.toUInt();
                    return;
                }
            }
            return;
        }
    }
    /// - если нашли строку соответствующую:
    /// - Execution Region RW_IRAM2 (Exec base: 0x24000000, Load base: 0x0803f63c, Size: 0x00077d24, Max: 0x00080000, ABSOLUTE, COMPRESSED[0x0000020c])
    if (QRegularExpressionMatch match = patternForObj->match(line); match.hasMatch())
    {
        if(findGlobal)  /// - чтобы одно регулярное выражение не наслаивалось на другое;
        {
            findGlobal = false;
        }
        MemoryObject obj;   /// - создаём объект Execution Region, заполняем его;
        obj.name = match.captured(1);
        obj.execAddr = match.captured(2).toUInt(0, 16);
        obj.loadAddr = match.captured(3).toUInt(0, 16);
        obj.size = match.captured(4).toUInt(0, 16);
        obj.maxSize = match.captured(5).toUInt(0, 16);
        obj.memReg = new QList<MemoryRegion>;

        memoryObjects.append(obj);
        currentObj = &memoryObjects.last();
        return;
    }

    for (auto* regex : patterns)
    {
        if (QRegularExpressionMatch match = regex->match(line); match.hasMatch())
        {
            if (!currentObj) {  /// - если не найдено Execution Region до входа в парсинг его элементов;
                qDebug() << "Ошибка: попытка добавить MemoryRegion, но нет MemoryObject!";
                return;
            }
            MemoryRegion memoryRegion;  /// - создаём объект memoryRegion, заполняем его поля;
            memoryRegion.execAddr = match.captured(1);
            memoryRegion.loadAddr = match.captured(2);
            memoryRegion.size = match.captured(3);
            memoryRegion.type = match.captured(4);
            memoryRegion.accessRights = match.captured(5);
            memoryRegion.index = match.captured(6);
            memoryRegion.sectionName = match.captured(7);
            memoryRegion.objectName = match.captured(8);

            currentObj->memReg->append(memoryRegion);
            return;
        }
    }

    if(line.contains("Global Symbols")) /// - для поиска внутри Global Symbols.
    {
        findGlobal = true;
    }
}

void MemoryParser::memoryStateCreate()
{

    for(uint16_t index = 0;index < globalSymbols.size();index++)    /// - заполнение объекта memoryState;
    {
        if(globalSymbols.at(index).type.contains("Thumb Code"))
        {
            memoryState.codeSize += globalSymbols.at(index).size.toUInt();
        }
    }
    for(uint16_t index = 0; index < memoryObjects.count(); index++)
    {
        MemoryObject* tmpMemObj = new MemoryObject(memoryObjects.at(index));
        if(tmpMemObj->name.contains("ROM"))
        {
            memoryState.ROMSize += tmpMemObj->maxSize;
            memoryState.ROMOccupied += tmpMemObj->size;
        }
        else if(tmpMemObj->name.contains("RAM"))
        {
            memoryState.RAMSize += tmpMemObj->maxSize;
            memoryState.RAMOccupied += tmpMemObj->size;
        }
        memoryState.ROMFree = memoryState.ROMSize - memoryState.ROMOccupied;
        memoryState.RAMFree = memoryState.RAMSize - memoryState.RAMOccupied;

        for(uint16_t i = 0; i < tmpMemObj->memReg->count(); i++)
        {
            if(tmpMemObj->memReg->at(i).accessRights.contains("RO"))
            {
                memoryState.ROSize += tmpMemObj->memReg->at(i).size.toUInt(0,16);
            }
            else if(tmpMemObj->memReg->at(i).accessRights.contains("RW"))
            {
                memoryState.RWSize += tmpMemObj->memReg->at(i).size.toUInt(0,16);
            }
        }
        tmpMemObj = nullptr;
    }
    showMemoryState();
}

void MemoryParser::showMemoryState()    /// - функция для отладки
{
    qDebug() << "MemoryState:";
    qDebug() << "  codeSize:" << memoryState.codeSize;
    qDebug() << "  ROSize:" << memoryState.ROSize;
    qDebug() << "  RWSize:" << memoryState.RWSize;
    qDebug() << "  ZISize:" << memoryState.ZISize;

    qDebug() << "  ROMSize:" << memoryState.ROMSize;
    qDebug() << "  ROMFree:" << memoryState.ROMFree;
    qDebug() << "  ROMOccu:" << memoryState.ROMOccupied;

    qDebug() << "  RAMSize:" << memoryState.RAMSize;
    qDebug() << "  RAMFree:" << memoryState.RAMFree;
    qDebug() << "  RAMOccu:" << memoryState.RAMOccupied;
}

void MemoryParser::changeListRegions(const QString &name)
{
    for (const auto& pair : STMSettings) {  /// - поиск нужного элемента
        if (pair.first.contains(name)) {
            listRegions = pair.second;
            break;
        }
    }
}

