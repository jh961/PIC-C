///////////////////////////////////////////////////////////////////////////
////                     KBD_LIB.C by Redraven                         ////
////                                                                   ////
////                     Derived from KBDD.C                           ////
////                  Generic keypad scan driver                       ////
////                                                                   ////
////  kbd_init()   Must be called before any other function.           ////
////                                                                   ////
////  c = kbd_getc(c)  Will return a key value if pressed or /0 if not ////
////                   This function should be called frequently so as ////
////                   not to miss a key press.                        ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,1997 Custom Computer Services            ////
//// This source code may only be used by licensed users of the CCS C   ////
//// compiler.  This source code may only be distributed to other       ////
//// licensed users of the CCS C compiler.  No other use, reproduction  ////
//// or distribution is permitted without written permission.           ////
//// Derivative programs created using this software in object code     ////
//// form are not restricted in any way.                                ////
////////////////////////////////////////////////////////////////////////////

////////////////// The following defines the keypad layout on port D

// Un-comment the following define to use port B
#define use_portb_kbd TRUE

// Make sure the port used has pull-up resistors (or the LCD) on
// the column pins


#if defined(__PCH__)
#if defined use_portb_kbd
   #byte kbd = 0xF81              // This puts the entire structure
#else
   #byte kbd = 0xF83              // This puts the entire structure
#endif
#else
#if defined use_portb_kbd
   #byte kbd = 6                  // on to port B (at address 6)
#else
   #byte kbd = 8                  // on to port D (at address 8)
#endif
#endif

#if defined use_portb_kbd
   #define set_tris_kbd(x) set_tris_b(x)
#else
   #define set_tris_kbd(x) set_tris_d(x)
#endif

//Keypad connection:   (for example column 0 is B0)

#define COL0 (1 << 0) // PIN_B0
#define COL1 (1 << 1) // PIN_B1
#define COL2 (1 << 2) // PIN_B2
#define COL3 (1 << 3) // PIN_B3

#define ROW0 (1 << 4) // PIN_B4
#define ROW1 (1 << 5) // PIN_B5
#define ROW2 (1 << 6) // PIN_B6
#define ROW3 (1 << 7) // PIN_B7

#define ALL_ROWS (ROW0|ROW1|ROW2|ROW3)
#define ALL_PINS (ALL_ROWS|COL0|COL1|COL2|COL3)

// Keypad layout:
char const KEYS[4][4] = {{'1','2','3','A'},
                         {'4','5','6','B'},
                         {'7','8','9','C'},
                         {'*','0','#','D'}};

#define KBD_DEBOUNCE_FACTOR 33    // Set this number to apx n/333 where
                                  // n is the number of times you expect
                                  // to call kbd_getc each second

void kbd_init() {
}

char kbd_getc( ) {
   static byte kbd_call_count;
   static short int kbd_down;
   static char last_key;
   static byte col;

   byte kchar;
   byte row;

   kchar='\0';
   if(++kbd_call_count>KBD_DEBOUNCE_FACTOR) {
       switch (col) {
         case 0   : set_tris_kbd(ALL_PINS&~COL0);
                    kbd=~COL0&ALL_PINS;
                    break;
         case 1   : set_tris_kbd(ALL_PINS&~COL1);
                    kbd=~COL1&ALL_PINS;
                    break;
         case 2   : set_tris_kbd(ALL_PINS&~COL2);
                    kbd=~COL2&ALL_PINS;
                    break;
         case 3   : set_tris_kbd(ALL_PINS&~COL3);
                    kbd=~COL3&ALL_PINS;
                    break;
       }

       if(kbd_down) {
         if((kbd & (ALL_ROWS))==(ALL_ROWS)) {
           kbd_down=false;
           kchar=last_key;
           last_key='\0';
         }
       } else {
          if((kbd & (ALL_ROWS))!=(ALL_ROWS)) {
             if((kbd & ROW0)==0)
               row=0;
             else if((kbd & ROW1)==0)
               row=1;
             else if((kbd & ROW2)==0)
               row=2;
             else if((kbd & ROW3)==0)
               row=3;
             last_key =KEYS[row][col];
             kbd_down = true;
          } else {
             ++col;
             if(col==4)
               col=0;
          }
       }
      kbd_call_count=0;
   }
  set_tris_kbd(ALL_PINS);
  return(kchar);
}