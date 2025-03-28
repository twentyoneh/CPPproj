#ifndef MEMORYINFO_H
#define MEMORYINFO_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QGroupBox>
#include <memoryparser.h>

class MemoryInfo : public QWidget
{
    Q_OBJECT
public:
    explicit MemoryInfo(MemoryParser* parser,QWidget *parent = nullptr);

    void updateVariableLayout(const GlobalSymbol& variable,const QString& dimension); ///<метод для обновления лейаута
    void updateStateLayout(const QString& dimension);

    QVBoxLayout* getMainLayout() const { return m_mainLayout; } ///<геттеры для возвращения лейаута
    QVBoxLayout* getStateLayout() const { return m_stateLayout; }
    QVBoxLayout* getVariableLayout() const { return m_variableLayout; }

// public slots:
//     void updateDimension(const QString& dimension);

private:
    QString formatSize(uint sizeInBytes, const QString& dimension);
    void createMainLayout();
    void clearLayout(QLayout* layout);
    QVBoxLayout* m_mainLayout;  ///<главный лейаут(внтури расположены прогресс бары)
    QVBoxLayout* m_stateLayout; ///<лейаут сосояния памяти
    QVBoxLayout* m_variableLayout;  ///<лейаут поиска переменной

    QProgressBar* m_progressBar; ///<образец progressBar
    MemoryParser* m_parser; ///<поле с парсером, где хранятся все структуры которые нам нужны

signals:
};

#endif // MEMORYINFO_H
