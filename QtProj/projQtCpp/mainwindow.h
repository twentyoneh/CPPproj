#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QUdpSocket>
#include <QElapsedTimer>
#include <QDialog>
#include <QObject>
#include <QQueue>
#include "QMessageBox"
#include "QHostAddress"
#include <QByteArray>
#include <QDebug>
#include <QMouseEvent>
#include <QtCore/QString>
#include <QHostInfo>
#include <QNetworkInterface>
#include "QThread"
#include <QFileDialog>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QRegExp>

#include"timerprototipe.h"
#include"udphandler.h"

#define SIZE_DEF_PACK   1280 /// - размер стандартного пакета (5 страниц по 256 байт);
#define MAX_ADDR_FLASH  0x01FFFFFF /// - размер стандартного пакета (5 страниц по 256 байт);

#define UDP_FIRMWARE_PORT              5764
#define	COMMAND_SET_ADDR               0x11    /// - команда установить адрес флеш-памяти;
#define ERROR_ENTRY_QPI_MODE           0x12    /// - ошибка входа в режим QPI;
#define SUCCESSFUL_SET_ADDR            0x13    /// - ответ от МК для ПК, что адрес был успешно установлен;
#define IDENTIFICATOR_DATA             0x14    /// - идентификатор, что отправляемые данные- данные открытого файла;
#define ERROR_SEND_DATA_TO_FLASH       0x15    /// - ошибка отправки данных в микросхему памяти;
#define ERROR_MEM_READY                0x16    /// - ошибка готовности памяти после записи в нее страницы;
#define COMMAND_ERASE_FLASH            0x17    /// - команда очистки флеш-памяти;
#define ERROR_COMAND_ERASE             0x18    /// - ошибка отправки команды очистки памяти;
#define SUCCESSFUL_COMAND_ERASE        0x19    /// - успешная очистка памяти;
#define SUCCESSFUL_PROGRAM_PACK        0x20    /// - успешно записан пакет даныых (5 страниц);
#define COMMAND_ASK_ADDR               0x21    /// - команда запроса адреса, на котором остановилась запись;
#define ERROR_SET_DEF_DUMMYCYCLES_QPI  0x22    /// - ошибка установки дефолтного значения пустых циклов;
#define SIZE_LAST_PACKET               0x23    /// - идентификатор, что пакет несет в себе информацию о размере последнего пакета;
#define COMMAND_WRITE_FPGA             0x24    /// - записать из флеш в ПЛИС;
#define COMMAND_FINISH_FPGA            0x25    /// - команда от МК что передача в ПЛИС окончена;
#define TIME_LOAD_MCU                  0x26    /// - идентификатор пакета с информацией о времени загрузки МК;
#define COMMAND_SET_NUMBER_FIRMWARE    0x27    /// - команда, указывающая номер прошивки. Всего прошивок в микросхеме флеш-памяти может быть две;
#define ERROR_SET_NUMBER_FIRMWARE      0x28    /// - ошибка установки номера прошивки ПЛИС;
#define SET_1_NUMBER_FIRMWARE          0x29    /// - установлен 1й номер прошивки;
#define SET_2_NUMBER_FIRMWARE          0x30    /// - установлен 2й номер прошивки;
#define ERROR_RESET_FPGA               0x31    /// - ошибка сброса ПЛИС;
#define ERROR_SEND_FIRMWARE_FPGA       0x32    /// - ошибка отправки прошивки в ПЛИС;
#define SUCCESSFUL_SEND_FIRMWARE_FPGA  0x33    /// - ПЛИС успешно прошита;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_open_file_button_clicked();
    void slot_check_addr_flash(QString);
    void on_write_to_flash_button_clicked();
    void commandTimeout();
    void AddJournalInfo(QString message);
    void readUdpMK();
    void slot_write_to_flash();
    void slot_ask_finish_addr();
    void updateTime();
    void updateTimeView();

    void disableButtonForFlash(); /// - отключение кнопок, связанных с работой флеш памяти;
    void enableButtonForFlash(); /// - включение кнопок, связанных с работой флеш памяти;

    void on_erase_flash_button_clicked();

    void on_set_addr_button_clicked();

    void on_JournalInfo_erase_Button_clicked();

    void on_write_FPGA_button_clicked();

    void on_firmware_1_button_clicked();

    void on_firmware_2_button_clicked();

private:
    Ui::MainWindow *ui;

    QString formatDatagram(const QByteArray& datagram);
    void handleDatagram(const QByteArray& datagram);

    void handleCommandAskAddr(const QByteArray& datagram);
    void handleCommandFinishFPGA();
    void handleTimeLoadMCU(const QByteArray& datagram);
    void handleSuccessfulErase();
    void handleSuccessfulProgramPack();
    void handleSuccessfulSetAddr();
    void handleSetNumberFirmware(int firmwareSlot);
    void handleErrorEntryQPI();
    void handleErrorSetDummyCycles();
    void handleErrorSendData();
    void handleErrorMemReady();
    void handleErrorErase();
    void handleErrorSetNumberFirmware();
    void handleErrorResetFPGA();
    void handleErrorSendFirmware();

    UdpHandler *updHandler; /// - порт, на который отправляем прочитанный файл;
    QHostAddress IpAddress; /// - адрес МК;
    uint64_t file_size = 0;
    uint64_t save_file_size;
    QByteArray data;              /// - создаем объект класса QByteArray, куда мы будем считывать данные из файла;
    QByteArray val_addr_flash;    /// - значение адреса, с которого начинаем запись в flash или на котором закончилась запись;
    QByteArray val_addr_flash_finish;
    QByteArray summ_val_addr_flash; /// - адрес начала и окончания прошивки;
    QTimer      *commandTimer  = nullptr; /// - таймер для таймаутов обмена ПК-МК;
    QTimer      *TimerWriteToFlash= nullptr; /// - промежуточный таймер для отсчета времени, потраченного на запись файла;
    QElapsedTimer Elaps_timer;
    QElapsedTimer Elaps_timer_writeFPGA;
    QTimer *TimerViewTime = nullptr;

    uint64_t count_err_tx_pack;   /// - счетчик ошибок отправки пакетов в флеш-память;
    uint64_t count_successful_program_pack; /// - счетчик успешно переданных пакетов;
    uint64_t count_tx_pack; /// - счетчик пакетов, которые были отправлены. Они могут быть отправлены успешно (записаны) и с ошибкой (ошибка во время записи);
    double summ_pack;
    uint64_t x_pos; /// - позиция в массиве QByteArray data, откуда будет отправляться очередной пакет;
    uint8_t flag_set_addr = 0; /// - флаг установки адреса, нужен для активации кнопки "записать во флеш";
    double time_write_1ms; /// - счетчик таймаутов по 1 мс;
    uint8_t size_last_pack = 0; /// - размер последнего пакета;

signals:
    void signal_tx_pack_done(); /// - сигнал, излучаемый при приеме от МК команды успешно записанных данных или с ошибкой;
    void signal_ask_finish_addr(); /// - сигнал запроса адреса, на котором остановилась запись предыдущего файла;
};

#endif // MAINWINDOW_H
