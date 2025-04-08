#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "defines.h"
#include "memoryparser.h"
#include "memoryinfo.h"
#include <QFile>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QScrollBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenFile_clicked();     ///<слот для открытия файла
    void on_findVariable_clicked(); ///<слот для поиска переменной
    void updateDimension();
    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    void createStateInfoLayout();
    void createMainLayout();
    void createButtonGroup();
    void saveFilePath(const QString& path); ///<функция для сохранения FilePath
    QString LoadFilePath();  ///<функция для загрузки FilePath

    QButtonGroup* buttonGroup;
    QString filePath = nullptr; ///<сам путь к файлу
    void openFileAndParse(const QString fileName); ///<функция открытия файла и парсинга
    void fillListWidget();  ///<функция заполнения ListWidget(состояние памяти и прогрессбары)
    MemoryParser parser;    ///<объект парсера
    MemoryInfo* infoItem;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
