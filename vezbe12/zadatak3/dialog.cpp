#include "dialog.h"
#include "ui_dialog.h"
#include <QThread>
#include <QTime>
#include <QTimer>
#include <wiringPi.h>
#include <lcd.h>
#include <string.h>

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;
int temp = 0;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QTimer *mytimer = new QTimer(this);

    connect(mytimer, SIGNAL(timeout()),this, SLOT(label_3()));
    mytimer->start(1000);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_timeEdit_userTimeChanged(const QTime &time)
{

}

void Dialog::on_checkBox_stateChanged(int arg1)
{
    int lcd;
    lcd = lcdInit(2,16,4,RS,EN,D0,D1,D2,D3,D0,D1,D2,D3);
    if (ui->checkBox->isChecked()) {
        // Set the cursor to the first column of the second row
        temp = 1;
    } else {
        // Set the cursor to the first column of the first row
        temp = 0;
    }
}

void Dialog::on_pushButton_clicked()
{
    QTime vreme = ui->timeEdit->time();
    int lcd;
    lcd = lcdInit(2,16,4,RS,EN,D0,D1,D2,D3,D0,D1,D2,D3);

    while (true) {
        vreme = vreme.addSecs(1);

        QString vreme_str;
        vreme_str = vreme.toString("HH:mm:ss");
        ui->label_3->setText(vreme_str);
        if(temp == 1)
        {
            lcdPosition(lcd,0,temp);
            lcdPuts(lcd, vreme_str.toLocal8Bit().constData());
        }

        if(temp == 0)
        {
            lcdPosition(lcd,0,temp);
            lcdPuts(lcd, vreme_str.toLocal8Bit().constData());
        }

        // Allow the UI to update
        QCoreApplication::processEvents();

        // Sleep for 1 second
        QThread::sleep(1);
        lcdClear(lcd);
        //delay(100);
    }
}


void Dialog::on_label_3_linkActivated(const QString &link)
{
    QTime vreme1 = QTime::fromString(link,"hh:mm:ss");
    vreme1 = vreme1.addSecs(1);
    QString vreme_str1 = vreme1.toString("hh:mm:ss");
    ui->label_3->setText(vreme_str1);
}



void Dialog::on_radioButton_clicked()
{
   //is24HourFormat = true;
    //is12HourFormat = false;
}

void Dialog::on_radioButton_2_clicked()
{
    //is24HourFormat = false;
    //is12HourFormat = true;
}


