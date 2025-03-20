#include "memoryparser.h"

MemoryParser::MemoryParser()
{

}

void MemoryParser::ParseLine(const QString& line)
{
    static MemoryObject* currentObj = nullptr;

    if(findGlobal)
    {
        if(QRegularExpressionMatch match = patternForGlobSymb->match(line); match.hasMatch())
        {
            GlobalSymbol globObj;
            globObj.symbolName = match.captured(1);
            globObj.value = match.captured(2);

            if(match.captured(2)=="-")
            {
                globObj.value = "- Undefined Weak Reference";
                globalSymbols.append(globObj);
                return;
            }

            globObj.type = match.captured(3);

            if(match.captured(3) == "Thumb")
            {
                globObj.type = "Thumb Code";
                QStringList tmpStr = match.captured(6).split(' ', Qt::SkipEmptyParts);
                globObj.size = tmpStr[0];
                globObj.object = tmpStr[1];
                globalSymbols.append(globObj);
                return;
            }

            globObj.size = match.captured(5);
            globObj.object = match.captured(6);

            globalSymbols.append(globObj);
            return;
        }

    }


    if (QRegularExpressionMatch match = patternForObj->match(line); match.hasMatch())
    {
        if(findGlobal)
        {
            findGlobal = false;
        }
        MemoryObject obj;
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


    QList<QRegularExpression*> patterns = {pattern, padPattern, ramPattern, universalPattern};
    for (auto* regex : patterns)
    {
        if (QRegularExpressionMatch match = regex->match(line); match.hasMatch())
        {
            if (!currentObj) {
                qDebug() << "Ошибка: попытка добавить MemoryRegion, но нет MemoryObject!";
                return;
            }
            MemoryRegion memoryRegion;
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

    if(line.contains("Global Symbols"))
    {
        findGlobal = true;
    }

}

void MemoryParser::MemoryStateCreate()
{

    // if(memoryObjects.empty())
    // {
    //     return;
    // }

    for(uint16_t index = 0;index < globalSymbols.size();index++)
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
    ShowMemoryState();
}

void MemoryParser::ShowMemoryState()
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
