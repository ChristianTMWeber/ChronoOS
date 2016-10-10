int display_count;
void fourOrFive_digit_display(long serialOutInteger); 

// sends the argument integer to the serial port
// capable of sending a 16 bit unsigned integer
// transmits four of five digits, depending on whether the 10^4 digit is 0 or not

void twoDigitDisplay(int serialOutInteger)// sends the argument integer to the serial port
{

// Tens
//
    display_count = 0x30;
    if (serialOutInteger >= 90)
    {
        display_count = 0x39;
        serialOutInteger = (serialOutInteger - 90);
    }
    if (serialOutInteger >= 80)
    {
        display_count = 0x38;
        serialOutInteger = (serialOutInteger - 80);
    }
    if (serialOutInteger >= 70)
    {
        display_count = 0x37;
        serialOutInteger = (serialOutInteger - 70);
    }
    if (serialOutInteger >= 60)
    {
        display_count = 0x36;
        serialOutInteger = (serialOutInteger - 60);
    }
    if (serialOutInteger >= 50)
    {
        display_count = 0x35;
        serialOutInteger = (serialOutInteger - 50);
    }
    if (serialOutInteger >= 40)
    {
        display_count = 0x34;
        serialOutInteger = (serialOutInteger - 40);
    }
    if (serialOutInteger >= 30)
    {
        display_count = 0x33;
        serialOutInteger = (serialOutInteger - 30);
    }
    if (serialOutInteger >= 20)
    {
        display_count = 0x32;
        serialOutInteger = (serialOutInteger - 20);
    }
    if (serialOutInteger >= 10)
    {
        display_count = 0x31;
        serialOutInteger = (serialOutInteger - 10);
    }
    putc(display_count);
    
    serialOutInteger = (serialOutInteger + 0x30);
    putc(serialOutInteger);
    
    
}