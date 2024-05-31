#include <18f4550.h>
#DEVICE ADC=10
#fuses HS,MCLR,NOWDT,NOPROTECT,NOPUT,NOBROWNOUT,NOPBADEN,NOLVP,NOCPD,NODEBUG,NOWRT,NOVREGEN
#FUSES CPUDIV1         //DIVISION DE FRECUENCIA DEL OSCILADOR: 1
#use delay(clock=20000000)
#include <math.h>
#include <lcd.c>


float distancia,valor,valorg=0,valor1=0;
int16 tiempo;

#define trig pin_A2
#define echo pin_A3

#define ledazul pin_B0
#define ledverde pin_B1


void main()
{
set_tris_a (0xff);
set_tris_b (0xff);


lcd_init();                             
printf(LCD_PUTC, "\f Iniciando.");
delay_ms(500);
printf(LCD_PUTC, "\f Iniciando..");
delay_ms(500);
printf(LCD_PUTC, "\f Iniciando...");
delay_ms(500);
   
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   
    printf (lcd_putc, "AUTORES");
   lcd_gotoxy (1, 2) ;
   printf (lcd_putc, "PORQUE NOS ODIA?");
   delay_ms (1000);
   lcd_putc ('\f');
   
   
   setup_adc (ADC_CLOCK_div_8);
   setup_adc_ports (AN0);
   set_adc_channel (0);
   delay_us (10);
                            


while(true){

output_high(trig);                   
delay_us(20);                       
output_low(trig);

   
while(input(echo)==0){}

set_timer1(0);                         
while(input(echo)==1){}

tiempo=get_timer1();
distancia=(tiempo*10)/(360);  //distancia=(tiempo*10)/(58.0);
valor=(3.5-(distancia/6));
   
    valorg = read_adc (); /////////// tomar datos condensador
    delay_ms (50);
    valorg=((valorg*5)/1024);
    valor1=(5-valorg)*2.3;

   printf (lcd_putc, "Lectura Sensores");
   lcd_gotoxy (1, 2) ;
   printf (lcd_putc, "Lu=%03.2f Lc=%03.2f",valor,valor1);
   delay_ms (200);
   lcd_putc ('\f');


if(distancia>10){
output_high(ledazul);
output_low(ledverde);
}
else{
output_low(ledazul);
output_high(ledverde);
}
//delay_ms(500);
}
}
