#include <18f4550.h>
#fuses hs,WDT,NOPROTECT,NOPUT, NOPBADEN //ordenes para el programador
#use delay (clock=4000000)
#include <lcd.c>

 long mig=0;

void main (void)
   {
   lcd_init(); // inicializar la libreria de trabajo para este caso lcd

   lcd_putc("\t\t miguel perez \n");
   delay_ms(1000);
while(true)
{
  for (mig=0;mig<1024;mig++)
      {
      printf(lcd_putc," controlador %lu ",mig);
     lcd_gotoxy(1,2);
     delay_ms(100);
      }
 }
   }
