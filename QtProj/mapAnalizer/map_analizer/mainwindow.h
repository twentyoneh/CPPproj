#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "defines.h"
#include "memoryparser.h"
#include "memoryinfo.h"
#include <QFile>
#include <QFileDialog>

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
    void on_OpenFIle_clicked();

    void on_findVariable_clicked();

private:
    QString filePath = nullptr;
    void openFileAndParse(const QString fileName);
    void fillListWidget(MemoryParser _parser);
    MemoryParser parser;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
