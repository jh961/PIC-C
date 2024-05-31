#include <generador de ciclos.h>
#fuses hs,nowdt,nolvp
#use delay(clock=20000000) 
#include <lcd.c>
//#device ADC=10
int valor;
float  voltaje;

#INT_TIMER2             //interruccion del timer1

void TIMER_ISR(VOID)
{
   output_toggle(pin_b0);            // salida de señal pueto
   set_timer2(11);                 // carga timer con 1k
}

void main()
{
   set_tris_b (0x00);
   set_tris_a (0xff);
   setup_timer_2( T2_div_by_4,1023, 1);            // configuracion timer
   enable_interrupts(INT_timer2);           // avilita la interruccion por derrame
   enable_interrupts(global);
   lcd_init();
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(AN0);
   set_adc_channel(0);
   delay_us(10);

   WHILE (true)
   {
      valor = read_adc();
      delay_ms(10);
      lcd_putc('\f');
      printf(lcd_putc,"vadc = %u", valor);
      output_bit(pin_b1, valor);
      voltaje = (valor=0.0196);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"volt = %g", voltaje);
      delay_ms(1000);
   }
}

