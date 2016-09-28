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

int porta_image;
int portb_image;
int portc_image;
int portd_image;
int porte_image;
int portf_image;
int portg_image;
int sw_input;
long total_chrono_count;
long chrono_data;
int display_count;
int run_mode;                    //Flag set when in run mode
int pdrst_flag;
int data_in;
long calib4_counter;
long idle4_counter;
long mrst4_counter;
int hit_imlar_image;
int hit_imlar_zero_image;
long error_count;
long error_check;
long wrtsig_counter;
long column_count1;
long column_count2;
long column_count3;
long column_count4;
long column_count5;
long column_count6;

//
// setup functions
//

void init_chrono(void);
void clear_chrono(void);
void read_chrono(void);
void count_chrono(void);
void check_inputs(void);

void ckcal_high(void);
void ckcal_low(void);
void cka_high(void);
void cka_low(void);
void ckb_high(void);
void ckb_low(void);
void ckc_high(void);
void ckc_low(void);
void pdrst_high(void);
void pdrst_low(void);
void tnin_high(void);
void tnin_low(void);
void tin_high(void);
void tin_low(void);

void set_high(void);
void set_low(void);
void rem_sel_high(void);
void rem_sel_low(void);
void radrvalid_high(void);
void radrvalid_low(void);
void rdtsth_high(void);
void rdtsth_low(void);
void rdclk_high(void);
void rdclk_low(void);
void rdparld_high(void);
void rdparld_low(void);
void hit_imlar_high(void);
void hit_imlar_low(void);
void hit_imlar_zero_high(void);
void hit_imlar_zero_low(void);

void readout(void);

void get_switch(void);
void four_digit_display(void);
void waveform_drdtst(void);
void waveform_mrst4(void);
void waveform_idle4(void);
void waveform_wrtt4(void);
void waveform_calib4(void);
void waveform_calin4(void);
void waveform_beam2(void);
void waveform_wrtsig(void);

long chrono_data_storage [600];
long chrono_data_storage_pointer;



void main()
{
    clear_chrono();
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
    
// Clear the Chronopixel by setting ports c though e to zero (but we still need to output, right?)
    clear_chrono();                     // Clear the Chronopixel
    
// set and output port c and d to 0
// these two ports seem related to setting the timestamps on the chronopixel
    portc_image = (0b00000000);            // Set a Stamp Counter
    portb_image = (0b00000000);            // Only first 4 LSB bits of portb go to Chronopixel(right side of image)
    output_c(portc_image);
    output_b(portb_image);
    
//
//
//
//
    while(TRUE)                          // Do stuff // The long while loop in which everything happens
    {
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
        output_c(portc_image);				   // output to port c
        output_b(portb_image);				   // output to port b
        clear_chrono();
        
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
        mrst4_counter = 0;
        while(mrst4_counter <5)
        {
            waveform_mrst4();
            mrst4_counter++;
        }
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
        total_chrono_count = column_count1;
        four_digit_display();
// Display the second group of columns
        putc(0x2C); //comma
        total_chrono_count = column_count2;
        four_digit_display();
// Display the third group of columns
        putc(0x2C); //comma
        total_chrono_count = column_count3;
        four_digit_display();
// Display the fourth group of columns
        putc(0x2C); //comma
        total_chrono_count = column_count4;
        four_digit_display();
// Display the fifth group of columns
        putc(0x2C); //comma
        total_chrono_count = column_count5;
        four_digit_display();
// Display the sixth group of columns
        putc(0x2C); //comma
        total_chrono_count = column_count6;
        four_digit_display();
        putc(0x0d);		// CR (carriage return) and
        putc(0x0a);   	// LF (linefeed) between pixels


    }     // End of while(TRUE)

}  // End of main


//
// Functions Start here
//


void ckcal_high()
{
    output_high(PIN_A0);
}

void ckcal_low()
{
    output_low(PIN_A0);
}


void cka_high()
{
    output_high(PIN_A1);
}

void cka_low()
{
    output_low(PIN_A1);
}

void ckb_high()
{
    output_high(PIN_A2);
}

void ckb_low()
{
    output_low(PIN_A2);
}


void ckc_high()
{
    output_high(PIN_A3);
}

void ckc_low()
{
    output_low(PIN_A3);
}


void tnin_high()
{
    output_high(PIN_A4);
}

void tnin_low()
{
    output_low(PIN_A4);
}

void tin_high()
{
    output_high(PIN_A5);
}

void tin_low()
{
    output_low(PIN_A5);
}

//
// PORT F IMAGE
//

