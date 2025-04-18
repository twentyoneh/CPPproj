#include "memoryinfo.h"

MemoryInfo::MemoryInfo(MemoryParser* parser, QWidget *parent)
    : QWidget{parent}, m_parser{parser}
{

    m_mainLayout = new QVBoxLayout(this);   /// - создание лейаутов;
    m_stateLayout = new QVBoxLayout();
    m_variableLayout = new QVBoxLayout();

    updateMainLayout("Байт"); /// - заполнение лейаутов.
    updateStateLayout("Байт");
}

void MemoryInfo::updateVariableLayout(const GlobalSymbol& variable,const QString& dimension)
{
    clearLayout(m_variableLayout);
    QList<QLabel*> labelList;   /// - создаём QList, внутри которого будут лежать данные о перменной;

    labelList.append(new QLabel("Название: " + variable.symbolName));
    for (Region& region : m_parser->listRegions)
    {
        for(GlobalSymbol& symbol : region.globalSymbols)
        {
            if(symbol.symbolName == variable.symbolName)
            {
                labelList.append(new QLabel("Название региона: " + region.name));
            }
        }
    }
    labelList.append(new QLabel("Тип: " + variable.type));
    labelList.append(new QLabel("Размер: " + formatSize(variable.size.toUInt(),dimension)));
    labelList.append(new QLabel("Начало: 0x" + variable.value.mid(2).toUpper()));
    labelList.append(new QLabel("Конец: 0x" +
                                        QString::number(variable.value.toUInt(nullptr, 16) + variable.size.toUInt(nullptr, 10), 16)
                                            .rightJustified(8, '0').toUpper()));  /// - добавляем нули слева до 8 символов
    labelList.append(new QLabel("Объектный файл: " + variable.object));

    for(QLabel* label : labelList)
    {
        m_variableLayout->addWidget(label); /// - внутрь лейаута помещаем отдельные лейблы.
    }
}

void MemoryInfo::updateMainLayout(const QString& dimension)
{
    clearLayout(m_mainLayout);
    for (Region& obj : m_parser->listRegions) {
        /// - cоздаём GroupBox для каждого региона;
        QGroupBox *regionBox = new QGroupBox(obj.name, this);
        QVBoxLayout *regionLayout = new QVBoxLayout(regionBox);
        QLabel* filledDataLable;
        QLabel* size;
        QLabel* busySpace;
        QLabel* freeSpace;

        if(obj.lastSymbol != 0)
        {
            size = new QLabel("Размер региона: " + formatSize(obj.availableSpace, dimension));
            busySpace = new QLabel("Занято: " + formatSize(obj.lastSymbol - obj.left, dimension));
            freeSpace = new QLabel("Свободно: " + formatSize(obj.right - obj.lastSymbol + 1, dimension));
        } else
        {
            /// - лейблы с информацией о размере памяти;
            size = new QLabel("Размер региона: " + formatSize(obj.availableSpace, dimension));
            busySpace = new QLabel("Занято: " + formatSize(0, dimension));
            freeSpace = new QLabel("Свободно: " + formatSize(obj.availableSpace, dimension));
        }

        QLabel* startDataLable = new QLabel("0x" + QString::number(obj.left, 16).toUpper().rightJustified(8, '0'));
        QLabel* endDataLable = new QLabel("0x" + QString::number(obj.right, 16).toUpper().rightJustified(8, '0'));
        if(obj.lastSymbol == 0)
        {
            filledDataLable = new QLabel("-");
        } else
        {
            filledDataLable = new QLabel("0x" + QString::number(obj.lastSymbol, 16).toUpper().rightJustified(8, '0'));
        }

        /// - прогресс-бар;
        float progressValue = float(obj.lastSymbol - obj.left) / float(obj.availableSpace);
        int result = progressValue * 100;

        m_progressBar = new QProgressBar(this);
        m_progressBar->setRange(0, 100);
        m_progressBar->setValue(result);

        /// - лейаут для названия и прогресс-бара;
        QVBoxLayout *containerLayout = new QVBoxLayout();
        containerLayout->addWidget(m_progressBar);

        /// - лейаут для диапазонов памяти;
        QHBoxLayout *memoryLayout = new QHBoxLayout();
        memoryLayout->addWidget(startDataLable);
        memoryLayout->addWidget(filledDataLable);
        memoryLayout->addWidget(endDataLable);

        /// - лейаут для информации о памяти;
        QVBoxLayout *sizeMemoryLayout = new QVBoxLayout();
        sizeMemoryLayout->addWidget(size);
        sizeMemoryLayout->addWidget(busySpace);
        sizeMemoryLayout->addWidget(freeSpace);

        /// - добавляем все лейауты внутрь GroupBox;
        regionLayout->addLayout(containerLayout);
        regionLayout->addLayout(memoryLayout);
        regionLayout->addLayout(sizeMemoryLayout);
        regionBox->setLayout(regionLayout);

        /// - добавляем GroupBox в основной лейаут;
        m_mainLayout->addWidget(regionBox);
    }

}

