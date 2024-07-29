#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    IpAddress.setAddress("192.168.1.65");

    updHandler = new UdpHandler(this);
    updHandler->bindSocket(UDP_FIRMWARE_PORT);
    connect(updHandler,&UdpHandler::datagramReceived, this, &MainWindow::readUdpMK);

    connect(ui->addr_flash_lineEdit, SIGNAL(textChanged(QString)),this,SLOT(slot_check_addr_flash(QString)));

    ui->addr_flash_lineEdit->setToolTip ("Введите 8 символов в формате hex. Последние 2 символа должны быть нулями (кратность странице флеш-памяти).");

    /// - таймер для таймаутов обмена командными сообщениями ПК-МК;
    TimerPrototipe commandTimer(1000);
    connect(&commandTimer, &TimerPrototipe::timeout, this, &MainWindow::commandTimeout);

    /// - таймер для оценки времени записи файла;
    TimerPrototipe TimerWriteToFlash(1);
    connect(&TimerWriteToFlash, &TimerPrototipe::timeout, this, &MainWindow::updateTime);

    /// - таймер, по которому выводится время записи;
    TimerPrototipe TimerViewTime(500);
    connect(&TimerViewTime, &TimerPrototipe::timeout, this, &MainWindow::updateTimeView);

    connect(this, SIGNAL(signal_tx_pack_done()), SLOT(slot_write_to_flash())); /// - при принятии от МК сообщения, что пакет успешно записан испускается сигнал, который вызывает выполнение слота, который отправляет следующий пакет;
    connect(this, SIGNAL(signal_ask_finish_addr()), SLOT(slot_ask_finish_addr())); /// - как только размер который осталось отправить становится нулевым (он обнуляется с отправкой последнего пакета) и приходит сообщение что последний пакет записан испускается сигнал о запросе адреса, который вызывает выполнение соответствующего слота;

    ui->flash_process_progressBar->setRange(0, 100);
}

/// - слот который вызывается по таймауту таймера TimerViewTime;
/// - выводит текущее время записи в флеш;
void MainWindow::updateTimeView()
{
    ui->timer_write_flash_label->setText(QString::number(time_write_1ms/1000));
    ui->flash_process_progressBar->setValue(round(((double(count_successful_program_pack))/(double(save_file_size)))*100));
}

/// - слот который вызывается по таймауту таймера TimerWriteToFlash;
/// - считает милисекунды;
void MainWindow::updateTime()
{
    time_write_1ms++;
}

/// - функция-обработчик сообщений, пришедших от МК;
void MainWindow::readUdpMK()
{

    while (updHandler->hasPendingDatagrams())
    {
        QByteArray datagram;
        QHostAddress sender;
        quint16 senderPort;
        QString str;
        datagram.resize(updHandler->pendingDatagramSize());
        updHandler->readDatagram(datagram.data(), datagram.size(), sender, senderPort);

        str = formatDatagram(datagram);

        commandTimer->stop();
        handleDatagram(datagram);
    }
}


