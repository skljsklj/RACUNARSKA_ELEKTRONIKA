#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	int i=0; int taster_pritisnut1=0; int taster_pritisnut2=0;
	int r_value1, r_value2;	
	if (wiringPiSetup() == -1)
	exit(1);
	pinMode(21, INPUT); //key0
	pinMode(22, INPUT); //key1
	if (softPwmCreate(28, 0, 100) != 0)
		exit (2);
	i = 0;
	taster_pritisnut1 = 0;
	taster_pritisnut2 = 0;
	while (1) {
	r_value1 = digitalRead(21); // procitaj KEY0
	r_value2 = digitalRead(22); // procitaj KEY1
	//cekamo na pritisak tastera
	if (!r_value1 && !taster_pritisnut1) {

		taster_pritisnut1 = 1;
		i += 20;
		if (i > 100) i = 0;
		printf("i = %d\n", i);
		fflush(stdout);
		softPwmWrite(28, i);
		delay(500);
		}
		// cekamo da se taster1 otpusti
		if (r_value1) taster_pritisnut1 = 0;
			
	if (!r_value2 && !taster_pritisnut2) {
		
		taster_pritisnut2 = 1;
		i -= 20;
		if (i < 0) i = 100;
		printf("i = %d\n", i);
		fflush(stdout);
		softPwmWrite(28, i);		
		delay(500);	
		}

		// cekamo da se taster2 otpusti
		if (r_value2) taster_pritisnut2 = 0;

	}
	
	return 0;
}