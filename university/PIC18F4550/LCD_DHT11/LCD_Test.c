#include <18F4550.h>
#device ADC=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)  //#use delay(clock=20000000)
#include <usb/usb_bootloader.h> //Comenta esta línea si no usas Bootloader
#include <JACSS_CDC.c>  //Libreria que genera el puerto COM virtual para comunicacion.

////////////Pre functions///////////
///////////////////////////////////////////

void update_set();
void state_motor();
void on_off();

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

////////////Sensor PIN's Definition////////
///////////////////////////////////////////

//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#define DHT11_pin PIN_A2

#include <DHT11_Lib.c>

/////////////PIN's Definition//////////////
///////////////////////////////////////////

#define push1 PIN_A0
#define push2 PIN_A1

#define motor PIN_B2

///////////////SET TEMPERATURE/////////////
///////////////////////////////////////////

int value1 = 0;
int value2 = 0;

int counter = 30;

void readpin(){
   value1 = input(push1);
   value2 = input(push2);
   delay_ms(50);
   
   if(value1==1){
      counter++;
      update_set();
   }
   if(value2==1){
      counter--;
      update_set();
   }
}

//////////////SENSOR VARIABLES/////////////
///////////////////////////////////////////

float temp = 30;
float hum = 30;

////////////////MOTOR CONTROL//////////////
///////////////////////////////////////////

int flag = 0;

void on_off(){
   if(counter<=temp){
      flag = 1;
      output_high(motor);
      state_motor();
   }
   else{
      flag = 0;
      output_low(motor);
      state_motor();
   }
}

////////////////UPDATE LCD/////////////////
///////////////////////////////////////////

void show_titles(){
   lcd_gotoxy(0,0);
   printf(lcd_putc,"RH:");
   
   lcd_gotoxy(0,1);
   printf(lcd_putc,"Temp:");
   
   lcd_gotoxy(9,0);
   printf(lcd_putc,"Step:");
   
   lcd_gotoxy(11,1);
   printf(lcd_putc,"Set:");
   
   update_set();
   state_motor();
}

void update(){
   //Temp
   lcd_gotoxy(6,1);
   printf(lcd_putc,"%.1f",temp);
   //RH
   lcd_gotoxy(4,0);
   printf(lcd_putc,"%.1f",hum);
}

void state_motor(){
   if(flag==1){
      lcd_gotoxy(14,0);
      printf(lcd_putc,"ON ");
   }
   else{
      lcd_gotoxy(14,0);
      printf(lcd_putc,"OFF");
   }
}

void update_set(){
   lcd_gotoxy(15,1);
   printf(lcd_putc,"%d",counter);
}

///////////////////////////////////////////
///////////////////////////////////////////

void main()
{
   lcd_init();
   DHT11_init();
   
   usbInit();
   delay_ms(200);
   
   lcd_putc("\f"); 
   show_titles();

   while(TRUE)
   {
      DHT11(temp,hum);
      temp=Temp;
      hum=Hum;
      update();
      readpin();
      on_off();
      delay_ms(25);
   }

}
