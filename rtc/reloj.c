// Real Time Clock & NVRAM
// Hardware DS1307 of Dallas Maxim
// With interface I2C
 
#include <18f4550.h>
#fuses HS,MCLR,NOWDT,NOPROTECT,NOPUT,NOBROWNOUT,NOPBADEN,NOLVP,NOCPD,NODEBUG,NOWRT,NOVREGEN
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
 
// Libreria DS1307.c //////////////////////////////////////////////////////////
 
//#define RTC_SDA  PIN_B0
//#define RTC_SCL  PIN_B1
 
#include <_ds1307.c>
 
//#define USE_INTERRUPTS 1
 
///////////////////////////////////////////////////////////////////////////////

char rec='f';
int sec,min,hrs,day,month,yr,dow;
char sdow[11];
 
// INTERRUPCION por RECEPCION SERIE -------------------------------------------
 
#int_rda
void serial_isr() {

     rec=fgetc();
    
}
 
void lee_y_transmite_date_and_time(void){
 
   ds1307_get_day_of_week((char*) sdow);
   ds1307_get_date(day,month,yr,dow);
   ds1307_get_time(hrs,min,sec);
   printf("\%s \%02d/\%02d/\%02d ",sdow,day,month,yr);
   printf("\%02d:\%02d:\%02d:\%02d\r\n", hrs,min,sec,dow);
}
 
void main() {
 
  
  
   set_tris_b(0b00000111);
   set_tris_e(0b00010000);
   output_e(0x00);
   set_tris_c(0b10000000);
 
   
   printf("\r\n");
   printf("based on DS1307 Dallas Maxim Hardware\r\n\n");
   printf("Available RS232 commands:\r\n");
   printf("  [o] Dump Date & Time ON\r\n");
   printf("  [f] Dump Date & Time OFF\r\n\n");
  
 
   enable_interrupts(int_ext2);
   enable_interrupts(int_rda);
   enable_interrupts(global);
 
   // Inicializa DS1307
   printf("Inicializando DS1307 ...\r\n\n");
    delay_ms(1000);
   ds1307_init(DS1307_OUT_ON_DISABLED_HIHG | DS1307_OUT_ENABLED | DS1307_OUT_1_HZ);
   //ds1307_set_date_time(8,8,15,6,12,12,12);
   // Set date for -> 5 Agosto 2006 Viernes
   // Set time for -> 02:50:00
   // printf("Set Date & Time to ...\r\n");
   // ds1307_set_date_time(5,8,6,5,2,50,00);
 
   // Lee Fecha y Hora actual y transmite
 
   printf("Fecha y Hora actual en el DS1307\r\n\n");
   lee_y_transmite_date_and_time();
   printf("\r\n\n");
 
   // Test de RAM -> primero Write, segundo Read
   printf("Test de la NVRAM interna (Write and read) ...\r\n\n");

   do{
 
      if(rec=='o'){
        
            printf("Set Dump ON\r\n\n");
          
         lee_y_transmite_date_and_time();
          delay_ms(1000);
         
      }else if(rec=='f'){
        
            printf("\r\nSet Dump OFF\r\n\n");
           rec=2;
         
      }
   } while (TRUE);
}
 