void MainWindow::handleDatagram(const QByteArray& datagram){
    /// - в зависимости от того, что записано нулевым байтом в сообщении выполняем действия:
    switch (datagram.at(0))
    {
        /*----------------------------COMMAND------------------------------------------------*/
        /// - ответ на запрос от ПК адреса, на котором остановилась запись файла;
    case COMMAND_ASK_ADDR:
    {
        handleCommandAskAddr(datagram);
    } break;

    case COMMAND_FINISH_FPGA:
    {
        handleCommandFinishFPGA();
    } break;

    case TIME_LOAD_MCU:
    {
        handleTimeLoadMCU(datagram);
    } break;
        /*----------------------------SUCCESSFUL------------------------------------------------*/
    case SUCCESSFUL_COMAND_ERASE:
    {
        handleSuccessfulErase();
    } break;

        /// - пришел ответ от МК, что пакет (5 страниц по 256 байт) записан успешно;
    case SUCCESSFUL_PROGRAM_PACK:
    {
        handleSuccessfulProgramPack();
    } break;

    case SUCCESSFUL_SET_ADDR:
    {
        handleSuccessfulSetAddr();
    } break;

    case SET_1_NUMBER_FIRMWARE:
    {
        handleSetNumberFirmware(1);
    } break;

    case SET_2_NUMBER_FIRMWARE:
    {
        handleSetNumberFirmware(2);
    } break;
        /*----------------------------ERROR------------------------------------------------*/
        /// - ошибка входа в режим QPI в микросхеме памяти;
    case ERROR_ENTRY_QPI_MODE:
    {
        handleErrorEntryQPI();
    } break;
    /// - ошибка установки дефолтных dummy циклов при старте контроллера;
    case ERROR_SET_DEF_DUMMYCYCLES_QPI:
    {
        handleErrorSetDummyCycles();
    } break;
    /// - ошибка может возникнуть во время передачи страницы в память или во время autopolling;
    case ERROR_SEND_DATA_TO_FLASH:
    {
        handleErrorSendData();
    } break;

    /// - ошибка воникающая в результате autopolling флеш-памяти;
    case ERROR_MEM_READY:
    {
        handleErrorMemReady();
    } break;

    case ERROR_COMAND_ERASE:
    {
        handleErrorErase();
    } break;

    case ERROR_SET_NUMBER_FIRMWARE:
    {
        handleErrorSetNumberFirmware();
    } break;

    case ERROR_RESET_FPGA:
    {
        handleErrorResetFPGA();
    } break;

    case ERROR_SEND_FIRMWARE_FPGA:
    {
        handleErrorSendFirmware();
    } break;
    }

}

void MainWindow::handleCommandAskAddr(const QByteArray& datagram){
     /// - запись пришедшего адреса в массив, хранящий адрес и установка этого значения в поле ввода адреса;
    val_addr_flash.clear();
    for (int i = 1; i <= 4; ++i)
        val_addr_flash.append(datagram[i]);

    ui->addr_flash_lineEdit->setText(val_addr_flash.toHex());
    /// - перевод стартового адреса и конечного из массива в переменные uint32_t для вычисления финишного (-1) и вывода в журнал;
    uint32_t local_val_addr_flash_start = ((summ_val_addr_flash[0])<<24)  |
                                          ((summ_val_addr_flash[1])<<16)  |
                                          ((summ_val_addr_flash[2])<<8)   |
                                          (summ_val_addr_flash[3]);

    uint32_t local_val_addr_flash_finish = ((val_addr_flash[0]&0xFF)<<24)  |
                                           ((val_addr_flash[1]&0xFF)<<16)  |
                                           ((val_addr_flash[2]&0xFF)<<8)   |
                                           (val_addr_flash[3]&0xFF);
    local_val_addr_flash_finish = local_val_addr_flash_finish - 0x01;

    AddJournalInfo(QString("Файл записан в флеш-память по адресу: 0x%1 - 0x%2").arg(local_val_addr_flash_start,8,16, QLatin1Char('0')).arg(local_val_addr_flash_finish,8,16, QLatin1Char('0')));
}


void MainWindow::handleCommandFinishFPGA(){
    AddJournalInfo("Время прошивки ПЛИС: " +QString::number(Elaps_timer_writeFPGA.elapsed())+ " мс");
}

void MainWindow::handleTimeLoadMCU(const QByteArray& datagram){
    QByteArray val_time_ms;
    for(int i = 1; i <= 4; ++i)
        val_time_ms.append(datagram[i]);

    QString str = val_time_ms.toHex();
    bool ok;
    uint appId = str.toUInt(&ok,16);
    //quint32 value = qFromBigEndian<quint32>(val_time_ms);
    AddJournalInfo("Время старта МК: " +QString::number(appId)+ " мс");
    qDebug() << val_time_ms.toUInt();
    qDebug() << val_time_ms.toHex();
}

void MainWindow::handleSuccessfulErase(){
    flag_set_addr = 0;
    enableButtonForFlash();

    AddJournalInfo("Успешная очистка памяти. Время очистки: " +QString::number(double(Elaps_timer.elapsed())/1000.0)+ " с");
}


