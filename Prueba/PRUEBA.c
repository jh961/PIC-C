#include <PRUEBA.h>
#fuses XT, NOWDT
#use delay (clock = 4000000) // reloj 4 Mhz
#use fast_io(B) //configurar rapidamente puerto B

void main()
{

  port_b_pullups(true);
  set_tris_b(0x1);
  output_low(pin_B1);
  
  while(true){
  while(input(pin_b2)==1)
  {
  if (input(pin_b0)==1)
  output_low(pin_b1);
  else 
  output_high(pin_B1);
  
  }

  WHILE (input(pin_b2)==0){
 
 output_high(PIN_B1);
 delay_ms(500);
 output_low(PIN_B1);
 delay_ms(200);
  }
 
 }

}
