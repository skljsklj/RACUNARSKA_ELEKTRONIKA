#include "dialog.h"
#include "ui_dialog.h"
#include <wiringPi.h>
#include <lcd.h>
#include <string.h>

std::string str1;
std::string str2;

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    int lcd;
    lcd = lcdInit(2,16,4,RS,EN,D0,D1,D2,D3,D0,D1,D2,D3);

    QString linija1 = ui->lineEdit->text();
    QString linija2 = ui->lineEdit_2->text(); // use lineEdit_2 for the second line

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();

    str1 = linija1.toStdString();
    str2 = linija2.toStdString();

    lcdClear(lcd);
    lcdPosition(lcd,0,0);
    lcdPrintf(lcd,"%s",str1.c_str());
    lcdPosition(lcd,0,1);
    lcdPrintf(lcd,"%s",str2.c_str());
}
