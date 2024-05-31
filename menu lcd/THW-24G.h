//////////////////////////////////////////////////////////////////////////////// 
//                        Laipac RF-24G / TXRX24G 
//                   2.4GHz Wireless Transceiver Driver 
// 
// Original by micro222@yahoo.com 
// 
// Filename     : RF-24G_6-byte.c 
// Programmer   : Steven Cholewiak, www.semifluid.com 
// Version      : Version 1.01 - 01/30/2006 
// Remarks      : Datasheets for RF-24G / TXRX24G are available from: 
//                http://www.sparkfun.com/datasheets/RF/RF-24G_datasheet.pdf 
//                http://www.sparkfun.com/datasheets/RF/RF-24G.pdf 
//                http://www.sparkfun.com/datasheets/RF/nRF2401rev1_1.pdf 
//                http://store.qkits.com/moreinfo.cfm/txrx24g.pdf 
// 
//                This code is modified from the original to support more 
//                configuration options with more information provided about 
//                each configuration byte. 
// 
// History      : Version 1.01 - 01/30/2006 
//                - numOfBytes is now used to describe the packet payload and 
//                  adjusts DATA1_W, DATA2_W, and BUF_MAX accordingly 
// 
//                Version 1.00 - 01/21/2006 
//                - Initial release 
//////////////////////////////////////////////////////////////////////////////// 

//////////////////////////////////////////////////////////////////////////////// 
//Pin Configuration 
// 
//    Pin   Name  Pin funtion Description 
//    1     GND   Power       Gound (0V) 
//    2     CE    Input       Chip Enable activates RX or TX mode 
//    3     CLK2  I/O         Clock output/input for RX data channel 2 
//    4     CS    Input       Chip Select activates Configuration mode 
//    5     CLK1  I/O         Clock Input(TX)&I/O(RX) for data channel 1 3-wire interface 
//    6     DATA  I/O         RX data channel 1/TX data input /3-wire interface 
//    7     DR1   Output      RX data ready at data channel 1 (ShockBurst only) 
//    8     DOUT2 Output      RX data channel 2 
//    9     DR2   Output      RX data ready at data channel 2 (ShockBurst only) 
//    10    VCC   Power       Power Supply (+3V DC) 

#define RF_24G_CE       PIN_B3 
#define RF_24G_DATA       PIN_B4 
#define RF_24G_CLK1     PIN_B5 
//#define RF_24G_CLK2     PIN_B0 
#define RF_24G_DR1       PIN_B6 
#define RF_24G_CS       PIN_B7 
//#define RF_24G_DOUT2      PIN_B4 
//#define RF_24G_DR2       PIN_B7 
//////////////////////////////////////////////////////////////////////////////// 

#define numOfBytes      6 

#inline 
RF_24G_initPorts() { 
   PORT_B_PULLUPS(FALSE); 
   DISABLE_INTERRUPTS(INT_RB); 
} 

//////////////////////////////////////////////////////////////////////////////// 
//Configuration Bytes 
// 
//Bytes 14-02: Shockburst Configuration 
//Bytes 01-00: General Device Configuration 

//Byte 14: Length of data payload section RX channel 2 in bits 
//    The total number of bits in a ShockBurst RF package may not exceed 256! 
//    Maximum length of payload section is hence given by: 
//    DATAx_W(bits) = 256 - ADDR_W - CRC 
#define DATA2_W            numOfBytes * 8 

//Byte 13: Length of data payload section RX channel 1 in bits 
#define DATA1_W            numOfBytes * 8 

//Byte 12-08: Channel 2 Address 
#define ADDR2_4            0x00 
#define ADDR2_3            0x00 
#define ADDR2_2            0x00 
#define ADDR2_1            0x42 
#define ADDR2_0            0x42 

//Byte 07-03: Channel 1 Address 
#define ADDR1_4            0x00 
#define ADDR1_3            0x00 
#define ADDR1_2            0x00 
#define ADDR1_1            0x42 
#define ADDR1_0            0x42 

//Byte 02 
//    Bit 07-02: ADDR_W    - Number of address bits (both RX channels) 
//                           Maximum number of address bits is 40 (5 bytes) 
//    Bit    01: CRC_L     - 8 or 16 bits CRC 
//    Bit    00: CRC_EN    - Enable on-chip CRC generation/checking 
//    Combine (via |) together constants from each group 
//                         0b76543210 
#define ADDR_W_5_BYTE      0b10100000 
#define ADDR_W_4_BYTE      0b10000000 
#define ADDR_W_3_BYTE      0b01100000 
#define ADDR_W_2_BYTE      0b01000000 
#define ADDR_W_1_BYTE      0b00100000 

