#include <18F4550.h>
#DEVICE PASS_STRINGS=IN_RAM
#device ADC=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)  //#use delay(clock=20000000)
#include <usb/usb_bootloader.h> //Comenta esta línea si no usas Bootloader
#include <JACSS_CDC.c>  //Libreria que genera el puerto COM virtual para comunicacion.
#use rs232(baud=9600, BITS=8, PARITY=N, xmit=PIN_C6,rcv=PIN_C7,STREAM=pucca, ERRORS)
//////////////////////////////////////////
//////////////////////////////////////////
#include <string.h>
#include <stdio.h>

////////////LCD PIN's Definition///////////
///////////////////////////////////////////

#define LCD_RS_PIN      PIN_D0
#define LCD_RW_PIN      PIN_D1

#define LCD_ENABLE_PIN  PIN_D2

#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7

#include <lcd.c>

//////////////////////////////////////////
//////////////////////////////////////////

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

char receive[64];
#zero_ram
void main()
{
   //usbInit();
   //delay_ms(200);
   
   LCD_Init();
   LCD_putc("\f");
   
   lcd_gotoxy(1,1);
   printf(lcd_putc,"Mis dos amores");
   lcd_gotoxy(1,0);
   printf(lcd_putc,"Stella y Yayo <3");
   
   while(true)
   {
      if(timed_getc() > 0)
      {
         read_string(receive, 64);
         fprintf(pucca,"Receive: %s\r\n",&receive);
    
         delay_ms(100);
         LCD_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc,"Recibi:");
         lcd_gotoxy(1,0);
         printf(lcd_putc,"%s",&receive);
      }
   }
}