void set_high()
{
    output_high(PIN_F0);
}

void set_low()
{
    output_low(PIN_F0);
}

void rem_sel_high()
{
    output_high(PIN_F1);
}

void rem_sel_low()
{
    output_low(PIN_F1);
}

void radrvalid_high()
{
    output_high(PIN_F2);
}

void radrvalid_low()
{
    output_low(PIN_F2);
}

void rdtsth_high()
{
    output_high(PIN_F3);
}

void rdtsth_low()
{
    output_low(PIN_F3);
}

void rdclk_high()
{
    output_high(PIN_F4);
}

void rdclk_low()
{
    output_low(PIN_F4);
}

void rdparld_high()
{
    output_high(PIN_F5);
}

void rdparld_low()
{
    output_low(PIN_F5);
}

void pdrst_high()
{
    output_high(PIN_F7);
}

void pdrst_low()
{
    output_low(PIN_F7);
}

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


void rdout()
{
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

void clear_chrono()
{
    portc_image = 0;                       // Clear Time Stamp Counter
    portb_image = 0;
    portd_image = 0;
    porte_image = 0;
    
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

void read_chrono()                        // Increments the row and column counters
{
    if(portd_image <47)                    // Row
    {
        portd_image++;
    }
    else
    {
        portd_image = 0;
        if(porte_image < 47)             // Column
        {
            porte_image++;
        }
        else
        {
            porte_image = 0;
        }
    }
    output_d(portd_image);                      //Row and Column Counter
    output_e((porte_image + hit_imlar_image + hit_imlar_zero_image));
    
}

void four_digit_display()
{
//
// Thousands
//
    display_count = 0x30;
    if (total_chrono_count >= 4000)
    {
        display_count = 0x34;
        total_chrono_count = (total_chrono_count - 4000);
    }
    if (total_chrono_count >= 3000)
    {
        display_count = 0x33;
        total_chrono_count = (total_chrono_count - 3000);
    }
    if (total_chrono_count >= 2000)
    {
        display_count = 0x32;
        total_chrono_count = (total_chrono_count - 2000);
    }
    if (total_chrono_count >= 1000)
    {
        display_count = 0x31;
        total_chrono_count = (total_chrono_count - 1000);
    }
    if (total_chrono_count < 1000)
    {
        putc(display_count);
    }
    
//
// Hundreds
//
    display_count = 0x30;
    if (total_chrono_count >= 900)
    {
        display_count = 0x39;
        total_chrono_count = (total_chrono_count - 900);
    }
    if (total_chrono_count >= 800)
    {
        display_count = 0x38;
        total_chrono_count = (total_chrono_count - 800);
    }
    if (total_chrono_count >= 700)
    {
        display_count = 0x37;
        total_chrono_count = (total_chrono_count - 700);
    }
    if (total_chrono_count >= 600)
    {
        display_count = 0x36;
        total_chrono_count = (total_chrono_count - 600);
    }
    if (total_chrono_count >= 500)
    {
        display_count = 0x35;
        total_chrono_count = (total_chrono_count - 500);
    }
    if (total_chrono_count >= 400)
    {
        display_count = 0x34;
        total_chrono_count = (total_chrono_count - 400);
    }
    if (total_chrono_count >= 300)
    {
        display_count = 0x33;
        total_chrono_count = (total_chrono_count - 300);
    }
    if (total_chrono_count >= 200)
    {
        display_count = 0x32;
        total_chrono_count = (total_chrono_count - 200);
    }
    if (total_chrono_count >= 100)
    {
        display_count = 0x31;
        total_chrono_count = (total_chrono_count - 100);
    }
    putc(display_count);
//
// Tens
//
    display_count = 0x30;
    if (total_chrono_count >= 90)
    {
        display_count = 0x39;
        total_chrono_count = (total_chrono_count - 90);
    }
    if (total_chrono_count >= 80)
    {
        display_count = 0x38;
        total_chrono_count = (total_chrono_count - 80);
    }
    if (total_chrono_count >= 70)
    {
        display_count = 0x37;
        total_chrono_count = (total_chrono_count - 70);
    }
    if (total_chrono_count >= 60)
    {
        display_count = 0x36;
        total_chrono_count = (total_chrono_count - 60);
    }
    if (total_chrono_count >= 50)
    {
        display_count = 0x35;
        total_chrono_count = (total_chrono_count - 50);
    }
    if (total_chrono_count >= 40)
    {
        display_count = 0x34;
        total_chrono_count = (total_chrono_count - 40);
    }
    if (total_chrono_count >= 30)
    {
        display_count = 0x33;
        total_chrono_count = (total_chrono_count - 30);
    }
    if (total_chrono_count >= 20)
    {
        display_count = 0x32;
        total_chrono_count = (total_chrono_count - 20);
    }
    if (total_chrono_count >= 10)
    {
        display_count = 0x31;
        total_chrono_count = (total_chrono_count - 10);
    }
    putc(display_count);
    
    total_chrono_count = (total_chrono_count + 0x30);
    putc(total_chrono_count);
    
    
}

void waveform_drdtst()                       //Read the Chronopixel
{
    chrono_data = 0;
    cka_low();
    ckb_low();
    ckc_low();
    ckcal_low();
    rem_sel_low();
    rdtsth_low();
    pdrst_high();
    
    tnin_high();
    delay_us(2);//13 6 3
    tnin_low();
    delay_us(1);//13 6 3
    tin_high();
    radrvalid_high();
    delay_us(1);//8 4 2
    rdparld_high();
    delay_us(1);//5 2
    tin_low();                 //t10
    delay_us(1);//5 2
    rdclk_high();              //t11
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 2048);
    }
    delay_us(2);//15 7 4
    rdparld_low();             //t15
    delay_us(1);//12 6 3
    rdclk_low();
    delay_us(2);//15 8 4
    rdclk_high();              //t20
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 1024);
    }
    delay_us(1);//13 6 3
    radrvalid_low();           //t22
    delay_us(1);//13 6 3
    rdclk_low();               //t24
    delay_us(1);//20 10 5
    tnin_high();               //t27
    delay_us(1);//5 2
    rdclk_high();              //t28
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 512);
    }
    
    delay_us(1);//13 6 3
    tnin_low();                //t31
    delay_us(1);//5 2
    rdclk_low();               //t32
    delay_us(1);//13 6 3
    tin_high();                //t35
    delay_us(1);//13 6 3
    rdclk_high();              //t36
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 256);
    }
    
    delay_us(1);//13 6 3
    tin_low();                 //t38
    delay_us(1);//13 6 3
    rdclk_low();               //t40
    delay_us(2);//25 12 6
    rdclk_high();              //t44
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 128);
    }
    
    delay_us(2);//25 12 6
    rdclk_low();               //t48
    delay_us(2);//25 12
    rdclk_high();              //t52
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 64);
    }
    
    delay_us(1);//20 10 5
    tnin_high();               //t55
    delay_us(1);//5 2
    rdclk_low();               //t56
    delay_us(2);//20 10
    tnin_low();                //t59
    delay_us(1);//5 2
    rdclk_high();              //t61
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 32);
    }
    
    delay_us(1);//13 6 3
    tin_high();                //t63
    delay_us(1);//8 4 2
    rdclk_low();               //t64
    delay_us(1);//8 4 2
    tin_low();                 //t65
    delay_us(1);//5 2
    rdclk_high();              //t68
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 16);
    }
    
    delay_us(2);//25 12 6
    rdclk_low();               //t72
    delay_us(2);//25 12 6
    rdclk_high();              //t76
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 8);
    }
    
    delay_us(2);//25 12 6
    rdclk_low();               //t81
    delay_us(1);//13 6 3
    tnin_high();               //t84
    delay_us(1);//13 6 3
    rdclk_high();              //t85
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 4);
    }
    
    delay_us(1);//13 6 3
    tnin_low();                //t87
    delay_us(1);//13 6 3
    rdclk_low();               //t88
    delay_us(1);//13 6 3
    tin_high();                //t91
    delay_us(1);//13 6 3
    rdclk_high();              //t93
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 2);
    }
    
    delay_us(1);//13 6 3
    tin_low();                 //t94
    delay_us(1);//13 6 3
    rdclk_low();               //t96
    delay_us(2);//25 12 6
    rdclk_high();              //t100
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 1);
    }
    
    delay_us(2);//25 12 6
    rdclk_low();               //t104
    delay_us(3);//25 12 6
    tnin_high();               //t110
    delay_us(3);//13 6
    tnin_low();                //t114
    delay_us(2);//25 12 6
    tin_high();                //t118
    delay_us(2);//25 12 6
    tin_low();                 //t122
