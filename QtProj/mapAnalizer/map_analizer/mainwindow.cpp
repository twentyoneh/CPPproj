#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openFileAndParse("Project_CAM.map");
    fillListWidget(parser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileAndParse(const QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file!";
    }
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        parser.parseLine(line);
    }

    qDebug() << parser.memoryObjects.count();

    file.close();
}

void MainWindow::fillListWidget(MemoryParser _parser)
{
    MemoryInfo *infoItem = new MemoryInfo(_parser);
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    // MemoryInfo *infoItem = new MemoryInfo(_parser, i);

    item->setSizeHint(infoItem->sizeHint());
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, infoItem);
}

void MainWindow::on_OpenFIle_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::homePath(), "Все файлы (*.*)");


}


void MainWindow::on_findVariable_clicked()
{
    QString name = ui->variableName->text();
    for (const GlobalSymbol &out : parser.globalSymbols)
    {
        if (out.symbolName == name) {
            qDebug() << "Найден:" << out.symbolName;
            break;
        }
    }
}

