#include <18F4550.h>
#device ADC=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)  //#use delay(clock=20000000)
#include <usb/usb_bootloader.h> //Comenta esta línea si no usas Bootloader
#include <JACSS_CDC.c>  //Libreria que genera el puerto COM virtual para comunicacion.

#define push1 PIN_A0
//#define push2 PIN_B1

int value = 0;
int counter = 0;

void readpin(){
   value = input(push1);
   delay_ms(500);
   if(value==1){
      counter=counter+1;
   }
   if(counter==5){
      counter=0;
   }
}

void offlights(){
   OUTPUT_B(0x00);
   delay_ms(2000);
}

void lefttoright(){
   OUTPUT_B(0x01);
   delay_ms(150);
   OUTPUT_B(0x02);
   delay_ms(150);
   OUTPUT_B(0x04);
   delay_ms(150);
   OUTPUT_B(0x08);
   delay_ms(150);
   OUTPUT_B(0x10);
   delay_ms(150);
   OUTPUT_B(0x20);
   delay_ms(150);
   OUTPUT_B(0x40);
   delay_ms(150);
   OUTPUT_B(0x80);
   delay_ms(150);
   readpin();
}

void righttoleft(){
   OUTPUT_B(0x80);
   delay_ms(150);
   OUTPUT_B(0x40);
   delay_ms(150);
   OUTPUT_B(0x20);
   delay_ms(150);
   OUTPUT_B(0x10);
   delay_ms(150);
   OUTPUT_B(0x08);
   delay_ms(150);
   OUTPUT_B(0x04);
   delay_ms(150);
   OUTPUT_B(0x02);
   delay_ms(150);
   OUTPUT_B(0x01);
   delay_ms(150);
   readpin();
}

void fromthecenter(){
   OUTPUT_B(0x18);
   delay_ms(150);
   OUTPUT_B(0x24);
   delay_ms(150);
   OUTPUT_B(0x42);
   delay_ms(150);
   OUTPUT_B(0x81);
   delay_ms(150);
   readpin();
}

void fromthecorner(){
   OUTPUT_B(0x81);
   delay_ms(150);
   OUTPUT_B(0x42);
   delay_ms(150);
   OUTPUT_B(0x24);
   delay_ms(150);
   OUTPUT_B(0x18);
   delay_ms(150);
   readpin();
}

void main()
{
   usbInit();
   delay_ms(200);
   
   while(true)
   {
      readpin();
      if(counter==0){
         offlights();
      }else{
      if(counter==1){
         lefttoright();
      }else{
      if(counter==2){
         righttoleft();
      }else{
      if(counter==3){
         fromthecenter();
      }else{
      if(counter==4){
         fromthecorner();
      }else{
      counter=0;
      }
      }
      }
      }
      }
      
   }

}