//   delay_us(12);//25 12
    
}
//
//
//
void waveform_mrst4()            // Memory Reset Test section
{
    cka_low();
    ckb_low();
    ckc_low();
    ckcal_low();
    rdparld_low();
    rdclk_low();
    radrvalid_low();
    tnin_high();
    pdrst_high();
    set_high();
    delay_us(6);//25,12
    pdrst_low();
    delay_us(6);//25,12
    tnin_low();
    delay_us(3);//13,6
    tin_high();
    set_low();
    delay_us(6);//25,12
    tin_low();                 //t11
    delay_us(2);//5,2
    tnin_high();
    delay_us(9);//37,18
    tnin_low();
    delay_us(9);//37,18
    tin_high();
    cka_high();
    delay_us(6);//25,12
    tin_low();
    tnin_high();               //t25
    delay_us(6);//25,12
    cka_low();
    tnin_low();
    delay_us(18);//75,36
    tin_high();                //t38
    delay_us(6);//25,12
    tin_low();
//   delay_us(12);//25
}


Void waveform_idle4()
{
    cka_low();
    ckb_low();
    ckc_low();
    ckcal_low();
    rdparld_low();
    rdclk_low();
    radrvalid_low();
    pdrst_high();
    tnin_high();
    delay_us(1);//6
    pdrst_low();
    delay_us(1);//6
    tnin_low();
    delay_us(1);//2
    tin_high();
    delay_us(2);//13
    tin_low();
    delay_us(1);//2
    tnin_high();
    delay_us(2);//13
    tnin_low();
    delay_us(1);//13
    tin_high();
    delay_us(2);//13
    tin_low();
    tnin_high();
    delay_us(2);//13
    tnin_low();
    delay_us(1);//25
    tin_high();
    delay_us(2);//13
    tin_low();
    
}

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

