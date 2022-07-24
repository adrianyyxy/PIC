#include <18F4550.h>
#device ADC=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)  //#use delay(clock=20000000)
#include <usb/usb_bootloader.h> //Comenta esta línea si no usas Bootloader
#include <JACSS_CDC.c>  //Libreria que genera el puerto COM virtual para comunicacion.

int16 value = 0.0;

void main()
{
   usbInit();
   delay_ms(200);
   
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   
   while(true)
   {
      /*
      output_high(PIN_A4);
      delay_ms(1000);
      output_low(PIN_A4);
      delay_ms(1000);
      */
      
      set_adc_channel(0);
      delay_us(10);
      value=read_adc();
      
      printf(usbWrite,"Test: %Ld \r\n", value);
      
      if(value>600){
         output_low(PIN_A3);
      }
      else{
         output_high(PIN_A3);
      }
      
      delay_ms(1000);
   }

}
