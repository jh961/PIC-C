#include <18f4550.h>
#DEVICE ADC=10
#fuses HS,MCLR,NOWDT,NOPROTECT,NOPUT,NOBROWNOUT,NOPBADEN,NOLVP,NOCPD,NODEBUG,NOWRT,NOVREGEN
#FUSES CPUDIV1         //DIVISION DE FRECUENCIA DEL OSCILADOR: 1
#use delay(clock=20000000)
#include <math.h>
#include <lcd.c>


float valorg,valor1;


void main (){
set_tris_a (0xff);
set_tris_b (0xff);


 lcd_init ();
   
   printf (lcd_putc, "AUTORES");
   lcd_gotoxy (1, 2) ;
   printf (lcd_putc, "PORQUE NOS ODIA?");
   delay_ms (1000);
   lcd_putc ('\f');
   
   
   setup_adc (ADC_CLOCK_div_8);
   setup_adc_ports (AN0);
   set_adc_channel (0);
   delay_us (10);

while (true){

output_toggle(PIN_b0);

    valorg = read_adc ();
    valor1=valorg;
   delay_ms (100);
   //valor1=exp (((2.249091222)*((valorg*5)/1024))+1.383707098);
   valor1=((valorg*5)/1024);
   valorg=((valorg*5)/1024);
   valor1=(7.942109*exp ((1.16538853)*valor1));
   
   lcd_putc ('\f');
   printf (lcd_putc, "Voltaje Galga");
   lcd_gotoxy (1, 2) ;
   printf (lcd_putc, "%03.3fv %03.3fg",valorg,valor1);
   
   
}
}
