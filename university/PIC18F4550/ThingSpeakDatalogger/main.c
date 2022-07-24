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
////////////LCD PIN's Definition///////////
///////////////////////////////////////////
#define LED PIN_D0

#define LCD_RS_PIN      PIN_D0
#define LCD_RW_PIN      PIN_D1

#define LCD_ENABLE_PIN  PIN_D2
S
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7

#include <lcd.c>

void off_echo(){
   fprintf(pucca,"ATE0\r\n");
   delay_ms(1000);
}S

////////////Sensor PIN's Definition////////
///////////////////////////////////////////
#define DHT11_pin PIN_A2

#include <DHT11_Lib.c>

//////////////SENSOR VARIABLES/////////////
///////////////////////////////////////////

float temp = 30;
float hum = 30;

////////////////UPDATE LCD/////////////////
///////////////////////////////////////////

void show_titles(){
   lcd_gotoxy(0,0);
   printf(lcd_putc,"RH:");
   
   lcd_gotoxy(0,1);
   printf(lcd_putc,"Temp:");  
}

void update(){
   //Temp
   lcd_gotoxy(6,1);
   printf(lcd_putc,"%.1f",temp);
   //RH
   lcd_gotoxy(4,0);
   printf(lcd_putc,"%.1f",hum);
}
//////////////////////////////////////////
//////////////////////////////////////////
void SendThingSpeak(){
   fprintf(pucca,"AT\r\n");
   delay_ms(1000);
   fprintf(pucca,"AT+CIPMUX=1\r\n");
   delay_ms(1000);
   fprintf(pucca,"AT+CIPSTART=0,\"TCP\",\"184.106.153.149\",80\r\n");
   delay_ms(1000);
   fprintf(pucca,"AT+CIPSEND=0,100\r\n");
   delay_ms(1000);
   fprintf(pucca,"GET /update?api_key=4NZWPSSD36STQHW2&field1=%.1f&field2=%.1f\n",temp,hum);
   delay_ms(1000);
}

char receive[10];

void main(){
   lcd_init();
   DHT11_init();
   
   lcd_putc("\f"); 
   show_titles();
   
   while(true)
   {
      DHT11(temp,hum);
      temp=Temp;
      hum=Hum;
      update();
      delay_ms(25);
      SendThingSpeak();
   }
}
