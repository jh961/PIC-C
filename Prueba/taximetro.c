#include <taximetro.h>
#use delay( clock = 20000000 ) // reloj de 20 MHz 
#fuses HS,NOWDT,PUT
#define H_TO_L

int vector[10]={0b11000000, 0b11111001, 0b10100100,0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10011000};
int i=0,i1=0,j1=0,j=0,m0=0,m1=0,cont=0;//varibales para contar
#INT_EXT

void EXT_ISR(VOID)
{
   WHILE (input (pin_b0) == 1)
   {
      IF (m1 == cont)
      {
         i = 0;
         j = 0;
         m1 = 0;
         cont = 0;
      }

      IF (input (PIN_B3) == 1)
      {
         cont++;

         IF (cont == 100)
         {
            cont = 0;
         }

         WHILE (input (PIN_B3) == 1){}// antirrebote
      }

      else IF (input (PIN_B4) == 1)
      {
         cont--;

         IF (cont == - 1)
         {
            cont = 99;
         }

         WHILE (input (PIN_B4) == 1){}// antirrebote
      }

      i = cont / 10; //decenas
      j = cont % 10; //unidades
      output_high (pin_a3);
      output_low (pin_a2);
      output_low (pin_a5);
      
      output_high (PIN_A0);
      output_low (PIN_A1); //unidades
      output_D (vector[i]);
      delay_us (1000);
      
      output_low (PIN_A0);
      output_high (PIN_A1);
      output_D (vector[j]);
      delay_us (1000);
      output_low (PIN_A0);
      output_low (PIN_A1);
   }
}

#INT_EXT1

void EXT1_ISR(VOID)
{
   
   m0++;

   IF (m1 == cont)
   {
      m0 = 0;
   }

   else IF (m0 == 2)
   {
      m1++;
      m0 = 0;
   }

   output_high (pin_a5);
   output_low (pin_a3);
   output_low (pin_a2);
}

void main( VOID )
{
   set_tris_b (255);
   set_tris_d (0x00);
   set_tris_a (255); //salidas para activar cada display
   enable_interrupts (INT_EXT) ;
   enable_interrupts (INT_EXT1) ;
   enable_interrupts (GLOBAL); // Habilitación general de interrupción
   WHILE (true)
   {
      IF (m1 == cont)
      {
         output_high (pin_a2);
         output_high (pin_a3);
         output_high (pin_a5);
         output_low (pin_b5);
         delay_ms (100);
      }

      else IF (m1 != cont)
      {
         output_high (pin_a2);
         output_low (pin_a3);
         output_low (pin_a5);
         output_high (pin_b5);
      }

      i1 = m1 / 10; //decenas
      j1 = m1 % 10; //unidades
      
      output_high (PIN_A0);
      output_low (PIN_A1); //unidades
      output_D (vector[i1]);
      delay_us (1000);
      
      output_low (PIN_A0);
      output_high (PIN_A1);
      output_D (vector[j1]);
      delay_us (1000);
      output_low (PIN_A0);
      output_low (PIN_A1);
   }
}

 /* UNIVERSIDAD DISTRITAL FRANCISCO JOSE DE CALDAS
                      AUTOR
                    JAIME DIAZ 
                    20141573116
  */
