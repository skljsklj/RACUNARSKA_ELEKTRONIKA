// primer rada sa PCF8563 koji ispisuje tekuce vreme
// u terminalu svakih 5 sekundi
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>
#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16) )

//adrese registara
#define SEK 0x02
#define MINS 0x03
#define SAT 0x04
#define DAN 0x05
#define MES 0x07
#define GOD 0x08
unsigned char WriteBuf[2];
unsigned char ReadBuf;
unsigned char g8563_Store[6];
// sec,min,sat
unsigned char init8563_Store[6]={0x00,0x59,0x08,0x03,0x30,0x60};

void P8563_settime(int fd)
{
	wiringPiI2CWriteReg8(fd,SEK,g8563_Store[0]); 
	wiringPiI2CWriteReg8(fd,MINS,g8563_Store[1]); 
	wiringPiI2CWriteReg8(fd,SAT,g8563_Store[2]); 
	wiringPiI2CWriteReg8(fd,DAN,g8563_Store[3]); 
	wiringPiI2CWriteReg8(fd,MES,g8563_Store[4]); 
	wiringPiI2CWriteReg8(fd,GOD,g8563_Store[5]); 
}
void P8563_init(int fd)
{
	unsigned char i;
	for(i=0;i<=5;i++)
	g8563_Store[i]=init8563_Store[i];
	P8563_settime(fd);
	printf("Postavi početno tekuće vreme\n");
	//inicijalizacija RTC-a
	wiringPiI2CWriteReg8(fd,0x0,0x00); 
}
void P8563_Readtime(int fd)
{
	unsigned char time[6];
	time[0] = wiringPiI2CReadReg8(fd,SEK);
	time[1] = wiringPiI2CReadReg8(fd,MINS);
	time[2] = wiringPiI2CReadReg8(fd,SAT);
	time[3] = wiringPiI2CReadReg8(fd,DAN);
	time[4] = wiringPiI2CReadReg8(fd,MES);
	time[5] = wiringPiI2CReadReg8(fd,GOD);
	g8563_Store[0] = time[0] & 0x7f; //sek
	g8563_Store[1] = time[1] & 0x7f; //min
	g8563_Store[2] = time[2] & 0x3f; //sat
	g8563_Store[3] = time[3] & 0x3f; //dan
	g8563_Store[4] = time[4] & 0x1f; //mes
	g8563_Store[5] = time[5]; //god
	g8563_Store[0] = changeHexToInt(g8563_Store[0]);
	g8563_Store[1] = changeHexToInt(g8563_Store[1]);
	g8563_Store[2] = changeHexToInt(g8563_Store[2]);
	g8563_Store[3] = changeHexToInt(g8563_Store[3]);
	g8563_Store[4] = changeHexToInt(g8563_Store[4]);
	g8563_Store[5] = changeHexToInt(g8563_Store[5]);
}


int main(int argc, char **argv)
{
	int fd;
	if (!wiringPiSetup() == -1)
		printf("wiringPi neuspesan");
	//bcm2835_i2c_begin();
	// adresa PCF8563 na I2C magistrali
	fd = wiringPiI2CSetup(0x51);
	if(fd == -1)
	{
		printf("wiringPiI2C neuspesno");
	}
	//bcm2835_i2c_set_baudrate(10000); 
	printf("start..........\n");
	P8563_init(fd) ;
	while(1)
	{
		P8563_Readtime(fd);
		printf("Godine:%d Meseci:%d Dani:%d Sati:%d Minuti:%d Sekunde:%d\n",g8563_Store[5],g8563_Store[4],g8563_Store[3],g8563_Store[2], g8563_Store[1],
		g8563_Store[0]);
		delay(5000);
	}
	//bcm2835_i2c_end(); 
	//bcm2835_close(); 
	return 0;
}