#include "dialog.h"
#include "ui_dialog.h"
#include <QThread>
#include <QTime>
#include <QTimer>

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

void Dialog::on_pushButton_clicked()
{
    QTime vreme = ui->timeEdit->time();



    while (true) {
        vreme = vreme.addSecs(1);
        QString vreme_str = vreme.toString("hh:mm:ss");
        ui->label_3->setText(vreme_str);

        // Allow the UI to update
        QCoreApplication::processEvents();

        // Sleep for 1 second
        QThread::sleep(1);
    }
}

void Dialog::on_label_3_linkActivated(const QString &link)
{
    QTime vreme1 = QTime::fromString(link,"hh:mm:ss");
    vreme1 = vreme1.addSecs(1);
    QString vreme_str1 = vreme1.toString("hh:mm:ss");
    ui->label_3->setText(vreme_str1);
}