void MemoryInfo::updateVariableLayout()
{
    clearLayout(m_variableLayout);
    QList<QLabel*> labelList;   /// - создаём QList, внутри которого будут лежать данные о перменной;

    labelList.append(new QLabel("Название: -"));
    labelList.append(new QLabel("Название региона: -"));
    labelList.append(new QLabel("Тип: -"));
    labelList.append(new QLabel("Размер: -"));
    labelList.append(new QLabel("Начало: -"));
    labelList.append(new QLabel("Конец: -"));  /// - добавляем нули слева до 8 символов
    labelList.append(new QLabel("Объектный файл: -"));

    for(QLabel* label : labelList)
    {
        m_variableLayout->addWidget(label); /// - внутрь лейаута помещаем отдельные лейблы.
    }
}

void MemoryInfo::updateStateLayout(const QString& dimension)
{
    clearLayout(m_stateLayout);
    QList<QLabel*> labelList;   /// - создаём QList, внутри которого будут лежать данные о состоянии памяти;

    labelList.append(new QLabel("Общая статистика:"));
    labelList.append(new QLabel("Размер кода (Code): " + formatSize(m_parser->memoryState.codeSize, dimension)));
    labelList.append(new QLabel("Данные только для чтения (RO-data): " + formatSize(m_parser->memoryState.ROSize, dimension)));
    labelList.append(new QLabel("Изменяемые данные (RW-data): " + formatSize(m_parser->memoryState.RWSize, dimension)));
    labelList.append(new QLabel("Нульинициализированные данные (ZI-data): " + formatSize(m_parser->memoryState.ZISize, dimension)));

    labelList.append(new QLabel("\nFlash-память:"));
    labelList.append(new QLabel("Занято: " + formatSize(m_parser->memoryState.ROMOccupied, dimension)));

    labelList.append(new QLabel("\nRAM-память:"));
    labelList.append(new QLabel("Занято: " + formatSize(m_parser->memoryState.RAMOccupied, dimension)));

    for(QLabel* label : labelList)
    {
        m_stateLayout->addWidget(label);    /// - внутрь лейаута помещаем отдельные лейблы.
    }
}


QString MemoryInfo::formatSize(uint sizeInBytes, const QString &dimension)
{
    if (dimension == "Бит") {
        return QString::number(sizeInBytes * 8) + " Бит";
    } else if (dimension == "Килобайт") {
        return QString::number(sizeInBytes / 1024.0, 'f', 2) + " Килобайт";
    }
    return QString::number(sizeInBytes) + " Байт";  /// - по умолчанию, если переданы "Байт" или некорректное значение.
}

void MemoryInfo::clearLayout(QLayout *layout) {
    if (!layout)
        return;

    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->hide();  /// - скрываем перед удалением (на всякий случай);
            widget->deleteLater();  /// - безопасное асинхронное удаление;
        }
        else if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout);
            delete childLayout;  /// - удаляем только дочерний layout;
        }

        delete item;  /// - безопасное удаление item.
    }
}