void MainWindow::handleSuccessfulProgramPack(){
    /// - инкремент количества успешно записанных в флеш пакетов и вывод этого количества в successful_program_pack_label;
    count_successful_program_pack++;
    ui->successful_program_pack_label->setText(QString::number(count_successful_program_pack));

    /// - проверка размера, который осталось передать. Размер обнуляется при передаче последнего фращмента;
    if (file_size != 0)
    {
        emit signal_tx_pack_done();
    }
    else
    {
        /// - извлекаем значение Elaps_timer - более точное время выполнения;
        time_write_1ms = Elaps_timer.elapsed();
        time_write_1ms = time_write_1ms/1000;
        ui->timer_write_flash_label->setText(QString::number(time_write_1ms));
        ///- остановка таймеров промежуточного подсчета времени записи;
        TimerWriteToFlash->stop();
        TimerViewTime->stop();

        flag_set_addr = 0;

        enableButtonForFlash();

        /// - показываем размер файла. Должен быть равен нулю, т.к. файл был записан;
        ui->file_size_label->setText(QString::number(file_size));
        summ_pack = 0;
        ui->summ_pack_label->setText(QString::number(summ_pack));

        emit signal_ask_finish_addr();
        AddJournalInfo("В микросхему флеш-памяти передано пакетов: " +QString::number(count_tx_pack)+ ".\rИз них записано успешно: " +QString::number(count_successful_program_pack)+ ".\rЗаписано с ошибкой: " +QString::number(count_err_tx_pack));
        ui->flash_process_progressBar->setValue(round(((double(count_successful_program_pack))/(double(save_file_size)))*100));
    }
}

void MainWindow::handleSuccessfulSetAddr(){
    flag_set_addr = 1;
    enableButtonForFlash();

    AddJournalInfo("Адрес начала записи успешно установлен.");
}

void MainWindow::handleSetNumberFirmware(int firmwareSlot){
    AddJournalInfo(QString("Выбран слот прошивки №%1.").arg(firmwareSlot));
}

void MainWindow::handleErrorEntryQPI(){
    AddJournalInfo("Ошибка входа в режиме QPI микросхемой памяти.");
}

void MainWindow::handleErrorSetDummyCycles(){
    AddJournalInfo("Ошибка установки dummy циклов.");
}

void MainWindow::handleErrorSendData(){
    AddJournalInfo("Ошибка передачи страницы в микросхему флеш-памяти. Запись прервана.");
    count_err_tx_pack++;
    ui->err_tx_pack_label->setText(QString::number(count_err_tx_pack));
}

void MainWindow::handleErrorMemReady(){
    AddJournalInfo("Ошибка готовности памяти.");
    enableButtonForFlash();
    ui->err_tx_pack_label->setText(QString::number(count_err_tx_pack));
}

void MainWindow::handleErrorErase(){
    AddJournalInfo("Ошибка отправки команды очистки памяти.");
}

void MainWindow::handleErrorSetNumberFirmware(){
    AddJournalInfo("Ошибка установки слота прошивки.");
}

void MainWindow::handleErrorResetFPGA(){
    AddJournalInfo("Ошибка сброса ПЛИС.");
}

void MainWindow::handleErrorSendFirmware(){
    AddJournalInfo("Ошибка отправки прошивки в ПЛИС.");
}


QString MainWindow::formatDatagram(const QByteArray& datagram)
{
    QString str = datagram.toHex();
    for (int i = 2; i < str.size(); i += 3)
        str.insert(i, ' ');
    //qDebug()<<"Принято "<<datagram.size()<<" байт: "<<str;
    return str;
}

MainWindow::~MainWindow()
{
    delete ui;
}

