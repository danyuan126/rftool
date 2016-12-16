/*
 * main.c
 *
 *  Created on: 2016��11��15��
 *      Author: admin
 */


//#include <iostream>
#include "DRV_Radio.h"

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>

/*
This function registers a function to received interrupts on the specified pin. 
The edgeType parameter is either INT_EDGE_FALLING, INT_EDGE_RISING, INT_EDGE_BOTH or 
INT_EDGE_SETUP. If it is INT_EDGE_SETUP then no initialisation of the pin will happen 
šC it¡¯s assumed that you have already setup the pin elsewhere (e.g. with the gpio program), 
but if you specify one of the other types, then the pin will be exported and initialised 
as specified. This is accomplished via a suitable call to the gpio utility program, 
so it need to be available.
*/
unsigned char spiData[10]={0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A};
unsigned char spiData1[10]={0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A};
unsigned char spiData2[10]={0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A};

void isrMsg(void)
{
    printf("key is press down\n");
    //wiringPiSPIDataRW (0, spiData, 10) ;
    //SX1278_DIO0_IN();
    //radioHalDIO0ISR();
}


/*
This is the way to initialise a channel (The Pi has 2 channels; 0 and 1). The speed parameter is an integer in the range 500,000 through 32,000,000 and represents the SPI clock speed in Hz.
The returned value is the Linux file-descriptor for the device, or -1 on error. If an error has happened, you may use the standard errno global variable to see why.
int wiringPiSPISetup (int channel, int speed) ;
*/

/*
This performs a simultaneous write/read transaction over the selected SPI bus. Data that was in your buffer is overwritten by data returned from the SPI bus.
int wiringPiSPIDataRW (int channel, unsigned char *data, int len) ;
*/

int main (void)
{
  int spiRet;
  int i;

	printf("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	
  wiringPiSetup () ;

  //pinMode (0, OUTPUT) ;
  //digitalWrite (0,  LOW) ;
  //pinMode (21, OUTPUT) ;
  //digitalWrite (21,  HIGH) ;
  //delay (1) ;
  //digitalWrite (21,  LOW) ;
  SX1278_DIO0_IN();
  wiringPiISR (SX1278_DIO0_PIN, INT_EDGE_RISING,  isrMsg) ;

  //spiRet = wiringPiSPISetup (0, 500000) ;
  //if(spiRet == -1)
  //{
  //  printf("Starting SPI failed\n");
  //}
  //else
  //{
  //  printf("Starting SPI SUCCED\n");
  //}

   // spiRet = wiringPiSPIDataRW (0, spiData, 10) ;
//delay (500) ;
  //spiData[0] = 1;
  //  spiRet = wiringPiSPIDataRW (0, spiData1, 10) ;
  //  spiData[0] = 2;
//delay (500) ;
   // spiRet = wiringPiSPIDataRW (0, spiData2, 10) ;
//delay (500) ;

	radioHalInit();
	
    //spiRet = wiringPiSPIDataRW (0, spiData, 10) ;
  for (i=0; i<100; i++)
  {
  //  digitalWrite (0, HIGH) ;
  //  delay (500) ;
	  if(SX1278_DIO0_STATE()==1)
	  {
		  radioHalDIO0ISR();
		  radioHalChangeState(RADIO_STATE_RX);
	  }
   // digitalWrite (0,  LOW) ;
   delay (100) ;
	//radioHalLoadSendBuf(13, "hello world!");
	//radioHalLoadSendBuf(, "hello world!");
	//radioHalChangeState(RADIO_STATE_TX);
  }
	printf("!!!program end!"); /*  */
  return 0 ;
}



