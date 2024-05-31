#include <18F4550.h>
#include <THW-24G.h>
//#include <ZMD44102.H>
#fuses HS,NOWDT,NOLVP
#use delay(clock= 20M)
#include <lcd.c>
//#include <KBD4x4_1.C>

#use standard_io(A)//configura el tria para que no joda con la conversion AD


                                 //HOLA=0,QUE TAL=1,CHAO=2,VEMOS=
void hola (void){   
  lcd_gotoxy(1,2);
  printf(lcd_putc, "HOLA");
 }

void quetal (void){
  lcd_gotoxy(1,2);
  printf(lcd_putc, "QUE TAL");
 }

void chao (void){  
  lcd_gotoxy(1,2);
  printf(lcd_putc, "CHAO");
 }

void vemos (void){
  lcd_gotoxy(1,2);
  printf(lcd_putc, "VEMOS");
 }

void run_func(int numfunc){   //Asignación de la función a realizar
                              //viene dada por la variable "item"
   switch(numfunc) {
      case hi:
         hola();
         break;
      case what:
         quetal();
         break;
      case bye:
         chao();
         break;
      case bye2:
         vemos();
         break;   
   }
}

void main() {
   char item;         //Variables de funciones
   char n_menus = 4;   //Número de funciones

   lcd_init();   
   printf(lcd_putc, "Buenas Tardes ");
   lcd_gotoxy(1,2);
   printf(lcd_putc, "profe Jacinto");
   delay_ms(2000) ;
   lcd_putc('\f');
   printf(lcd_putc, "Laboratorio #4");
   lcd_gotoxy(1,2);
   printf(lcd_putc, "C. Digitales II");
   delay_ms(2000);
    lcd_putc('\f');

  while (true) {
   if (input(PIN_A0) == 1) {   //Detecta botón de selección
       item++;                  //Si pulsa aumenta la variable
       delay_ms(300);//Para evitar rebotes
       lcd_putc('\f');     }

if (item > (n_menus-1)) {   //Si la variable supera el número de...
      item = 0; }                 //funciones la inicializa

   switch (item) {
      case 0:
        lcd_gotoxy(1,1);
        printf(lcd_putc, "1* HOLA");
        break;
      case 1:
         lcd_gotoxy(1,1);
        printf(lcd_putc, "2* QUE TAL?");
        break;
      case 2:
         lcd_gotoxy(1,1);
        printf(lcd_putc, "3* CHAO");
        break;
      case 3:
         lcd_gotoxy(1,1);
        printf(lcd_putc, "4* VEMOS");
        break;
   }
  if (input(PIN_A1) == 1)   //Si se pulsa el botón de selección
     {delay_ms(200);         // ANTIREBOTE
     run_func(item);}      //se llama a la función correspondiente
  }
}
