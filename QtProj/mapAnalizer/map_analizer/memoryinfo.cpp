#include "memoryinfo.h"

MemoryInfo::MemoryInfo(MemoryParser parser, QWidget *parent)
    : QWidget{parent}
{

    QVBoxLayout *mainlayout = new QVBoxLayout(this);

    for (int index = 0; index < parser.memoryObjects.count(); index++)
    {
        float result = float(parser.memoryObjects.at(index).size)/float(parser.memoryObjects.at(index).maxSize);
        int progressValue = result*100;

        QString startDataString = QString::asprintf("0x%08x",parser.memoryObjects.at(index).execAddr).toUpper();
        QString endDataString = QString::asprintf("0x%08x",parser.memoryObjects.at(index).execAddr+parser.memoryObjects.at(index).size).toUpper();
        QString filledDataString = QString::asprintf("0x%08x",parser.memoryObjects.at(index).execAddr+parser.memoryObjects.at(index).maxSize).toUpper();

        QHBoxLayout *progressLayout = new QHBoxLayout();
        QVBoxLayout *infoLayout = new QVBoxLayout();

        QLabel *label = new QLabel(parser.memoryObjects.at(index).name, this);
        progressBar = new QProgressBar(this);

        progressBar->setRange(0, 100);
        progressBar->setValue(progressValue);

        progressLayout->addWidget(label);
        progressLayout->addWidget(progressBar);
        mainlayout->addLayout(progressLayout);

        QLabel *startDataLabel = new QLabel("Начало региона: " + startDataString, this);
        QLabel *endDataLabel = new QLabel("Последний адрес записанных данных: " + endDataString, this);
        QLabel *filledDataLabel = new QLabel ("Конец региона: " + filledDataString, this);

        infoLayout->addWidget(startDataLabel);
        infoLayout->addWidget(endDataLabel);
        infoLayout->addWidget(filledDataLabel);

        mainlayout->addLayout(infoLayout);

    }
    setLayout(mainlayout);
}

void MemoryInfo::CreateMemoryStateInfo(MemoryParser parser)
{
    QVBoxLayout* mainlayout = new QVBoxLayout(this);

    QList<QLabel> lableList;

    lableList.append(QLabel("codeSize:" + QString::number(parser.memoryState.codeSize)));
    lableList.append(QLabel("ROSize: " + QString::number(parser.memoryState.ROSize)));
    lableList.append(QLabel(QString::number(parser.memoryState.RWSize)));
    lableList.append(QLabel(QString::number(parser.memoryState.ROMSize)));
    lableList.append(QLabel(QString::number(parser.memoryState.ROMFree)));
    lableList.append(QLabel(QString::number(parser.memoryState.ROMOccupied)));
    lableList.append(QLabel(QString::number(parser.memoryState.RAMSize)));
    lableList.append(QLabel(QString::number(parser.memoryState.RAMFree)));
    lableList.append(QLabel(QString::number(parser.memoryState.RAMOccupied)));

    for(int index = 0; index < lableList.count(); index++)
    {

        mainlayout->addItem(lableList.at(index));
    }
}
