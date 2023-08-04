#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <lcd.h>

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int main()
{
	if(wiringPiSetup() <0 )
	{
		fprintf(stderr,"Greska pri inicijalizacijij:%s\n", strerror(errno));
		return 1;
	}
	int x = 0;
	int y = 0;
	int lcd_h;
	int taster1 = 0;
	int taster2 = 0;
	int taster3 = 0;
	int taster4 = 0;
	int r_value1, r_value2, r_value3, r_value4;
	pinMode(21, INPUT); //key0
	pinMode(22, INPUT); //key1
	pinMode(23, INPUT); //key2
	pinMode(24, INPUT); //key3
	lcd_h = lcdInit(2,16,4,RS,EN,D0,D1,D2,D3,D0,D1,D2,D3);
	while(1)
	{
		r_value1 = digitalRead(21);
		r_value2 = digitalRead(22);
		r_value3 = digitalRead(23);
		r_value4 = digitalRead(24);
		lcdPosition(lcd_h,y,x);
		lcdCursor(lcd_h, 1);
		delay(200);

		if (!r_value1 && !taster1) {
		taster1 = 1;
		y++;
		if(y == 16) y = 0;
		}
		// cekamo da se taster1 otpusti
		if (r_value1) taster1 = 0;

		if (!r_value2 && !taster2) {
		taster2 = 1;
		x++;
		if(x == 2) x = 0;
		}
		// cekamo da se taster2 otpusti
		if (r_value2) taster2 = 0;
		
		/*if (!r_value3 && !taster3) {
		taster3 = 1;
		y++;
		if(y == 2) y = 0;
		}
		// cekamo da se taster3 otpusti
		if (r_value3) taster3 = 0;

		if (!r_value4 && !taster4) {
		taster4 = 1;
		y--;
		if(y == -1) y = 1;
		}
		// cekamo da se taster4 otpusti
		if (r_value4) taster4 = 0;*/
			
	}
	return 0;
}