#define CRC_L_8_BIT        0b00000000 
#define CRC_L_16_BIT       0b00000010 

#define CRC_EN_DISABLE     0b00000000 
#define CRC_EN_ENABLE      0b00000001 

//Byte 01 
//    Bit    07: RX2_EN    - Enable two channel receive mode 
//    Bit    06: CM        - Communication mode ( Direct or ShockBurst) 
//    Bit    05: RFDR_SB   - RF data rate (1Mbps requires 16MHz crystal) 
//    Bit 04-02: XO_F      - Crystal frequency (Factory default 16MHz crystal mounted) 
//    Bit 01-00: RF_PWR    - RF output power 
//    Combine (via |) together constants from each group 
//                         0b76543210 
#define RX2_EN_DISABLE     0b00000000 
#define RX2_EN_ENABLE      0b10000000 

#define CM_DIRECT          0b00000000 
#define CM_SHOCKBURST      0b01000000 

#define RFDR_SB_250_KBPS   0b00000000 
#define RFDR_SB_1_MBPS     0b00100000 

#define XO_F_4MHZ          0b00000000 
#define XO_F_8MHZ          0b00000100 
#define XO_F_12MHZ         0b00001100 
#define XO_F_16MHZ         0b00001100 
#define XO_F_20MHZ         0b00010000 

#define RF_PWR_N20DB       0b00000000  // -20db 
#define RF_PWR_N10DB       0b00000001  // -10db 
#define RF_PWR_N5DB        0b00000010  // -5db 
#define RF_PWR_0DB         0b00000011  // 0db (Full Power) 

//Byte 01 
//    Bit 07-01: RF_CH#    - Frequency channel (2400MHz + RF_CH# * 1.0MHz) 
//    Bit    00: RXEN      - RX or TX operation 
//    Combine (via |) together constants from each group 
//                         0b76543210 
#define RF_CH              0b10000000 // 64 - 2464GHz 

#define RXEN_TX            0b00000000 
#define RXEN_RX            0b00000001 
//////////////////////////////////////////////////////////////////////////////// 

#define BUF_MAX            numOfBytes 
byte buf[BUF_MAX]; 
#define CLKDELAY()         delay_us(1) 
#define CSDELAY()          delay_us(10) 
#define PWUPDELAY()        delay_ms(3) 

void putByte( byte b ) {  //MSB bit first 
   int8 i; 
   int8 p = 7; 
   for(i=0 ; i < 8 ; i++) { 
      OUTPUT_LOW(RF_24G_CLK1); 
      if( BIT_TEST(b,p--) ) { 
         OUTPUT_HIGH(RF_24G_DATA); 
      }else{ 
         OUTPUT_LOW(RF_24G_DATA); 
      } 
      CLK DELAY(); 
      OUTPUT_HIGH(RF_24G_CLK1);  // Clock out on rising edge 
      CLK DELAY(); 
   } 
} 

byte getByte() {  //MSB bit first 
   int8 i , b = 0; 
   int8 p = 7; 
   for(i=0 ; i < 8 ; i++) { 
      OUTPUT_LOW(RF_24G_CLK1); 
      CLK DELAY(); 
      OUTPUT_HIGH(RF_24G_CLK1); 
      CLKDELAY();           // Read before falling edge 
      if( INPUT(RF_24G_DATA) ) { 
         BIT_SET(b,p--); 
      }else{ 
         BIT_CLEAR(b,p--); 
      } 
   } 
   return b; 
} 

void RF_24G_Config() { 
   OUTPUT_LOW(RF_24G_CE); 
   OUTPUT_LOW(RF_24G_CS); 
   OUTPUT_LOW(RF_24G_CLK1); 
   OUTPUT_LOW(RF_24G_DATA); 
   PWUPDELAY(); 
   OUTPUT_HIGH(RF_24G_CS); 
   CSDELAY(); 

   //MSB byte first 
   putByte(DATA2_W); 
   putByte(DATA1_W); 
   putByte(ADDR2_4); 
   putByte(ADDR2_3); 
   putByte(ADDR2_2); 
   putByte(ADDR2_1); 
   putByte(ADDR2_0); 
   putByte(ADDR1_4); 
   putByte(ADDR1_3); 
   putByte(ADDR1_2); 
   putByte(ADDR1_1); 
   putByte(ADDR1_0); 
   putByte(ADDR_W_2_BYTE | CRC_L_16_BIT | CRC_EN_ENABLE); 
   putByte(RX2_EN_DISABLE | CM_SHOCKBURST | RFDR_SB_1_MBPS | XO_F_16MHZ | RF_PWR_0DB); 
   putByte(RF_CH | RXEN_RX); 

   OUTPUT_FLOAT(RF_24G_DATA); 
   OUTPUT_LOW(RF_24G_CE); 
   OUTPUT_LOW(RF_24G_CS); 
   OUTPUT_LOW(RF_24G_CLK1); 
} 

