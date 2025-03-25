#ifndef MEMORYINFO_H
#define MEMORYINFO_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <memoryparser.h>

class MemoryInfo : public QWidget
{
    Q_OBJECT
public:
    explicit MemoryInfo(MemoryParser* parser,QWidget *parent = nullptr);

    void updateVariableLayout(const GlobalSymbol* variable); ///<метод для обновления лейаута

    QVBoxLayout* getMainLayout() const { return m_mainLayout; } ///<геттеры для возвращения лейаута
    QVBoxLayout* getStateLayout() const { return m_stateLayout; }
    QVBoxLayout* getVariableLayout() const { return m_variableLayout; }

private:
    void createMainLayout();
    void createStateLayout();

    QVBoxLayout* m_mainLayout;  ///<главный лейаут(внтури расположены прогресс бары)
    QVBoxLayout* m_stateLayout; ///<лейаут сосояния памяти
    QVBoxLayout* m_variableLayout;  ///<лейаут поиска переменной

    QProgressBar* m_progressBar; ///<образец progressBar
    MemoryParser* m_parser; ///<поле с парсером, где хранятся все структуры которые нам нужны

signals:
};

#endif // MEMORYINFO_H
