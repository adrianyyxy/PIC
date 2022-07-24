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

#define LED PIN_D0
//////////////////////////////////////////
//////////////////////////////////////////

void LED_probe(){
   output_high(LED);
   delay_ms(200);
   output_low(LED);
}

int1 timeout_error;

char timed_getc(){

   long timeout;

   timeout_error=FALSE;
   timeout=0;

   while(!kbhit()&&(++timeout<50000)) // 1/2
                                    // second
          delay_us(10);
   if(kbhit())
          return(getc(pucca));
   else {
          timeout_error=TRUE;
          return(0);
   }
}

//////////////////////////////////////////
//////////////////////////////////////////

void read_string(char* MyString, unsigned int max)
{
   unsigned int len;
   char c;
   --max;
   len=0;
   
   do {
     c = timed_getc();
     if(c==8) {
        if(len>0){
          len--;
        }
     }else if ((c>=' ')&&(c<='~'))
       if(len<max){
         MyString[len++]=c;
       }
   } while(c!=13);
   MyString[len]=0;
}
//////////////////////////////////////////
//////////////////////////////////////////
void check_OK(char* MyString, unsigned int max){
   unsigned int len;
   char c;
   --max;
   len=0;
   
   do {
     c = timed_getc();
         MyString[len++]=c;
   } while(len!=max);
   
   if(strcmp(MyString, "\r\nOK\r\n")){
      LED_probe();    
      break;
   }
   
   MyString[len]=0;
}
//////////////////////////////////////////
//////////////////////////////////////////

void off_echo(){
   fprintf(pucca,"ATE0\r\n");
   delay_ms(1000);
}

void probe(){
   fprintf(pucca,"AT\r\n");
   delay_ms(2000);
}

char receive[10];

void main(){
   usbInit();
   delay_ms(200);
   off_echo();
   
   while(true)
   {
      probe();
      if(timed_getc() > 0){
         check_OK(receive, 5);
      }
   }
}
