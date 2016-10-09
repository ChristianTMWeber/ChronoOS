/*
 *  Latest Changes Jun 15, 2016    changed the way counts are displayed, should now work better with the serial output
 *  Latest Chenges May 12,2016             Do not increment the time stamp
 *  Latest changes April 25, 2016
 *  Latest changes March 30, 2016
 *  Latest changes January 11, 2016
 *
 *  Title:         Chronopixel4
 *  Date:          December 28, 2015
 *  Author:        Thomas Barker
 *  Description:   Chronopixel4 interacts with the Chronopixel chip
 *                 to read the time stamp if an event occured.
 *
 *
 *
 *
 *
 *                 Use PIC16F1527
 *
 * PORT A OUTPUT BITS
 *
 * 0  CKCAL
 * 1  CKA
 * 2  CKB
 * 3  CKC
 * 4  TNIN
 * 5  TIN
 * 6  OSC
 * 7  OSC
 *
 * PORT B OUTPUT BITS
 *
 * 0  TSCNT<8>
 * 1  TSCNT<9>
 * 2  TSCNT<10>
 * 3  TSCNT<11>
 * 4
 * 5
 * 6  ICSPCLK (used for programming)
 * 7  ICSPDAT (used for programming)
 *
 * PORT C OUTPUT BITS
 *
 * 0  TSCNT<0>
 * 1  TSCNT<1>
 * 2  TSCNT<2>
 * 3  TSCNT<3>
 * 4  TSCNT<4>
 * 5  TSCNT<5>
 * 6  TSCNT<6>
 * 7  TSCNT<7>
 *
 * PORT D OUTPUT BITS
 *
 * 0  RADR<0>
 * 1  RADR<1>
 * 2  RADR<2>
 * 3  RADR<3>
 * 4  RADR<4>
 * 5  RADR<5>
 * 6
 * 7
 *
 * PORT E OUTPUT BITS
 *
 * 0  ColADR<0>
 * 1  ColADR<1>
 * 2  ColADR<2>
 * 3  ColADR<3>
 * 4  ColADR<4>
 * 5  ColADR<5>
 * 6
 * 7
 *
 * PORT F INPUT/OUTPUT BITS
 *
 * 0  SET
 * 1  Rem_Sel
 * 2  RAdrValid
 * 3  RdTslh
 * 4  RdClk
 * 5  RdParLD
 * 6  RdOut
 * 7  PDRST
 *
 * PORT G INPUT/OUTPUT BITS
 *
 * 0  SWITCH 1
 * 1  TX2
 * 2  RC2
 * 3  SWITCH 2
 * 4  SWITCH 3
 * 5  Vpp/MCLR
 *
 *
 *
 *
 *
 *
 */
#include "C:\Dropbox\ChronoPixel\ChronoOS\ChronoOSHeader.h"

//
// IIC setup
//
//#define device_SDA pin_C4
//#define device_SCL pin_C3
//#use i2c(master,sda = Device_SDA,scl = Device_SCL)
//
//
//
#use delay(clock = 20000000)


//
// setup variables
//

int porta_image;    //never used!
int portb_image;
int portc_image;
int portd_image;
int porte_image;
int portf_image;    //never used!
int portg_image;
int sw_input;
long total_chrono_count;    //never used!
long chrono_data;
int run_mode;                    //Flag set when in run mode
int pdrst_flag;     //never used!
int data_in;    //never used!
long calib4_counter;
long idle4_counter;
long mrst4_counter;
int hit_imlar_image;
int hit_imlar_zero_image;
long error_count;   //never used!
long error_check;   //never used!
long wrtsig_counter;
long column_count1;
long column_count2;
long column_count3;
long column_count4;
long column_count5;
long column_count6;

long chrono_data_storage [600]; //never used!
long chrono_data_storage_pointer; //never used!

long time; // to store the timer in
long codeIterationLimit;

//
// setup functions
//

