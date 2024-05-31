#include <modulacion2.h>
#fuses hs,nowdt,nolvp
#use delay(clock=20000000) 
#include <lcd.c>
//#device ADC=10

   int valor; // valores hasta 255
   long ciclo_util=0;  // tienes valores mayores a 6025 

/*
cristal/ reloj = 20Mhz
tosc=1/cristal
tmr2 prescaler = t2_div_by_4  tres posiblilidades 2, 4, 16
setup_timer_2(t2_div_by_4,pr2,1);
pr2=30

periodo PWM / T = (pr2+1)* 4 * tosc *tmr2 prescaler
perido PWM = (30+1)*4*0.05us*4 = 0.00001

frecuencia =1/ perido PWM 
*/

void main()
{
   
   set_tris_b(0x00);
   setup_ccp1(ccp_pwm);
   setup_timer_2 (T2_div_by_16,30,1);   // configuracion timer
 
   setup_adc(ADC_CLOCK_INTERNAL); 
   setup_adc_ports(AN0);   
   set_adc_channel(0);            
   delay_us(10);

   WHILE (true)
   {
   valor= read_adc ();
   ciclo_util= valor/2;          // esta valor es dividido por el pr2*4 /maximo
   set_pwm1_duty(ciclo_util);  
   }
}





