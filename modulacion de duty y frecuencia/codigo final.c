#include "C:\Users\JAIME DIAZ\Desktop\LABORATORIOS UD\PROGRAMAS PIC\codigo final.h"
#fuses hs,nowdt,nolvp,noput,put,noprotect,nodebug,cpudiv1,usbdiv
#use delay(clock=20000000) 
#include <lcd.c>
#define L_TO_H
INT   x = 0, y = 0,z=0,n=0;
long valor=0, time = 255, subida = 0, bajada = 0,pwmh = 0,modi=0;

/*
frecuencia =10k
tiempo deseado= 1/(frecuencia*2)
cristal/ reloj = 20Mhz
division de crital=t2_div_b_#/cristal
setup_timer_1(t1_internal|t1_div_by_#);
set_timer1(time);

Time = 65536-((tiempo requerido)/(4/division de crital))
frecuencia =(1/ perido PWM)*2 
*/
#INT_EXT

void EXT_ISR(VOID)
{
   disable_interrupts (INT_TIMER0); // inavilita la interruccion por derrame
   disable_interrupts (INT_ext);
   disable_interrupts (global);
   output_low (pin_b7) ;

   WHILE (input (pin_b0) == 1)
   {
      IF ((input (pin_b0) == 1)&& (z == 0) )
      {
         IF (input (pin_b4) == 1)
         {
            y++;

            IF (y == 4)
            {
               y = 0;
            }

            WHILE (input (pin_b4) == 1){}
         }

         IF (y == 0)
         {
            
            lcd_gotoxy (1, 1) ;
            printf (lcd_putc, "@ 1K HZ");
            lcd_gotoxy (1, 2) ;
            printf (lcd_putc, " 2.5K Hz");
            }else IF (y == 1){
            
            lcd_gotoxy (1, 1) ;
            printf (lcd_putc, " 1K Hz");
            lcd_gotoxy (1, 2) ;
            printf (lcd_putc, "@ 2.5K Hz");
            }else IF (y == 2){
            
            lcd_gotoxy (1, 1) ;
            printf (lcd_putc, "@ 4K Hz");
            lcd_gotoxy (1, 2) ;
            printf (lcd_putc, " 10K Hz");
            }else IF (y == 3){
            
            lcd_gotoxy (1, 1) ;
            printf (lcd_putc, " 4K Hz");
            lcd_gotoxy (1, 2) ;
            printf (lcd_putc, "@ 10K Hz");
         }
      }

      ELSE
      {
         
         lcd_gotoxy (1, 1) ;
         printf (lcd_putc, "Seleccionó ");
         
         IF (y == 0)
         {
            lcd_gotoxy (1, 2) ;
            printf (lcd_putc, " 1K HZ");
            setup_timer_0 (rtcc_div_16|rtcc_internal|rtcc_8_bit);
            }else IF (y == 1){
            
            lcd_gotoxy (1, 2) ;
            printf (lcd_putc, " 2.5K Hz");
            setup_timer_0 (rtcc_div_8|rtcc_internal|rtcc_8_bit);
            }else IF (y == 2){
            
            lcd_gotoxy (1, 2);
            printf (lcd_putc, " 4K Hz");
            setup_timer_0 (rtcc_div_8|rtcc_internal|rtcc_8_bit);
            }else IF (y == 3){
            
            lcd_gotoxy (1, 2) ;
            printf (lcd_putc, " 10K Hz");
            setup_timer_0 (rtcc_div_2|rtcc_internal|rtcc_8_bit);
         }
      }

      delay_ms (50);
      lcd_putc ('\f');
      
      IF (input (pin_b3) == 1)
      {
         z = 1;
         
         WHILE (input (pin_b3) == 1){}
      }
   }

   enable_interrupts (INT_TIMER0); // avilita la interruccion por derrame
   enable_interrupts (INT_ext);
   enable_interrupts (global);
}

#INT_timer0