void waveform_wrtsig()
{
    output_low(PIN_A1);           //cka low
    output_low(PIN_A2);           //ckb low
    output_low(PIN_A3);           //ckc low
    output_low(PIN_A0);           //ckcla low
    output_low(PIN_F0);           //set low
    output_low(PIN_F5);           //rdparld low
    output_low(PIN_F4);           //rdclk low
    output_low(PIN_F2);           //radrvalid low
    output_high(PIN_A4);          //tnin high
    output_high(PIN_F7);          //pdrst high
    delay_us(5);
    output_low(PIN_F7);           //pdrst low
    delay_us(6);
    output_low(PIN_A4);           //tnin low
    delay_us(1);
    output_high(PIN_A5);          //tin high
    delay_us(2);
    output_low(PIN_A5);           //tin low at t11
    delay_us(1);
    output_high(PIN_A4);          //tnin high
    delay_us(2);
    output_low(PIN_A4);           //tnin low
    delay_us(2);
    output_high(PIN_A5);          //tin high
    delay_us(2);
    output_high(PIN_A1);          //cka high at t24
    delay_us(2);
    output_low(PIN_A5);           //tin low
    output_high(PIN_A4);          //tnin high at t25
    delay_us(2);
    output_low(PIN_A1);           //cka low
    delay_us(2);
    output_low(PIN_A4);           //tnin low
    delay_us(1);
    output_high(PIN_A5);          //tin high at t38
    delay_us(2);
    output_low(PIN_A5);           //tin low
}

void waveform_calib4()
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
    delay_us(6);//6
    pdrst_low();
    delay_us(6);//6
    tnin_low();
    delay_us(2);//2
    tin_high();
    delay_us(10);//10
    ckcal_high();
    delay_us(2);//2
    tin_low();                 //t11
    delay_us(2);//2
    tnin_high();
    delay_us(8);//17,8
    tnin_low();
    ckcal_low();
    delay_us(8);//17,8
    tin_high();
    cka_high();
    ckc_high();
    delay_us(25);//25
    tin_low();
    tnin_high();               //t25
    delay_us(12);//12
    cka_low();
    ckc_low();
    tnin_low();
    delay_us(6);//12,6
    tin_high();                //t38
    delay_us(6);//12,6
    tin_low();
}

void waveform_calin4()
{
    cka_low();
    ckb_low();
    ckc_high();
    ckcal_high();
    set_low();
    rdparld_low();
    rdclk_low();
    radrvalid_low();
    tnin_high();
    pdrst_high();
    delay_us(1);
    pdrst_low();
    delay_us(1);
    tnin_low();
    delay_us(1);
    tin_high();
    delay_us(2);
    tin_low();                 //t11
    delay_us(1);
    tnin_high();
    delay_us(2);
    tnin_low();
    delay_us(1);
    tin_high();
    delay_us(2);
    tin_low();
    tnin_high();               //t25
    delay_us(2);
    tnin_low();
    delay_us(1);// was 50
    tin_high();                //t38
    delay_us(2);
    tin_low();
//   delay_us(12);
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


