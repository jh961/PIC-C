#include <18f4550.h>
#fuses HS,MCLR,NOWDT,NOPROTECT,NOPUT,NOBROWNOUT,NOPBADEN,NOLVP,NOCPD,NODEBUG,NOWRT,NOVREGEN
#FUSES CPUDIV1         //DIVISION DE FRECUENCIA DEL OSCILADOR: 1
#use delay(clock=20000000)
#include <lcd.c>

#use i2c(master, scl=PIN_B1, sda=PIN_B0,SLOW)

int valor=12;

void main(){
set_tris_a (0x0f);
 lcd_init();
 lcd_putc("\f");
 lcd_gotoxy (1, 1) ;
    printf (lcd_putc, "AUTOR");
    lcd_gotoxy (1, 2) ;
    printf (lcd_putc, "JUAN");
    delay_ms(1000);
    
 while (true){


if (input(pin_a0)==1){

   i2c_start();
   
   i2c_write(0xB0); 
   i2c_write(0x05);
  
   i2c_start();
   i2c_write(0xB1);
   valor=i2c_read(0);
 
   i2c_stop();
   output_high(pin_a5);
   delay_ms(1000);
   while (input(pin_a0)==1){}
}
output_low(pin_a5);
lcd_putc("\f");
  lcd_gotoxy (1, 1) ;
    printf (lcd_putc, "Dato es =");
    lcd_gotoxy (1, 2) ;
    printf (lcd_putc, "%u",valor);
    delay_ms(10);
   
   
}




 }

