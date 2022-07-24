#include <18F4550.h>
#DEVICE PASS_STRINGS=IN_RAM
#device ADC=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)  //#use delay(clock=20000000)
#include <usb/usb_bootloader.h> //Comenta esta línea si no usas Bootloader
#include <JACSS_CDC.c>  //Libreria que genera el puerto COM virtual para comunicacion.
#use rs232(baud=115200, BITS=8, PARITY=N, xmit=PIN_C6,rcv=PIN_C7,STREAM=pucca, ERRORS)
//////////////////////////////////////////
//////////////////////////////////////////
#include <string.h>
#include <stdio.h>

void probe(){
   float probe=77.7;
   float probe2=66.6;
   fprintf(pucca,"AT\r\n");
   delay_ms(1000);
   fprintf(pucca,"AT+CIPMUX=1\r\n");
   delay_ms(1000);
   fprintf(pucca,"AT+CIPSTART=0,\"TCP\",\"184.106.153.149\",80\r\n");
   delay_ms(1000);
   fprintf(pucca,"AT+CIPSEND=0,100\r\n");
   delay_ms(1000);
   fprintf(pucca,"GET /update?api_key=4NZWPSSD36STQHW2&field1=%.1f&field2=%.1f\n",probe,probe2);
   delay_ms(1000);
}

void main(){
   usbInit();
   delay_ms(200);
   
   /*fprintf(pucca,"AT+CWMODE=1\r\n");
   delay_ms(1000);
   fprintf(pucca,"AT+CWJAP=\"AdrianStella\",\"12345678\"\r\n");
   delay_ms(1000);*/
   
   while(true)
   {
      delay_ms(5000);
      probe();
   }
}
