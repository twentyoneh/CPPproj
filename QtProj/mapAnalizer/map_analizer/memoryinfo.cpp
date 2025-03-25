#include "memoryinfo.h"

MemoryInfo::MemoryInfo(MemoryParser* parser, QWidget *parent)
    : QWidget{parent}, m_parser{parser}
{

    m_mainLayout = new QVBoxLayout(this);   /// - создание лейаутов;
    m_stateLayout = new QVBoxLayout();
    m_variableLayout = new QVBoxLayout();

    createMainLayout(); /// - заполнение лейаутов.
    createStateLayout();
}

void MemoryInfo::updateVariableLayout(const GlobalSymbol& variable)
{
    QList<QLabel*> labelList;   /// - создаём QList, внутри которого будут лежать данные о перменной

    labelList.append(new QLabel("Название: " + variable.symbolName));
    labelList.append(new QLabel("Тип: " + variable.type));
    labelList.append(new QLabel("Размер: " + variable.size));
    labelList.append(new QLabel("Начало: " + variable.value));
    labelList.append(new QLabel("Объектный файл: " + variable.object));

    for(QLabel* label : labelList)
    {
        m_variableLayout->addWidget(label); /// - внутрь лейаута помещаем отдельные лейблы
    }
}

void MemoryInfo::createMainLayout()
{
    for (int index = 0; index < m_parser->memoryObjects.count(); index++)   /// - парсинг всех областей памяти, установка progressBar, установка данных о регионе
    {
        float result = float(m_parser->memoryObjects.at(index).size)/float(m_parser->memoryObjects.at(index).maxSize);
        int progressValue = result*100;

        QString startDataString = QString::asprintf("0x%08x",m_parser->memoryObjects.at(index).execAddr).toUpper();
        QString endDataString = QString::asprintf("0x%08x",m_parser->memoryObjects.at(index).execAddr+m_parser->memoryObjects.at(index).size).toUpper();
        QString filledDataString = QString::asprintf("0x%08x",m_parser->memoryObjects.at(index).execAddr+m_parser->memoryObjects.at(index).maxSize).toUpper();

        QHBoxLayout *progressLayout = new QHBoxLayout();

        QLabel *label = new QLabel(m_parser->memoryObjects.at(index).name, this);
        m_progressBar = new QProgressBar(this);

        m_progressBar->setRange(0, 100);
        m_progressBar->setValue(progressValue);

        progressLayout->addWidget(label);
        progressLayout->addWidget(m_progressBar);
        m_mainLayout->addLayout(progressLayout);

        QLabel *startDataLabel = new QLabel("Начало региона: " + startDataString, this);
        QLabel *endDataLabel = new QLabel("Последний адрес записанных данных: " + endDataString, this);
        QLabel *filledDataLabel = new QLabel ("Конец региона: " + filledDataString, this);

        m_mainLayout->addWidget(startDataLabel);
        m_mainLayout->addWidget(endDataLabel);
        m_mainLayout->addWidget(filledDataLabel);
    }
}

void MemoryInfo::createStateLayout()
{
    QList<QLabel*> labelList;   /// - создаём QList, внутри которого будут лежать данные о состоянии памяти

    labelList.append(new QLabel("Общая статистика:"));
    labelList.append(new QLabel("Размер кода (Code): " + QString::number(m_parser->memoryState.codeSize)));
    labelList.append(new QLabel("Данные только для чтения (RO-data): " + QString::number(m_parser->memoryState.ROSize)));
    labelList.append(new QLabel("Иниц. знач-ями изменяемые данные (RW-data): " + QString::number(m_parser->memoryState.RWSize)));
    labelList.append(new QLabel("\nFlash-память:"));
    labelList.append(new QLabel("Размер: " + QString::number(m_parser->memoryState.ROMSize)));
    labelList.append(new QLabel("Свободно: " + QString::number(m_parser->memoryState.ROMFree)));
    labelList.append(new QLabel("Занято: " + QString::number(m_parser->memoryState.ROMOccupied)));
    labelList.append(new QLabel("\nRAM-память:"));
    labelList.append(new QLabel("Размер: " + QString::number(m_parser->memoryState.RAMSize)));
    labelList.append(new QLabel("Свободно: " + QString::number(m_parser->memoryState.RAMFree)));
    labelList.append(new QLabel("Занято: " + QString::number(m_parser->memoryState.RAMOccupied)));

    for(QLabel* label : labelList)
    {
        m_stateLayout->addWidget(label);    /// - внутрь лейаута помещаем отдельные лейблы
    }

}