/// - обработчик кнопки открытия файла;
void MainWindow::on_open_file_button_clicked()
{
    data.clear();
    save_file_size = 0;

    x_pos = 0; /// - обнуление положения пакета в массиве data;
    count_successful_program_pack = 0; /// - обнуляем счетчик успешно записанных пакетов;
    count_err_tx_pack = 0; /// - обнуляем счетчик пакетов, переданных с ошибкой;
    count_tx_pack = 0; /// - обнулениче счетчика переданных пакетов;
    /// - обнуление счетчиков пакетов;
    ui->count_tx_pack_label->setText(QString::number(count_tx_pack));
    ui->successful_program_pack_label->setText(QString::number(count_successful_program_pack));
    ui->err_tx_pack_label->setText(QString::number(count_err_tx_pack));
    ui->flash_process_progressBar->setValue(0);
    /// - обнуление счетчика времени записи;
    time_write_1ms = 0;
    ui->timer_write_flash_label->setText(QString::number(time_write_1ms));

    QString str = QFileDialog::getOpenFileName(this,
                                               "Открыть...",
                                               "D:\\QT_proj\\Proj_file_to_flash"
                                               );

    QFile file(str);

    if (!file.open(QIODevice::ReadOnly)) /// - проверяем, возможно ли открыть наш файл для чтения;
    {
        qDebug() << "Error read";
        return; /// - если это сделать невозможно, то завершаем функцию;
    }

    data = file.readAll(); //считываем все данные с файла в массив data, очистка массива после его отправки;

    /// - определение размера файла в байтах;
    file_size = data.size();
    ui->file_size_label->setText(QString::number(file_size));

    /// - определение количества пакетов по 1280 байт в файле;
    summ_pack = double(file_size/1280.0);
    summ_pack = ceil(summ_pack);
    save_file_size = summ_pack;
    ui->summ_pack_label->setText(QString::number(summ_pack));

    /// - расчет размера последнего пакета;
    size_last_pack = trunc((double(file_size))/256.0);
    size_last_pack = file_size - (size_last_pack * 256);
    AddJournalInfo("Размер последнего пакета: " +QString::number(size_last_pack));


    // if (flag_set_addr == 1)
    // {
    //   ui->write_to_flash_button->setEnabled(true);
    // }
}

/// - слот проверки введенного адреса, вызывается при любом изменении в addr_flash_lineEdit;
void MainWindow::slot_check_addr_flash(QString flash_addr)
{
    val_addr_flash.clear(); /// - очищаем значение адреса, потому что по результатам выполнения этого слота в массив val_addr_flash будет внесено содержимое addr_flash_lineEdit;

    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());

    //int count;
    //count = lineEdit->text().length();

    /// - если адрес не пустой и есть отправитель;
    if (lineEdit != nullptr && !flash_addr.isEmpty())
    {
        lineEdit->setStyleSheet("color:red");
        QRegExp reg_exp("[0-9a-fA-F]{8}$");

        /// - если ключ совпал с регулярным выражением с 0й позиции;
        if (!reg_exp.indexIn(flash_addr))
        {
            QStringList strList;
            QString key2;

            for (int i = 0; i < flash_addr.size(); i+=2)
            {
                key2 = flash_addr.mid(i,2);
                strList.append(key2);
            }

            /// - запись содержимого lineEdit в массив;
            bool is_ok = true;
            for (int i = 0; i < strList.size(); i++)
            {
                val_addr_flash.push_back(strList[i].toUInt(&is_ok, 16));
            }

            /// - проверка, чтобы в последних 2х символах были нули, т.е. кратность адреса флеш 256;
            /// - и старший байт не больше 1, то есть адрес не больше максималньо возможного;
            if ((val_addr_flash.at(val_addr_flash.size()-1) != 0) || (val_addr_flash.at(val_addr_flash.size()-0) != 0) || (val_addr_flash.at(0) > 0x01))
            {
                lineEdit->setStyleSheet("color:red");
                ui->set_addr_button->setEnabled(false);
            }
            /// - если последние 2 символа нули и адрес не больше максимального;
            else
            {
                lineEdit->setStyleSheet("color:green");
                ui->set_addr_button->setEnabled(true);
            }
        }
        /// - если не совпал с регулярным выражением;
        else
        {
            lineEdit->setStyleSheet("color:red");
            ui->set_addr_button->setEnabled(false);
        }
    }
    /// - если адрес пустой и нет отправителя;
    else
    {
        lineEdit->setStyleSheet("color:red");
        ui->set_addr_button->setEnabled(false);
    }
}

