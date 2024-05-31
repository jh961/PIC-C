#include <18f4550.h>
#use delay (clock=20000000)
#fuses nowdt,hs,put
#include <lcd.c>

int mig=0;
char m=400;

void main (void)
   {
   lcd_init(); // inicializar la libreria de trabajo para este caso lcd

   lcd_putc("\t\t miguel perez \n");
   delay_ms(500);

  for (mig=0;mig<255;mig++)
      {
      m=m+1;
      printf(lcd_putc," controlador %c ",m);
     lcd_gotoxy(1,2);
     delay_ms(100);
      }

   }
