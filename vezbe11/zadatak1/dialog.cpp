#include "dialog.h"
#include "ui_dialog.h"
#include <wiringPi.h>

void toggleLed(){
    static bool state = true;
    digitalWrite(25, state ? HIGH : LOW);
    state = !state;
}

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
    toggleLed();
}