/// - обработчик нажатия на кнопку записи данных. Отправляет первый пакет, чтобы получить от МК ответ и запуститть процедуру дальнейшей записи: прием ответа от МК что пакет записан - испускание сигнала - вызов слота- ожидание ответа и по новой;
void MainWindow::on_write_to_flash_button_clicked()
{
    if (!data.isEmpty())
    {
        if (flag_set_addr == 1)
        {
            commandTimer->start(1000);
            disableButtonForFlash();

            /// - обнуление счетчика времени записи;
            time_write_1ms = 0;
            ui->timer_write_flash_label->setText(QString::number(time_write_1ms));
            /// - запуск таймеров;
            TimerWriteToFlash->start(); /// - промежуточный подсчет 1 мс;
            TimerViewTime->start(); /// - таймер отображения времени;
            Elaps_timer.start(); /// - таймер времени точного выполения;

            x_pos = 0; /// - обнуление положения пакета в массиве data;
            count_successful_program_pack = 0; /// - обнуляем счетчик успешно записанных пакетов;
            count_err_tx_pack = 0; /// - обнуляем счетчик пакетов, переданных с ошибкой;
            count_tx_pack = 0; /// - обнулениче счетчика переданных пакетов;

            /// - массив для хранения размера передаваемого пакета. Может быть не постоянным из-за последнего фрагмента;
            uint8_t sizeOFpack[2];

            sizeOFpack[0] = SIZE_DEF_PACK >> 8;
            sizeOFpack[1] = SIZE_DEF_PACK;

            QByteArray sendPACK2;
            sendPACK2.resize(SIZE_DEF_PACK);

            /// - инкремент переданных в МК пакетов и их отображение, потому что каждый раз, когда мы заходим в этот обработчик мы отправляем пакет;
            count_tx_pack++;
            ui->count_tx_pack_label->setText(QString::number(count_tx_pack));

            if (file_size >= SIZE_DEF_PACK)
            {
                /// - извлечение из массива с данными для отправки фрагмента в локальный массив;
                sendPACK2 = data.mid(x_pos, SIZE_DEF_PACK);
                /// - нулевым байтом будем идентификатор пакета, а 1 и 2 размер пакета;
                sendPACK2.prepend(sizeOFpack[1]);
                sendPACK2.prepend(sizeOFpack[0]);
                sendPACK2.prepend(IDENTIFICATOR_DATA);

                updHandler->writeDatagram(sendPACK2, IpAddress, UDP_FIRMWARE_PORT);

                file_size = file_size - SIZE_DEF_PACK;
                x_pos = x_pos + SIZE_DEF_PACK;
            }
            /// - если размер файла изначально был меньше пакета 1280 байт, то указываем ПО и МК что это первый и ПОСЛЕДНИЙ пакет;
            else
            {
                /// - изменение размера локального массива для отправки под размер оставшегося файла;
                sendPACK2.resize(file_size);
                sizeOFpack[0] = file_size >> 8;
                sizeOFpack[1] = file_size;
                /// - извлечение из массива с данными для отправки фрагмента в локальный массив;
                sendPACK2 = data.mid(x_pos, file_size);
                /// - нулевым байтом будем идентификатор пакета, а 1 и 2 размер пакета;
                sendPACK2.prepend(sizeOFpack[1]);
                sendPACK2.prepend(sizeOFpack[0]);
                sendPACK2.prepend(IDENTIFICATOR_DATA);

                updHandler->writeDatagram(sendPACK2, IpAddress, UDP_FIRMWARE_PORT);

                file_size = 0; /// - обнуление размера данных, чтобы обработчик ответа от МК понимал, что к нему пришел ответ на отправку последнего фрагмента;
                data.clear();

                /// - отправка размера последнего пакета;
                QByteArray sendPACK3;
                sendPACK3.prepend(size_last_pack);
                sendPACK3.prepend(SIZE_LAST_PACKET);
                updHandler->writeDatagram(sendPACK3, IpAddress, UDP_FIRMWARE_PORT);
                qDebug() << sendPACK3.toHex();
            }
        }
        else
        {
            AddJournalInfo("Адрес не установлен.");
        }
    }
    else
    {
        AddJournalInfo("Нет данных для записи.");
    }
}

