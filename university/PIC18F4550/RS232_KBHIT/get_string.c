/* #include <get_string.c>
*
* Creada por: Ing. Abiezer Hernandez O.
* Fecha de creacion: 04/08/2019
* Electronica y Circuitos
*
*/

#include <stdio.h>
#include <string.h>

void read_string(char* s, unsigned int max)
{
   unsigned int len;
   char c;
   --max;
   len=0;
   do {
     c = getc();
     if(c==8) {
        if(len>0){
          len--;
        }
     }else if ((c>=' ')&&(c<='~'))
       if(len<max){
         s[len++]=c;
       }
   } while(c!=13);
   s[len]=0;
}

#ifdef STREAM_PIC
void read_string_stream(char* s2, unsigned int max2)
{
   unsigned int len2;
   char c2;
   --max2;
   len2=0;
   do {
     c2 = getch(SPIC);
     if(c2==8) {
        if(len2>0){
          len2--;
        }
     }else if ((c2>=' ')&&(c2<='~'))
       if(len2<max2){
         s2[len2++]=c2;
       }
   } while(c2!=13);
   s2[len2]=0;
}
#endif

void read_substring(char* cp, char* vc, int inc , int fn)
{
   int pt = 0;
   for(int lt=inc; lt<=fn; lt++)
   {
      vc[pt] = cp[lt];
      pt++;
   }
   pt = 0;
}

void read_string_until(char stopchar, char* buffer_rx, int st_size)
{
   unsigned int con_t = 0;
   while(*(buffer_rx-1) != stopchar)
   {
      con_t++;
      *buffer_rx++ = getc();
      if(con_t >= st_size) break;
   }
   *--buffer_rx=0;
}

char *find_string(char *s1, char *s2)
{
    char *s, *t;
    while(*s1)
    {
        for(s = s1, t = s2; *t && (*s == *t); ++s, ++t);
        if (*t == '\0')
            return s1;
        ++s1;
    }
    return 0;
}
