#include <16f877a.h>
#fuses XT,NOWDT,NOPROTECT,PUT,NOBROWNOUT,NOLVP
#use delay(clock=4000000)
#include <lcd.c>

#use i2c(SLAVE, SDA=PIN_C4, SCL=PIN_C3, ADDRESS=0XB0)
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
         //output_b(255);


      }


   }
   if((state == 0x80)&& (flag==1))                     //Master is requesting data
   {
      i2c_write(dato);
      flag=0;
   }
}




void main (){
enable_interrupts(GLOBAL);
enable_interrupts(INT_SSP);

setup_adc_ports (AN0);
setup_adc(ADC_CLOCK_INTERNAL );

   output_b(0);

while (true){
set_adc_channel(0);
delay_ms(1);
dato=read_adc();
delay_ms(1);
output_b(dato);

}

}