/// - слот отправки данных, вызывается после первой отправки сообщения из-за испускаемого сигнала, который испрускается в ответ на сообщение от МК, что пакет принят и записан;
void MainWindow::slot_write_to_flash()
{
    commandTimer->start(1000);

    uint8_t sizeOFpack[2];

    sizeOFpack[0] = SIZE_DEF_PACK >> 8;
    sizeOFpack[1] = SIZE_DEF_PACK;

    QByteArray sendPACK2;
    sendPACK2.resize(SIZE_DEF_PACK);

    count_tx_pack++;
    ui->count_tx_pack_label->setText(QString::number(count_tx_pack));

    if (file_size >= SIZE_DEF_PACK)
    {
        /// - извлечение из массива с данными для отправки фрагмента в локальный массив;
        sendPACK2 = data.mid(x_pos, SIZE_DEF_PACK);
        /// - нулевым байтом будем идентификатор пакета, а 1 и 2 размер пакета;
        sendPACK2.prepend(sizeOFpack[1]);
        sendPACK2.prepend(sizeOFpack[0]);
        sendPACK2.prepend(IDENTIFICATOR_DATA);

        updHandler->writeDatagram(sendPACK2, IpAddress, UDP_FIRMWARE_PORT);

        file_size = file_size - SIZE_DEF_PACK;
        x_pos = x_pos + SIZE_DEF_PACK;
    }
    else
    {
        /// - изменение размера локального массива для отправки под размер оставшегося файла;
        sendPACK2.resize(file_size);
        sizeOFpack[0] = file_size >> 8;
        sizeOFpack[1] = file_size;
        /// - извлечение из массива с данными для отправки фрагмента в локальный массив;
        sendPACK2 = data.mid(x_pos, file_size);
        /// - нулевым байтом будем идентификатор пакета, а 1 и 2 размер пакета;
        sendPACK2.prepend(sizeOFpack[1]);
        sendPACK2.prepend(sizeOFpack[0]);
        sendPACK2.prepend(IDENTIFICATOR_DATA);

        updHandler->writeDatagram(sendPACK2, IpAddress, UDP_FIRMWARE_PORT);

        file_size = 0; /// - обнуление размера данных, чтобы обработчик ответа от МК понимал, что к нему пришел ответ на отправку последнего фрагмента;
        data.clear();

        /// - отправка размера последнего пакета;
        QByteArray sendPACK3;
        sendPACK3.prepend(size_last_pack);
        sendPACK3.prepend(SIZE_LAST_PACKET);
        updHandler->writeDatagram(sendPACK3, IpAddress, UDP_FIRMWARE_PORT);
        qDebug() << sendPACK3.toHex();
    }
}

/// - слот запроса адреса, на котором закончилась запись;
void MainWindow::slot_ask_finish_addr()
{
    QByteArray sendPACK;

    sendPACK[0] = COMMAND_ASK_ADDR;
    sendPACK.append(val_addr_flash);

    updHandler->writeDatagram(sendPACK, IpAddress, UDP_FIRMWARE_PORT);
    commandTimer->start(1000);
}

void MainWindow::on_erase_flash_button_clicked()
{
    AddJournalInfo("Запущена очистка памяти. Пожалуйста, подождите. Максимум 45 секунд.");
    disableButtonForFlash();

    Elaps_timer.start(); /// - таймер времени точного выполения;

    QByteArray sendPACK;

    sendPACK[0] = COMMAND_ERASE_FLASH;
    sendPACK.append(val_addr_flash);

    updHandler->writeDatagram(sendPACK, IpAddress, UDP_FIRMWARE_PORT);
    commandTimer->start(45000);
}

