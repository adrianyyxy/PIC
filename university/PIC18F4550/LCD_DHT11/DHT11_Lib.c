
#INCLUDE <stdlib.h>


unsigned char values[5];

void DHT11_init(); 
unsigned char get_byte(); 
unsigned char get_data();
float string_to_float(char dat1, char dat2);

void DHT11_init() 
{ 
   output_float(DHT11_pin); 
   delay_ms(1000); 
} 

unsigned char get_byte() 
{ 
   unsigned char s = 0; 
   unsigned char value = 0; 

   for(s = 0; s < 8; s += 1) 
   { 
      value <<= 1; 
      while(!input(DHT11_pin)); 
      delay_us(30); 

      if(input(DHT11_pin)) 
      { 
          value |= 1; 
      } 
      while(input(DHT11_pin)); 
   } 
   return value; 
} 


unsigned char get_data() 
{ 
   short chk = 0; 
   unsigned char s = 0; 
   unsigned char check_sum = 0; 

   output_high(DHT11_pin); 
   output_low(DHT11_pin); 
   delay_ms(18); 
   output_high(DHT11_pin); 
   delay_us(26); 
    
   chk = input(DHT11_pin); 
   if(chk) 
   { 
      return 1; 
   } 
   delay_us(80); 
    
   chk = input(DHT11_pin); 
   if(!chk) 
   { 
      return 2; 
   } 
   delay_us(80); 

   for(s = 0; s <= 4; s += 1) 
   { 
       values[s] = get_byte(); 
   } 
  
   output_high(DHT11_pin); 
    
   for(s = 0; s < 4; s += 1) 
   { 
       check_sum += values[s]; 
   } 
    
   if(check_sum != values[4]) 
   { 
      return 3; 
   } 
   else 
   { 
      return 0; 
   } 
} 

void DHT11(float &Temp, float &Hum)
{
   
   unsigned char state = 0;
   state = get_data(); 
      
      switch(state) 
      { 
            case 1: 
            { 
            } 
            case 2: 
            { 
               //printf(usbWrite,"\fNo Sensor Found! \r\n");
               //printf("\fNo Sensor Found! \r\n"); 
               break; 
            } 
            case 3: 
            { 
               //printf(usbWrite,"\fChecksum Error! \r\n"); 
               //printf("\fChecksum Error! \r\n");
               break; 
            } 
            default: 
            { 
 
               Temp=string_to_float(values[2],values[3]);
               Hum=string_to_float(values[0],values[1]);

               //printf(usbWrite,"Tmp: %u.%02u C\n\r",values[2], values[3]);
               //printf(usbWrite,"R.H: %u.%02u \n\r", values[0], values[1] );
               
               printf("%f C  %f \n\r",Temp,Hum);
               delay_ms(200);
               break; 
            } 
      }
   
}

float string_to_float(char dat1, char dat2)
{
   char concatenated[6];
   sprintf(concatenated,"%u.%01u\0",dat1,dat2);
   return(atof(concatenated));
}

