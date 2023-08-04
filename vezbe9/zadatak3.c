#include <bcm2835.h> 
#include <stdio.h>
#include <unistd.h>
unsigned char WriteBuf; 
unsigned char ReadBuf0,ReadBuf1,ReadBuf2,ReadBuf3; 
enum svetlost {SLABO, DNEVNO, NOCNO};


#define PIN1 12
#define PIN2 16
#define PIN3 20





int main(int argc, char **argv) 
{ 
	if (!bcm2835_init()) 
		return 1; 
	bcm2835_i2c_begin(); 
	bcm2835_i2c_setSlaveAddress(0x48); 
	bcm2835_i2c_set_baudrate(10000);
	bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP); 
	bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PIN3, BCM2835_GPIO_FSEL_OUTP);
	

	enum svetlost light;
	while(1) 
	{ 

		WriteBuf = 0x00; 
		bcm2835_i2c_write_read_rs(&WriteBuf, 1, &ReadBuf0, 1); 
		bcm2835_i2c_read(&ReadBuf0, 1); 
		
		if(ReadBuf0 < 50){
			light = SLABO;		
		}else if(ReadBuf0 >= 50 && ReadBuf0 < 186){
			light = DNEVNO;
		}else if(ReadBuf0 >= 186){
			light = NOCNO;
		}

		switch(light){

		case SLABO:
			printf("SLABO\n");
			bcm2835_gpio_write(PIN1, HIGH);
			bcm2835_delay(500);
			bcm2835_gpio_write(PIN1, LOW);

		break;
		case DNEVNO:
			printf("DNEVNO\n");
			bcm2835_gpio_write(PIN2, HIGH);
			bcm2835_delay(500);
			bcm2835_gpio_write(PIN2, LOW);
		break;
		case NOCNO:
			printf("NOCNO\n");
			bcm2835_gpio_write(PIN3, HIGH);
			bcm2835_delay(500);
			bcm2835_gpio_write(PIN3, LOW);
			
		break;



		}
		printf("adc0: %d\n",ReadBuf0);
		printf ("\r") ; fflush (stdout) ;
		bcm2835_delay(100); 
	} 
	
	bcm2835_i2c_end(); 
	bcm2835_close(); 
	return 0; 
 }
