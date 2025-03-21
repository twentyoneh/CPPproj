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
    explicit MemoryInfo(MemoryParser parser,QWidget *parent = nullptr);
    void CreateMemoryStateInfo(MemoryParser parser);

private:
    QProgressBar *progressBar;

signals:
};

#endif // MEMORYINFO_H
