#include <16F1527.h>
#device adc=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT_SW                   //No Watch Dog Timer, enabled in Software
#FUSES NOBROWNOUT               //No brownout reset
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
//#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCLKOUT
#FUSES NOWRT


#use delay(clock=20000000)//#use delay(clock=25000000)
#use rs232(baud=115200,parity=N,xmit=PIN_G1,rcv=PIN_G2,bits=8)

