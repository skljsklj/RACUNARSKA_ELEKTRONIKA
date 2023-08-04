#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <wiringPi.h>
#include <errno.h>
#include <lcd.h>
//d3d4ebb

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;


int main(int argc, char *argv[])
{
	if(wiringPiSetup() == -1)
		exit(1);
	pinMode (25, OUTPUT);
	int fd = -1, ret;
	char *tmp1, tmp2[10], ch='t';
	char devname_head[50] =
	"/sys/devices/w1_bus_master1/28-00000";
	char devname_end[10] = "/w1_slave";
	char dev_name[100];
	long value;
	int integer, decimal;
	char buffer[100];
	int i,j;
	int lcd_h;
	lcd_h = lcdInit(2,16,4,RS,EN,D0,D1,D2,D3,D0,D1,D2,D3);
	

	while(1)
	{
		strcpy(dev_name, devname_head);
		strcat(dev_name, argv[1]);
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
		integer = value / 1000;
		decimal = value % 1000;
		printf("Temperatura je %d.%d\n", integer,decimal);
		close(fd);
		
		lcdPosition(lcd_h, 0, 0);
		lcdPrintf(lcd_h,"%d.%d", integer, decimal);
		lcdPosition(lcd_h,0,1);
		delay(500);					
		lcdClear(lcd_h);
		
	}
	
	return 0;
}
