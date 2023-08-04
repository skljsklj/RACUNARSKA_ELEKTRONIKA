#include "dialog.h"
#include "ui_dialog.h"


float napon=0;
float temp=0;
float svetlo=0;
int adc1=0;
int r6=0;
int integer, decimal;

long citaj_temp() {

    int fd = -1, ret;
    char *tmp1, tmp2[10], ch='t';
    char devname_head[50] = "/sys/devices/w1_bus_master1/28-00000a41dec3";  // =====>     DODAJ TU BROJ NA KRAJU !!!

    char devname_end[10] = "/w1_slave";
    char dev_name[100];
    long value;
    char buffer[100];


    strcpy(dev_name, devname_head);
    strcat(dev_name, devname_end);

    if ((fd = open(dev_name, O_RDONLY)) < 0)
        {
        perror("Greška pri otvaranju!");
        exit(1);
        }

        ret = read(fd, buffer, sizeof(buffer));

        if (ret < 0)
        {
        perror("Greška pri čitanju!");
        exit(1);
        }

        tmp1 = strchr(buffer, ch);
        sscanf(tmp1, "t=%s", tmp2);
        value = atoi(tmp2);

        close(fd);

return value;
}

void read_sensors(){
    const char PCF8591 = 0x48;
    int fd;

    if (wiringPiSetup () == -1) exit (1);
    fd = wiringPiI2CSetup(PCF8591);

    napon= wiringPiI2CReadReg8(fd, PCF8591 + 3);
    napon= wiringPiI2CReadReg8(fd, PCF8591 + 3);
    adc1= wiringPiI2CReadReg8(fd, PCF8591 + 1);
    adc1= wiringPiI2CReadReg8(fd, PCF8591 + 1);
    svetlo=wiringPiI2CReadReg8(fd, PCF8591 + 0);
    svetlo=wiringPiI2CReadReg8(fd, PCF8591 + 0);
}



Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->dial->setDisabled(true);
    ui->verticalSlider->setDisabled(true);

    timer=new QTimer(this);
    connect (timer, SIGNAL(timeout()), this,SLOT(update_parametara()));
    timer->setInterval(200);
    timer->start();
}


Dialog::~Dialog()
{
    delete ui;
}




void Dialog::update_parametara()
{
    read_sensors();
    ispis_broja();

    // pretvaranje napona u volte
    napon=(napon*3.3/255)*10;

    //pretvaranje adc1 u temp
    r6=(1000*adc1)/(256-adc1);
    //temp=(298.15*3950)/(3950 + log(r6/10000));
    //temp = temp - 273.15; // U celzijuse

    //pretvaranje svetlosti u procente
    svetlo=(svetlo/255)*100;

    //ispis na ekran
    ui->dial->setValue(napon);
    ui->verticalSlider->setValue(svetlo);
    ui->lcdNumber->display(broj.arg(integer).arg(decimal));
    //ui->lcdNumber->display(temp);
}

void Dialog::ispis_broja()
{
    integer = citaj_temp() / 1000;
    decimal = citaj_temp() % 1000;
    broj="%1.%2";
}

