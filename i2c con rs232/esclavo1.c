#include <18f4550.h>
#fuses HS,MCLR,NOWDT,NOPROTECT,NOPUT,NOBROWNOUT,NOPBADEN,NOLVP,NOCPD,NODEBUG,NOWRT,NOVREGEN
#FUSES CPUDIV1         //DIVISION DE FRECUENCIA DEL OSCILADOR: 1
#use delay(clock=20000000)
#include <lcd.c>

#use i2c(slave, fast, sda=PIN_B0, scl=PIN_B1, address=0XB0)
int flag =0;
int dato;
byte incoming,state;

#INT_SSP
void ssp_interupt ()
{
BYTE incoming, state;

   state = i2c_isr_state();

   if(state < 0x80)                     //Master is sending data
   {
      incoming = i2c_read();

      if (incoming == 0x05){

         flag=1;
         
      output_high(pin_a5);

      }


   }
   if((state == 0x80)&& (flag==1))                     //Master is requesting data
   {
      i2c_write(dato);
      flag=0;
   }
}




void main (){
set_tris_b (0xff);
set_tris_a (0x0f);
enable_interrupts(GLOBAL);
enable_interrupts(INT_SSP);

 lcd_init();
 lcd_putc("\f");
 lcd_gotoxy (1, 1) ;
    printf (lcd_putc, "AUTOR");
    lcd_gotoxy (1, 2) ;
    printf (lcd_putc, "JUAN");
    delay_ms(1000);
    
setup_adc_ports (AN0);
setup_adc(ADC_CLOCK_INTERNAL );
set_adc_channel(0);
delay_us(10);
 

while (true){
output_low(pin_a5);
dato=read_adc();
delay_ms(1);
lcd_putc("\f");
  lcd_gotoxy (1, 1) ;
    printf (lcd_putc, "Dato es =");
    lcd_gotoxy (1, 2) ;
    printf (lcd_putc, "%u",dato);
    delay_ms(10);
}

}