void RF_24G_SetTxByte() { 
   OUTPUT_LOW(RF_24G_CE); 
   OUTPUT_HIGH(RF_24G_CS); 
   CSDELAY(); 
   putByte(RF_CH | RXEN_TX); 
   OUTPUT_LOW(RF_24G_CS); 
   OUTPUT_LOW(RF_24G_CLK1); 
} 

void RF_24G_SetTx() { 
   // Once the wanted protocol, modus and RF channel are set, 
   // only one bit (RXEN) is shifted in to switch between RX and TX. 
   OUTPUT_LOW(RF_24G_CE); 
   OUTPUT_HIGH(RF_24G_CS); 
   CSDELAY(); 
   OUTPUT_LOW(RF_24G_DATA); 
   OUTPUT_HIGH(RF_24G_CLK1); 
   CLKDELAY(); 
   OUTPUT_LOW(RF_24G_CLK1); 
   CLKDELAY(); 
   OUTPUT_LOW(RF_24G_CS); 
   OUTPUT_LOW(RF_24G_CLK1); 
} 

void RF_24G_SetRxByte() { 
   OUTPUT_LOW(RF_24G_CE); 
   OUTPUT_HIGH(RF_24G_CS); 
   CSDELAY(); 
   putByte(RF_CH | RXEN_RX); 
   OUTPUT_LOW(RF_24G_CS); 
   OUTPUT_FLOAT(RF_24G_DATA); 
   OUTPUT_LOW(RF_24G_CLK1); 
   OUTPUT_HIGH(RF_24G_CE); 
} 

void RF_24G_SetRx() { 
   // Once the wanted protocol, modus and RF channel are set, 
   // only one bit (RXEN) is shifted in to switch between RX and TX. 
   OUTPUT_LOW(RF_24G_CE); 
   OUTPUT_HIGH(RF_24G_CS); 
   CSDELAY(); 
   OUTPUT_HIGH(RF_24G_DATA); 
   OUTPUT_HIGH(RF_24G_CLK1); 
   CLKDELAY(); 
   OUTPUT_LOW(RF_24G_CLK1); 
   CLKDELAY(); 
   OUTPUT_LOW(RF_24G_CS); 
   OUTPUT_FLOAT(RF_24G_DATA); 
   OUTPUT_LOW(RF_24G_CLK1); 
   OUTPUT_HIGH(RF_24G_CE); 
} 

void putBuffer() { 
   int8 i; 
   OUTPUT_HIGH(RF_24G_CE); 
   CSDELAY(); 

   putByte(ADDR1_1); 
   putByte(ADDR1_0); 

   for( i=0; i<BUF_MAX ; i++) { 
      putByte(buf[i]); 
   } 
   OUTPUT_LOW(RF_24G_CE); 
   OUTPUT_LOW(RF_24G_CLK1); 
} 

void getBuffer() { 
   int8 i; 
   for( i=0; i<BUF_MAX ; i++) { 
       buf[i] = getByte(); 
   } 
   OUTPUT_LOW(RF_24G_CLK1); 
   OUTPUT_HIGH(RF_24G_CE); 
} 

//////////////////////////////////////////////////////////////////////////////// 
//Example Setup: 
// 
//    RF_24G_initPorts(); 
//    RF_24G_Config(); 
//    RF_24G_SetRx();    // Switch to receive 
//    buf[0] = 'A'; 
//    buf[1] = 'B';  // Not used 
//    buf[2] = 'C';  // Not used 
//    buf[3] = 'D';  // Not used 
// 
//    while(1) { 
//       if(INPUT(RF_24G_DR1)){ 
//          getBuffer();   // Get packet 
//          putc(buf[0]); 
//       } 
// 
// 
//       // Transmit RF 
//       RF_24G_SetTx();     // switch to transmit 
//       delay_ms(1); 
//       putBuffer();      // send packet (buf) 
//       delay_ms(1);      // won't go back to recieve without this 
//       RF_24G_SetRx();     // switch back to receive 
//       delay_ms(1); 
//    } 
