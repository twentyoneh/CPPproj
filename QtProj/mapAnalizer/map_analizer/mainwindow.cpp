#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileAndParse(const QString fileName)
{
    QFile file(fileName);   /// - пытаемся открыть файл;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file!";
    }
    QTextStream in(&file);  /// - создали текстовый поток который будем загружать в наш парсер;

    while (!in.atEnd()) {   /// - пока внутри текстового потока что-то есть
        QString line = in.readLine();    /// - берём строку из потока
        parser.parseLine(line); /// - отдаём его парсеру
    }

    // qDebug() << parser.memoryObjects.count();
    parser.memoryStateCreate(); /// - создаём состояние памяти

    file.close();
}

void MainWindow::fillListWidget()
{
    MemoryInfo *infoItem = new MemoryInfo(&parser); /// - infoItem объект внутри котого у нас будут хранится все визуальные представления структур описанные внутри defines.h;
    /// - создаю обертку QWidget над моим QLayout, чтобы потом засунуть QWidget в QListWidgetItem, который в свою очередь отобразится внутри QListWidget;
    QWidget* mainWidget = new QWidget();    /// - основной виджет, внутри него состояния областей памяти(progressbar);
    mainWidget->setLayout(infoItem->getMainLayout());

    QListWidgetItem* mainListWidgetItem = new QListWidgetItem(ui->mainListWidget);
    mainListWidgetItem->setSizeHint(infoItem->getMainLayout()->sizeHint());
    ui->mainListWidget->addItem(mainListWidgetItem);
    ui->mainListWidget->setItemWidget(mainListWidgetItem, mainWidget);

    QWidget* stateWidget = new QWidget();   /// - аналогичные действия, только для состояния памяти.
    stateWidget->setLayout(infoItem->getStateLayout());

    QListWidgetItem* stateListWidgetItem = new QListWidgetItem(ui->stateInfoList);
    stateListWidgetItem->setSizeHint(infoItem->getStateLayout()->sizeHint());
    ui->stateInfoList->addItem(stateListWidgetItem);
    ui->stateInfoList->setItemWidget(stateListWidgetItem, stateWidget);
}

void MainWindow::on_OpenFile_clicked()
{
    QString lastPath = LadFilePath(); /// - открываем файл, сохраняем его в QSettings;
    filePath = QFileDialog::getOpenFileName(this, "Выберите файл", lastPath, "Все файлы (*.*)");
    if(!filePath.isEmpty()) /// - если файл не Empty;
    {
        saveFilePath(filePath);     /// - сохраняем последний открытый файл;
        openFileAndParse(filePath); /// - чтение и парсинг файла;
        fillListWidget(); /// - заполнение листа данными из парсинга;
    }
    else
    {
        QMessageBox msgBox; /// - в случае если не отрыли файл - показать QMessageBox.
        msgBox.setText("Не выбран .map файл!");
        msgBox.exec();
    }
}


void MainWindow::on_findVariable_clicked()
{
    QString name = ui->variableName->text();    /// - забираем из текстового поля название переменной;
    for (const GlobalSymbol &out : parser.globalSymbols)    /// - проходим по всему листу globalSymbols, каждый элемент становится out;
    {
        if (out.symbolName == name) {   /// - если мы нашли нужную нам переменную - распарсим нашу переменную и выведем информацию о ней;
            ui->variableInfoList->clear();
            MemoryInfo *infoItem = new MemoryInfo(&parser);
            infoItem->updateVariableLayout(out);   /// - у отрисовщика вызываем метод который обновляет данные о переменной в gui;

            QWidget* variableWidget = new QWidget();  /// - логика аналогичная fillListWidget().
            variableWidget->setLayout(infoItem->getVariableLayout());

            QListWidgetItem* variableListWidgetItem = new QListWidgetItem(ui->variableInfoList);
            variableListWidgetItem->setSizeHint(infoItem->getVariableLayout()->sizeHint());
            ui->variableInfoList->addItem(variableListWidgetItem);
            ui->variableInfoList->setItemWidget(variableListWidgetItem, variableWidget);
            break;
        }
    }
}

void MainWindow::saveFilePath(const QString &path)
{
    QSettings settings("MyCompany", "MyApp");
    settings.setValue("lastFilePath", path);
}

QString MainWindow::LadFilePath()
{
    QSettings settings("MyCompany", "MyApp");
    return settings.value("lastFilePath", "").toString();
}