void timer0_isr(VOID)
{
   output_toggle (pin_b7);
   
   
   IF (x == 0)
   {
      x = 1;
      output_low (pin_b5);
      set_timer0 (subida); // carga timer con 1k
      }ELSE {
      x = 0;
      output_high (pin_b5);
      set_timer0 (bajada);
   }

   //set_timer0 (time);
}

  
void main()
{
   
   
   set_tris_a (0xff);
   set_tris_b (0x0f);
   //set_tris_d (0x00);
   
   lcd_init ();
   
   printf (lcd_putc, "AUTOR");
   lcd_gotoxy (1, 2) ;
   printf (lcd_putc, "JAIME DIAZ");
   delay_ms (1000);
   lcd_putc ('\f');
   
   
   // set_timer0 (time);
   enable_interrupts (INT_TIMER0); // avilita la interruccion por derrame
   enable_interrupts (INT_ext);
   enable_interrupts (global);
   
   setup_timer_0 (rtcc_div_16|rtcc_internal|rtcc_8_bit);
   
   setup_adc (ADC_CLOCK_internal);
   setup_adc_ports (AN0);
   set_adc_channel (0);
   delay_us (10);

   WHILE (true)
   {
      
      valor = read_adc ();
      pwmh = valor;
      // modi = (9 * valor) / 1023;
      // delay_ms (10);
      output_high (pin_b6);
      z = 0;
      
      
      // setup_timer_0 (rtcc_div_2|rtcc_internal|rtcc_8_bit);
      
      // lcd_gotoxy (1, 1) ;
     // lcd_putc( "DUTY = ");
      //lcd_gotoxy (1, 2) ;
      
      
      IF (y == 0)
      {
         /// 1k prescaler de 16
         IF ( (pwmh <= 113)&& (pwmh >= 0)){            //10%
            subida = 13;
            bajada = 193;
            }else IF ( (pwmh <= 226)&& (pwmh >= 114) ){ //20 %
            subida = 33;
            bajada = 173;
            }else IF ( (pwmh <= 339)&& (pwmh >= 227) ){ //30 %
            subida = 53;
            bajada = 153;
            }else IF ( (pwmh <= 452)&& (pwmh >= 340) ){ //40 %
            subida = 83;
            bajada = 123;
            }else IF ( (pwmh <= 565)&& (pwmh >= 453)) { //50 %
            subida = 103;
            bajada = 103;
            }else IF ( (pwmh <= 678)&& (pwmh >= 566)) { //60 %
            subida = 123;
            bajada = 83;
            }else IF ( (pwmh <= 791)&& (pwmh >= 679)) { //70 %
            subida = 153;
            bajada = 53;
            }else IF ( (pwmh <= 904)&& (pwmh >= 792)) { //80 %
            subida = 173;
            bajada = 33;
            }else IF ( (pwmh <= 1023)&& (pwmh >= 905)) { //90 %
            subida = 193;
            bajada = 13;
         }

         } else IF (y == 1){  /// 2.5k prescaler de 8
         IF ( (pwmh <= 113)&& (pwmh >= 0)){            //10%
            subida = 58;
            bajada = 218;
            }else IF ( (pwmh <= 226)&& (pwmh >= 114) ){ //20 %
            subida = 78;
            bajada = 198;
            }else IF ( (pwmh <= 339)&& (pwmh >= 227) ){ //30 %
            subida = 98;
            bajada = 178;
            }else IF ( (pwmh <= 452)&& (pwmh >= 340) ){ //40 %
            subida = 118;
            bajada = 158;
            }else IF ( (pwmh <= 565)&& (pwmh >= 453)) { //50 %
            subida = 138;
            bajada = 138;
            }else IF ( (pwmh <= 678)&& (pwmh >= 566)) { //60 %
            subida = 158;
            bajada = 118;
            }else IF ( (pwmh <= 791)&& (pwmh >= 679)) { //70 %
            subida = 178;
            bajada = 98;
            }else IF ( (pwmh <= 904)&& (pwmh >= 792)) { //80 %
            subida = 198;
            bajada = 78;
            }else IF ( (pwmh <= 1023)&& (pwmh >= 905)) { //90 %
            subida = 218;
            bajada = 58;
         }

         }else IF (y == 2){  /// 4k prescaler de 8
         IF ( (pwmh <= 113)&& (pwmh >= 0)){         //10%
             subida = 135;
            bajada = 235;
            }else IF ( (pwmh <= 226)&& (pwmh >= 114) ){ //20 %
            subida = 145;
            bajada = 225;
            }else IF ( (pwmh <= 339)&& (pwmh >= 227) ){ //30 %
            subida = 155;
            bajada = 215;
            }else IF ( (pwmh <= 452)&& (pwmh >= 340) ){ //40 %
            subida = 170;
            bajada = 200;
            }else IF ( (pwmh <= 565)&& (pwmh >= 453)) { //50 %
            subida = 185;
            bajada = 185;
            }else IF ( (pwmh <= 678)&& (pwmh >= 566)) { //60 %
            subida = 200;
            bajada = 170;
            }else IF ( (pwmh <= 791)&& (pwmh >= 679)) { //70 %
            subida = 215;
            bajada = 155;
            }else IF ( (pwmh <= 904)&& (pwmh >= 792)) { //80 %
            subida = 225;
            bajada = 145;
            }else IF ( (pwmh <= 1023)&& (pwmh >= 905)) { //90 %
            subida = 235;
            bajada = 135;
            
         }

         } else IF (y == 3){  /// 4k prescaler de 8
         IF ( (pwmh <= 113)&& (pwmh >= 0)){       //10%
            subida = 76;
            bajada = 255;
            }else IF ( (pwmh <= 226)&& (pwmh >= 114) ){ //20 %
            subida = 94;
            bajada = 220;
            }else IF ( (pwmh <= 339)&& (pwmh >= 227) ){ //30 %
            subida = 115;
            bajada = 200;
            }else IF ( (pwmh <= 452)&& (pwmh >= 340) ){ //40 %
            subida = 134;
            bajada = 180;
            }else IF ( (pwmh <= 565)&& (pwmh >= 453)) { //50 %
            subida = 160;
            bajada = 154;
            }else IF ( (pwmh <= 678)&& (pwmh >= 566)) { //60 %
            subida = 180;
            bajada = 134;
            }else IF ( (pwmh <= 791)&& (pwmh >= 679)) { //70 %
            subida = 200;
            bajada = 115;
            }else IF ( (pwmh <= 904)&& (pwmh >= 792)) { //80 %
            subida = 220;
            bajada = 94;
            }else IF ( (pwmh <= 1023)&& (pwmh >= 905)) { //90 %
            subida = 255;
            bajada = 76;
         }
      }
   }
}

     
  
   
/*
       
      IF ( (pwmh <= 25)&& (pwmh >= 0)) 
      {
         //10 %
         lcd_gotoxy (1, 2) ;
         printf (lcd_putc, " 10 ");
         }else IF ( (pwmh <= 50)&& (pwmh >= 26) ) { //20 %
         lcd_gotoxy (1, 2) ;
         printf (lcd_putc, " 20 ");
         }else IF ( (pwmh <= 75)&& (pwmh >= 51) ) { //30 %
         lcd_gotoxy (1, 2) ;
         printf (lcd_putc, " 30 ");
         }else IF ( (pwmh <= 100)&& (pwmh >= 76) ) { //40 %
         lcd_gotoxy (1, 2) ;
         printf (lcd_putc, " 40 ");
         
         }else IF ( (pwmh <= 125)&& (pwmh >= 101)) { //50 %
         lcd_gotoxy (1, 2) ;
         printf (lcd_putc, " 50 ");
         }else IF ( (pwmh <= 150)&& (pwmh >= 126)) { //60 %
         lcd_gotoxy (1, 2) ;
         printf (lcd_putc, " 60 ");
         }else IF ( (pwmh <= 175)&& (pwmh >= 151)) { //70 %
         lcd_gotoxy (1, 2) ;
         printf (lcd_putc, " 70 ");
         }else IF ( (pwmh <= 200)&& (pwmh >= 176)) { //80 %
         lcd_gotoxy (1, 2) ;
         printf (lcd_putc, " 80 ");
         }else IF ( (pwmh <= 255)&& (pwmh >= 201)) { //90 %
         lcd_gotoxy (1, 2) ;
         printf (lcd_putc, " 90 ");
      }

         // printf (lcd_putc, " 10 ");
     

      */
