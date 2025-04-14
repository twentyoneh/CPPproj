#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createButtonGroup();

    ui->mainListWidget->verticalScrollBar()->setSingleStep(10);

    connect(buttonGroup, &QButtonGroup::buttonClicked,
            this,&MainWindow::updateDimension);

    infoItem = new MemoryInfo(&parser);
    fillListWidget();
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
    // parser.memoryStateCreate(); /// - создаём состояние памяти

    file.close();
}

void MainWindow::fillListWidget()
{
    ui->stateInfoList->clear();
    infoItem->updateStateLayout(buttonGroup->checkedButton()->text());
    createStateInfoLayout();

    ui->mainListWidget->clear();
    infoItem->updateMainLayout(buttonGroup->checkedButton()->text());
    createMainLayout();

}

void MainWindow::on_OpenFile_clicked()
{
    QString lastPath = LoadFilePath(); /// - открываем файл, сохраняем его в QSettings;
    filePath = QFileDialog::getOpenFileName(this, "Выберите файл", lastPath, "Файлы .map (*.map)");
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
    bool foundFlag = false;
    QString name = ui->variableName->text();    /// - забираем из текстового поля название переменной;
    for (const GlobalSymbol &out : parser.globalSymbols)    /// - проходим по всему листу globalSymbols, каждый элемент становится out;
    {
        if (out.symbolName == name) {   /// - если мы нашли нужную нам переменную - распарсим нашу переменную и выведем информацию о ней;
            foundFlag = true;
            ui->variableInfoList->clear();
            infoItem->updateVariableLayout(out,buttonGroup->checkedButton()->text());   /// - у отрисовщика вызываем метод который обновляет данные о переменной в gui;
            createVariableLayout();
            break;
        }
    }
    if(!foundFlag)
    {
        ui->variableInfoList->clear();
        infoItem->updateVariableLayout();
        createVariableLayout();
    }
}

void MainWindow::updateDimension()
{
    if(ui->mainListWidget->count() == 0)
    {
        return;
    }
    ui->stateInfoList->clear();
    infoItem->updateStateLayout(buttonGroup->checkedButton()->text());
    createStateInfoLayout();

    ui->mainListWidget->clear();
    infoItem->updateMainLayout(buttonGroup->checkedButton()->text());
    createMainLayout();

    on_findVariable_clicked();
}

void MainWindow::createButtonGroup()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);  // Обеспечивает выбор только одного элемента

    QStringList options = {"Бит", "Байт", "Килобайт"};
    QRadioButton *selectedButton = nullptr;
    for (const QString &option : options) {
        QRadioButton *radioButton = new QRadioButton(option, this);
        layout->addWidget(radioButton);
        buttonGroup->addButton(radioButton);
        if (option == "Байт") selectedButton = radioButton;
    }
    selectedButton->setChecked(true);
    ui->buttonWidget->setLayout(layout);

}

void MainWindow::saveFilePath(const QString &path)
{
    QSettings settings("MyCompany", "MyApp");
    settings.setValue("lastFilePath", path);
}

QString MainWindow::LoadFilePath()
{
    QSettings settings("MyCompany", "MyApp");
    return settings.value("lastFilePath", "").toString();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &name)
{
    parser.changeListRegions(name);
    fillListWidget();
}

void MainWindow::createVariableLayout()
{
    QWidget* variableWidget = new QWidget();  /// - логика аналогичная fillListWidget().
    variableWidget->setLayout(infoItem->getVariableLayout());

    QListWidgetItem* variableListWidgetItem = new QListWidgetItem(ui->variableInfoList);
    variableListWidgetItem->setSizeHint(infoItem->getVariableLayout()->sizeHint());
    ui->variableInfoList->addItem(variableListWidgetItem);
    ui->variableInfoList->setItemWidget(variableListWidgetItem, variableWidget);
}

void MainWindow::createStateInfoLayout()
{
    QWidget* stateWidget = new QWidget();   /// - аналогичные действия, только для состояния памяти.
    stateWidget->setLayout(infoItem->getStateLayout());

    QListWidgetItem* stateListWidgetItem = new QListWidgetItem(ui->stateInfoList);
    stateListWidgetItem->setSizeHint(infoItem->getStateLayout()->sizeHint());
    ui->stateInfoList->addItem(stateListWidgetItem);
    ui->stateInfoList->setItemWidget(stateListWidgetItem, stateWidget);
}

void MainWindow::createMainLayout()
{
    QWidget* mainWidget = new QWidget();    /// - основной виджет, внутри него состояния областей памяти(progressbar);
    mainWidget->setLayout(infoItem->getMainLayout());

    QListWidgetItem* mainListWidgetItem = new QListWidgetItem(ui->mainListWidget);
    mainListWidgetItem->setSizeHint(infoItem->getMainLayout()->sizeHint());
    ui->mainListWidget->addItem(mainListWidgetItem);
    ui->mainListWidget->setItemWidget(mainListWidgetItem, mainWidget);
}

