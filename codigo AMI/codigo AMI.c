#include <18f4550.h>
#fuses HS,MCLR,NOWDT,NOPROTECT,NOPUT,NOBROWNOUT,NOPBADEN,NOLVP,NOCPD,NODEBUG,NOWRT,NOVREGEN
#FUSES CPUDIV1         //DIVISION DE FRECUENCIA DEL OSCILADOR: 1
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7,STREAM=pc 1)
#include <stdio.h>


int e=0,d=0,g=1,band=0;
char a,dato[]={0};

#int_rda
void rda_isr()
   {
   output_high(PIN_b0);
   a=fgetc();
   if(a=='@'){
   e=100;
   dato[0]=a;
      for(d=1;d<=e;d++) {
      a=fgetc();
      dato[d]=a;
      
      if(a=='#'){
      e=0;
      }
     }
    }
   }
   
   
void main (){
set_tris_a (0xff);
set_tris_b (0x00);

 enable_interrupts(int_rda);
   enable_interrupts(GLOBAL);

while (true){
output_toggle(PIN_b0);

if(input(PIN_b5)==1){

    for(g=1;g<d-1;g++){
       if((dato[g]==1)&&(band==0)){
         output_high(PIN_b1);
         output_low(PIN_b2);
         band=1;
       delay_ms(10);
       }else if((dato[g]==1)&&(band==1)){
         output_low(PIN_b1);
         output_high(PIN_b2);
       delay_ms(10);
       }else{
         output_low(PIN_b1);
         output_low(PIN_b2);
       delay_ms(10);
       }
    }
        
while(input(PIN_b5)==1){}// antirrebote
   }

}
}