void init_chrono(void);     // ? in use at all ?
void count_chrono(void);    // ? in use at all ?
void check_inputs(void);    // ? in use at all ?
void readout(void);         // ? in use at all ?  ! has not even a definition !
void waveform_wrtt4(void);  // ? in use at all ?
void waveform_beam2(void);  // ? in use at all ?
void get_switch(void);      // ? in use at all ?  ! has not even a definition !



void hit_imlar_high(void);
void hit_imlar_low(void);
void hit_imlar_zero_high(void);
void hit_imlar_zero_low(void);

// change individual pins by calling chronopixel specific function (like pdrst_high instead of output_high(PIN_F7);)
#include "PinsToFunctions.h"


// waveform definitions and declarations
#include "wrtsig.h"
#include "mrst4.h"
#include "drdtst.h"
#include "calin4.h"
#include "calib4.h"
#include "idle4.h"

// non waveform related functions
#include "FourOrFiveDigitDisplay.h"
#include "noneWaveformFunctions.h"

void main()
{   setup_timer_1(T1_INTERNAL|T1_DIV_BY_4); // start timer1, the 16 bit timer, see refernce page 92
    // use set_timer1(0); to set the timer to 0, get_timer1(); to get the time

    time = get_timer1();

    run_mode = 0;                             // Clear the run mode flag
    
    set_tris_a(0b00000000);
    set_tris_b(0b00000000);
    set_tris_c(0b00000000);
    set_tris_d(0b00000000);
    set_tris_e(0b00000000);
    set_tris_f(0b00000100);
    set_tris_g(0b10111100);
//
//
//
    delay_ms(500);
    
    
// set and output port c and d to 0
// these two ports seem related to setting the timestamps on the chronopixel
    portc_image = (0b00000000);            // Set a Stamp Counter
    portb_image = (0b00000000);            // Only first 4 LSB bits of portb go to Chronopixel(right side of image)
    output_c(portc_image);
    output_b(portb_image);
    
//
//
codeIterationLimit = 0;
//
    while(TRUE)                          // Do stuff // The long while loop in which everything happens
    {
        if(codeIterationLimit < 200)
            {codeIterationLimit += 1;}
        else
            {codeIterationLimit = 1;}

        portg_image = input_g();                        // Get inputs from PortG
        sw_input = portg_image & (0b00010000);          // Sw1 from Pin G4
        if(sw_input !=0)
        {
        }
        while(sw_input != 0)                            // Input is high
        {
            portg_image = input_g();                        // Get inputs from PortG
            sw_input = portg_image & (0b00010000);          // Sw1 from Pin G4
            hit_imlar_zero_low();                           // Release from 0 mVolts
            hit_imlar_high();                               // Pull VTH to adjust threshold mV
        }
        
        portc_image = (0b00000000);            // Set timestamp to 0
        portb_image = (0b00000000);            // Only first 4 LSB bits of portb go to Chronopixel(right side of image)
        output_c(portc_image);               // output to port c
        output_b(portb_image);               // output to port b
        
        idle4_counter = 0;
        while(idle4_counter <5)
        {
            waveform_idle4();
            idle4_counter++;
        }
        
//   hit_imlar_zero_low();                  // Release from 0 mVolts
//   hit_imlar_high();                      // Pull VTH to 30 mV
//    changed on 8/31/2016
        hit_imlar_zero_high();                  // Release from 0 mVolts
        hit_imlar_low();                      // Pull VTH to 30 mV
        
        waveform_calin4();
        
        // calibrate repeatedly
        calib4_counter = 0;
        while(calib4_counter <100)
        {
            waveform_calib4();
            calib4_counter++;
        }
        
        hit_imlar_zero_low();                  // Release VTH short
        hit_imlar_low();                       // VTH to 250 mV
        // reset the memory by writing the output c (and maybe b too) to the chronopixel
        
        set_timer1(0); // reset the timer to 0
        mrst4_counter = 0;
        while(mrst4_counter <codeIterationLimit)
        {
            waveform_mrst4();
            mrst4_counter++;
        }
        time = get_timer1(); // save the timer

        hit_imlar_high();                      // Pull VTH to 30 mV
        hit_imlar_zero_high();                 // Pull VTH to 0mV
        
//
///*
        // set the timestamp to 1 and send it to the chronopixel
        portc_image = (0b00000001);            // Set a Stamp Counter
        portb_image = (0b00000000);            // Only first 4 LSB bits of portb go to Chronopixel(right side of image)
        output_c(portc_image);
        output_b(portb_image);
///*

        wrtsig_counter = 0;
        while(wrtsig_counter < 4095)        //Time Stamp 4095
        {
            waveform_wrtsig(); // record particle incidents on the chronopixel
            wrtsig_counter++;
/*
            //increment the timestamp to write to the chronopixel
            if(portc_image <255) //port c seems to be responsible for the 8 least significant bits
            { portc_image ++;}               // Increment Time Stamp Counter
            else
            {   portc_image = 0;
                portb_image ++; // and port b for the remaining 4 (most) significant bits
            }
           output_c(portc_image); //output the incremented timestamp to the chronopixel
           output_b(portb_image);
*/
        }
     
        portc_image = 0;                 // Clear time stamp
        portb_image = 0;
        output_c(portc_image);
        output_b(portb_image);
        
        
//
// Write to memory
//
        portd_image = 0;
        porte_image = 0;
        rem_sel_low();
        column_count1 = 0;
        column_count2 = 0;
        column_count3 = 0;
        column_count4 = 0;
        column_count5 = 0;
        column_count6 = 0;
        wrtsig_counter = 0;
        while(wrtsig_counter <384)         // First eight columns. Number of total pixels is 2304
        {
            waveform_drdtst();                     // Read the timestamp from the pixel
            read_chrono();                         // Increment the rows and columns
            
            if(chrono_data != 0)
            {
                column_count1++;
            }
            wrtsig_counter++;
            
        }
//
//
//
        while(wrtsig_counter <768)         // Second eight columns. Number of total pixels is 2304
        {
            waveform_drdtst();                     // Read the timestamp from the pixel
            read_chrono();                         // Increment the rows and columns
            
            if(chrono_data != 0)
            {
                column_count2++;
            }
            wrtsig_counter++;
            
        }
//
//
//
        while(wrtsig_counter <1152)         // Third eight columns. Number of total pixels is 2304
        {
            waveform_drdtst();                     // Read the timestamp from the pixel
            read_chrono();                         // Increment the rows and columns
            
            if(chrono_data != 0)
            {
                column_count3++;
            }
            wrtsig_counter++;
            
        }
//
//
//
        while(wrtsig_counter <1536)         // Forth eight columns. Number of total pixels is 2304
        {
            waveform_drdtst();                     // Read the timestamp from the pixel
            read_chrono();                         // Increment the rows and columns
            
            if(chrono_data != 0)
            {
                column_count4++;
            }
            wrtsig_counter++;
            
        }
        
//
//
//
        while(wrtsig_counter <1920)         // Fifth eight columns. Number of total pixels is 2304
        {
            waveform_drdtst();                     // Read the timestamp from the pixel
            read_chrono();                         // Increment the rows and columns
            
            if(chrono_data != 0)
            {
                column_count5++;
            }
            wrtsig_counter++;
            
        }
//
//
//
        while(wrtsig_counter <2304)         // Sixth(last) eight columns. Number of total pixels is 2304
        {
            waveform_drdtst();                     // Read the timestamp from the pixel
            read_chrono();                         // Increment the rows and columns
            
            if(chrono_data != 0)
            {
                column_count6++;
            }
            wrtsig_counter++;
            
        }
        
// Display the first group of columns
        fourOrFive_digit_display(column_count1);
// Display the second group of columns
        putc(0x2C); //comma
        fourOrFive_digit_display(column_count2);
// Display the third group of columns
        putc(0x2C); //comma
        fourOrFive_digit_display(column_count3);
// Display the fourth group of columns
        putc(0x2C); //comma
        fourOrFive_digit_display(column_count4);
// Display the fifth group of columns
        putc(0x2C); //comma
        fourOrFive_digit_display(column_count5);
// Display the sixth group of columns
        putc(0x2C); //comma
        fourOrFive_digit_display(column_count6);
// Display the timer
        putc(0x2C); //comma
        fourOrFive_digit_display(time);
// Display the number of code iterations
        putc(0x2C); //comma
        fourOrFive_digit_display(codeIterationLimit);
        putc(0x0d);      // CR (carriage return) and
        putc(0x0a);      // LF (linefeed) between pixels
    }     // End of while(TRUE)

}  // End of main


