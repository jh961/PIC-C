#include <18f4550.h> 
#device adc=10    
#fuses hs,nowdt,nobrownout,put 
#use delay(clock=20000000) 
#include <KBD.c>
#include <lcd.c>

#define  LOAD  PIN_B7 
#define  THRES 30.0     

int16 digital_reading;  
float temp,tempc; 
int num1,num2,numf;

void main() 
{    
   
   char k,p,car,car1,numero;
   //int a,b,c,d;
   set_tris_e(0x00);
   lcd_init(); // inicializar la libreria de trabajo para este caso lcd
   kbd_init();
   port_b_pullups(TRUE);

   /* ADC Initialization */ 
   setup_adc(ADC_CLOCK_INTERNAL); 
   setup_adc_ports(AN0);   
   set_adc_channel(0);            
   delay_us(100);                    
    
   /* Configuracion de perifericos */ 
   lcd_init();                   
   lcd_gotoxy(1,1);              
   lcd_putc("\fsensor de ");  
   lcd_gotoxy(1,2);              
   lcd_putc("temperatura ");  
   delay_ms(500);
   lcd_gotoxy(1,1);              
   lcd_putc("\fpresentador por: ");  
   delay_ms(500);
   lcd_gotoxy(1,1);              
   lcd_putc("\fJerson Daza, ");  
   lcd_gotoxy(1,2);             
   lcd_putc("Cristian Cortes ");  
   delay_ms(500);
   lcd_putc("\f");
   
    lcd_gotoxy(1,1);              
   lcd_putc("\f1.inicar ");  
   lcd_gotoxy(1,2);              
   lcd_putc("2.configurar "); 
   k=0;
   
   while(true)  
   {  
      
      while(k==0){
      k=kbd_getc();
      }
         if(k==0){}
      
          else if(k=='1') //iniciar
          {
      
            while (k=='1'){            
            digital_reading = read_adc();    
            delay_ms(1);                   
            temp = digital_reading * 0.4883; 
            lcd_gotoxy(1,1); 
            printf(lcd_putc,"\f %2.1f gradosC",temp);
            lcd_gotoxy(1,2);              
            lcd_putc("#.Atras ");
      
            if(temp>num1){
                  output_high(pin_e0);              
                  output_low(pin_e1);  
            }
            else{
                  output_high(pin_e1);
                  output_low(pin_e0);  
            }    
              
            k=kbd_getc();
            if (k=='#'){break;} 
            else{
            k='1';
            }
           }
      }  
      
      else if(k=='2') // configuracion
      {  
         lcd_gotoxy(1,1);
         lcd_putc("\fDigite temperatura maxima ");
         lcd_gotoxy(1,2);
         lcd_putc("#.atras ");
         delay_ms(500);
         lcd_gotoxy(1,1);
         lcd_putc("\f#.atras ");
      
            while (k=='2'){      
             p=0;
            
             while(p==0)
             {
             p=kbd_getc();
             }
           /* if(p==0){}
            else if(p=='1'){} //lcd_putc(p);
            else if(p=='2'){}
            else if(p=='3'){}
            else if(p=='4'){}
            else if(p=='5'){}
            else if(p=='6'){}
            else if(p=='7'){}
            else if(p=='8'){}
            else if(p=='9'){}
            else if(p=='0'){} 
            */
             numero=numero+p;  
             lcd_putc(numero);
              num1=(int)numero;
            if(p=='#'){ 
               k='#';
               break;
               } 
            }
            /*
      car=lcd_getc(9,1);
      car1=lcd_getc(10,1);
      num1=(int)car;
      num2=(int)car1;
      numf=(num1*10)+num2;
      lcd_putc("\f");
      lcd_putc(numf);
      
     
      
      delay_ms(1000);
      */
      }
      
      else if(k=='#')
      {
      
         while (k=='#'){
         lcd_gotoxy(1,1);
         lcd_putc("\f1.iniciar");
         lcd_gotoxy(1,2);
         lcd_putc("2.configurar ");
         k=kbd_getc();
         }
      }
       
       
} //while (true)
}//void main
