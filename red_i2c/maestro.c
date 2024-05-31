#include <16f877a.h>
#fuses XT,NOWDT,NOPROTECT,PUT,NOBROWNOUT,NOLVP
#use delay(clock=4000000)
#include <lcd.c>

#use i2c(MASTER, SDA=PIN_C4, SCL=PIN_C3,FORCE_HW)

int valor;


void main(){

 lcd_init();
 lcd_putc("\f");
   printf(lcd_putc,"El dato es el %i",valor);

 while (true){


if (input(pin_a0)){

   i2c_start();
   i2c_write(0x0B0);
   i2c_write(0x05);
   i2c_start();
   i2c_write(0xB1);
   valor=i2c_read(0);
   i2c_stop();

   lcd_putc("\f");
   printf(lcd_putc,"El dato es el %u",valor);
   while (input(pin_a0)){}
}




 }




}