//
// Functions Start here
//


void hit_imlar_high()
{
    hit_imlar_image = 64;
    output_high(PIN_E6);
}

void hit_imlar_low()
{
    hit_imlar_image = 0;
    output_low(PIN_E6);
}
void hit_imlar_zero_high()
{
    hit_imlar_zero_image = 128;
    output_high(PIN_E7);
    
}
void hit_imlar_zero_low()
{
    hit_imlar_zero_image = 0;
    output_low(PIN_E7);
}




//
//
//

void check_inputs()
{
    portg_image = input_g();                       // Get input 2
    
    sw_input = portg_image & (0b00010000); // G4
    if(sw_input == 0)                // Check Switch One
    {
    }
    sw_input = portg_image & (0b00001000); //G3
    if(sw_input == 0)                // Check Switch Two
    {
    }
    sw_input = portg_image & (0b00000001); //G0
    if(sw_input == 0)                // Check Switch Three
    {
    }
    
}
void init_chrono()
{
    portc_image = 0;                       // Clear Time Stamp Counter
    portb_image = 0;
    portd_image = 0;
    porte_image = 0;
    
    cka_low();
    ckb_low();
    ckc_low();
    ckcal_low();
    tin_low();
    tnin_low();
    set_low();
    rdparld_low();
    
    
}