void MainWindow::on_set_addr_button_clicked()
{
    disableButtonForFlash();

    uint32_t local_val_addr_flash = ((val_addr_flash[0]&0xFF)<<24)  |
                                    ((val_addr_flash[1]&0xFF)<<16)  |
                                    ((val_addr_flash[2]&0xFF)<<8)   |
                                    (val_addr_flash[3]&0xFF);

    uint32_t local_finish_addr_flash = local_val_addr_flash + (ceil((double)(file_size)/256.0))*256;

    /// - переворачиваем порядок байт в переменной uint32_t, нужно для последующей записи uint32_t в QByteArray;
    local_finish_addr_flash = (local_finish_addr_flash & 0x00FF00FF) <<  8 | (local_finish_addr_flash & 0xFF00FF00) >>  8;
    local_finish_addr_flash = (local_finish_addr_flash & 0x0000FFFF) << 16 | (local_finish_addr_flash & 0xFFFF0000) >> 16;

    val_addr_flash_finish = QByteArray::fromRawData(reinterpret_cast<const char *>(&local_finish_addr_flash), sizeof(local_finish_addr_flash));
    //qDebug() << val_addr_flash_finish;

    if ((local_val_addr_flash + file_size) > MAX_ADDR_FLASH)
    {
        ui->set_addr_button->setEnabled(true);
        AddJournalInfo("Оставшейся памяти с учетом указанного адреса не хватит чтобы записать файл. Адрес не установлен!");
    }
    else
    {
        if (file_size == 0)
        {
            AddJournalInfo("Не был открыт файл для записи. Невозможно установить адрес окончания записи.");
            return;
        }

        summ_val_addr_flash.clear();
        summ_val_addr_flash.append(val_addr_flash);
        summ_val_addr_flash.append(val_addr_flash_finish);

        QByteArray sendPACK;

        sendPACK[0] = COMMAND_SET_ADDR;
        sendPACK.append(summ_val_addr_flash);

        //qDebug() << summ_val_addr_flash.toHex();

        updHandler->writeDatagram(sendPACK, IpAddress, UDP_FIRMWARE_PORT);
        qDebug() << sendPACK.toHex();

        commandTimer->start(1000);
    }
}

void MainWindow::commandTimeout()
{
    AddJournalInfo("Нет связи с устройством.");
    commandTimer->stop();
    TimerWriteToFlash->stop(); /// - промежуточный подсчет 1 мс;
    TimerViewTime->stop(); /// - таймер отображения времени;
    Elaps_timer.elapsed(); /// - таймер времени точного выполения;

    /// - если вышло время, активируем все кнопки;
    enableButtonForFlash();

    /// - удаление записываемого файла из память и обнуление адреса;
    data.clear();
    flag_set_addr = 0;
    file_size = 0;
    size_last_pack = 0;
    summ_pack = 0;
    ui->file_size_label->setText(QString::number(file_size));
    ui->summ_pack_label->setText(QString::number(summ_pack));
}

void MainWindow::AddJournalInfo(QString message)
{
    ui->JournalInfo->append(QTime::currentTime().toString());
    ui->JournalInfo->append(message);
    ui->JournalInfo->append("");
}

void MainWindow::on_JournalInfo_erase_Button_clicked()
{
    ui->JournalInfo->clear();
}

/// - отключение кнопок, связанных с работой флеш памяти;
void MainWindow::disableButtonForFlash()
{
    ui->erase_flash_button->setEnabled(false);
    //ui->set_addr_button->setEnabled(false);
    ui->write_to_flash_button->setEnabled(false);
    //ui->open_file_button->setEnabled(false);
}

/// - включение кнопок, связанных с работой флеш памяти;
void MainWindow::enableButtonForFlash()
{
    ui->erase_flash_button->setEnabled(true);
    ui->set_addr_button->setEnabled(true);
    ui->write_to_flash_button->setEnabled(true);
    ui->open_file_button->setEnabled(true);
}



void MainWindow::on_write_FPGA_button_clicked()
{
    QByteArray sendPACK;
    sendPACK[0] = COMMAND_WRITE_FPGA ;

    updHandler->writeDatagram(sendPACK, IpAddress, UDP_FIRMWARE_PORT);
    Elaps_timer_writeFPGA.start();
}

void MainWindow::on_firmware_1_button_clicked()
{
    QByteArray sendPACK;

    sendPACK[0] = COMMAND_SET_NUMBER_FIRMWARE;
    sendPACK.append(0x01);

    updHandler->writeDatagram(sendPACK, IpAddress, UDP_FIRMWARE_PORT);
    commandTimer->start(1000);
}

void MainWindow::on_firmware_2_button_clicked()
{
    QByteArray sendPACK;

    sendPACK[0] = COMMAND_SET_NUMBER_FIRMWARE;
    sendPACK.append(0x02);

    updHandler->writeDatagram(sendPACK, IpAddress, UDP_FIRMWARE_PORT);
    commandTimer->start(1000);
}
