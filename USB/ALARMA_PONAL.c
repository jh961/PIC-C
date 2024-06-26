
//////////////////////////////////////////////////
#include <18F4550.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN
#use delay(clock=48000000)


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// CCS Library dynamic defines. For dynamic configuration of the CCS Library
// for your application several defines need to be made. See the comments
// at usb.h for more information
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#define USB_HID_DEVICE FALSE // deshabilitamos el uso de las directivas HID
#define USB_EP1_TX_ENABLE USB_ENABLE_BULK // turn on EP1(EndPoint1) for IN bulk/interrupt transfers
#define USB_EP1_RX_ENABLE USB_ENABLE_BULK // turn on EP1(EndPoint1) for OUT bulk/interrupt transfers
#define USB_EP1_TX_SIZE 32 // size to allocate for the tx endpoint 1 buffer
#define USB_EP1_RX_SIZE 32 // size to allocate for the rx endpoint 1 buffer

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Include the CCS USB Libraries. See the comments at the top of these
// files for more information
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <pic18_usb.h> // Microchip PIC18Fxx5x Hardware layer for CCS's PIC USB driver
#include "header.h" // Configuración del USB y los descriptores para este dispositivo
#include <usb.c> // handles usb setup tokens and get descriptor reports
//#use rs232(baud=234400, xmit=PIN_B0,rcv=PIN_B7, stream = zigbee)

#define Enciende Output_High
#define Apaga Output_Low
#define Conmuta Output_Toggle
#define RecCommand recbuf[0]
#define Largo recbuf[1]
#define COMMAND_FIRMWARE 99
#define COMMAND_BORRADO 88
#define COMMAND_DATOS 60
#define COMMAND_DATOS1 10
#define COMMAND_DATOS2 20
#define COMMAND_DATOS3 30
#define COMMAND_DATOS4 40
#define COMMAND_DATOS5 50
const int8 Lenbuf = 32;

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// RAM, RAM, RAM
//
///////////////////////////////////////////////////////////////////////////////////////////////////
char Version[] = "HOLA MUNDO";
char z;
int8 recbuf[Lenbuf];
int8 sndbuf[Lenbuf];
int  p, posmem, x, i;
//void almacenamiento();
//void transmitir();
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// M A I N
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void main(void) {
set_tris_a(0x00);
  //delay_ms(500);
  usb_init();
  usb_task();
  usb_wait_for_enumeration();
  enable_interrupts(global);
  while (TRUE){
       
   
  

    if(usb_enumerated()){
      if (usb_kbhit(1)){
        usb_get_packet(1, recbuf, Lenbuf);
        if(RecCommand==COMMAND_FIRMWARE){
          usb_put_packet(1,Version,10,USB_DTS_TOGGLE);
        }
        else if(RecCommand==COMMAND_DATOS){
               p=0;
               for (i=2; i<largo;i++){
                  
                     write_eeprom(p,recbuf[i]);
                     delay_us(10);
                     p++;
               
               }
        
        }else if(RecCommand==COMMAND_DATOS1){
        usb_put_packet(1,Version,4,USB_DTS_TOGGLE);
        output_high(pin_a0);
        delay_ms(100);
        output_low(pin_a0);
        }
        else if(RecCommand==COMMAND_DATOS2){
        usb_put_packet(1,Version,10,USB_DTS_TOGGLE);
        output_high(pin_a0);
        delay_ms(200);
        output_low(pin_a0);
        }
        else if(RecCommand==COMMAND_DATOS3){
        usb_put_packet(1,Version,3,USB_DTS_TOGGLE);
        output_high(pin_a0);
        delay_ms(300);
        output_low(pin_a0);
        }
        else if(RecCommand==COMMAND_DATOS4){
        usb_put_packet(1,Version,9,USB_DTS_TOGGLE);
        output_high(pin_a0);
        delay_ms(400);
        output_low(pin_a0);
        }
        else if(RecCommand==COMMAND_DATOS5){
        usb_put_packet(1,Version,7,USB_DTS_TOGGLE);
        output_high(pin_a0);
        delay_ms(500);
        output_low(pin_a0);
        }
        else if(RecCommand==COMMAND_BORRADO){
        
        }
      }
    }
   //-------------------------------



  }
}