void count_chrono()                       // Increments the time stamp
{
    if(portc_image <255)
    {
        portc_image++;
    }
    else
    {
        portc_image = 0;
        if(portb_image < 15)
        {
            portb_image++;
        }
        else
        {
            portb_image = 0;
            portc_image = 0;
        }
    }
//
//Write Time Stamp Counter
//
    output_c(portc_image);
    output_b(portb_image);
}






//
//
//


void waveform_wrtt4()
{
    cka_low();
    ckb_low();
    ckc_low();
    ckcal_low();
    set_low();
    rdparld_low();
    rdclk_low();
    radrvalid_low();
    tnin_high();
    pdrst_high();
    delay_us(3);//6
    pdrst_low();
    delay_us(3);//6
    tnin_low();
    delay_us(1);//2
    tin_high();
    delay_us(6);//13
    tin_low();                 //t11
    delay_us(1);//2
    tnin_high();
    delay_us(8);//17
    tnin_low();
    delay_us(8);//17
    tin_high();
    cka_high();
    delay_us(6);//13
    tin_low();
    tnin_high();               //t25
    delay_us(6);//13
    cka_low();
    tnin_low();
    delay_us(12);//25
    tin_high();                //t38
    delay_us(6);//13
    tin_low();
    delay_us(6);//13
}



void waveform_beam2()
{
    cka_low();
    ckb_low();
    ckc_low();
    ckcal_low();
    set_low();
    rdparld_low();
    rdclk_low();
    radrvalid_low();
    tnin_high();
    delay_us(2);
    pdrst_high();
    delay_us(5);
    tnin_low();
    delay_us(5);
    tin_high();
    delay_us(2);
    pdrst_low();
    delay_us(10);
    tin_low();                 //t10
    delay_us(10);
    tnin_high();
    delay_us(12);
    tnin_low();
    delay_us(12);
    tin_high();
    delay_us(12);
    tin_low();               //t25
    delay_us(5);
    tnin_high();
    delay_us(12);
    tnin_low();
    delay_us(17);
    cka_high();
    tin_high();
    delay_us(10);
    tin_low();                //t38
    tnin_high();
    delay_us(12);
    tnin_low();
    cka_low();
    delay_us(17);
    tin_high();
    delay_us(12);
    tin_low();
    delay_us(12);
}
//*/


