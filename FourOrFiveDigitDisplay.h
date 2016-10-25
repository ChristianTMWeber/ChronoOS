
void fourOrFive_digit_display(long serialOutInteger); 

// sends the argument integer to the serial port
// capable of sending a 16 bit unsigned integer
// transmits four of five digits, depending on whether the 10^4 digit is 0 or not

void fourOrFive_digit_display(long serialOutInteger)// sends the argument integer to the serial port
{
    int display_count;
//
//Tenthousands
    if (serialOutInteger >= 10000)
    {
        /*if (serialOutInteger >= 90000)
        {
            display_count = 0x39;
            serialOutInteger = (serialOutInteger - 90000);
        }
        if (serialOutInteger >= 80000)
        {
            display_count = 0x38;
            serialOutInteger = (serialOutInteger - 80000);
        }
        if (serialOutInteger >= 70000)
        {
            display_count = 0x37;
            serialOutInteger = (serialOutInteger - 70000);
        } */
        if (serialOutInteger >= 60000)
        {
            display_count = 0x36;
            serialOutInteger = (serialOutInteger - 60000);
        }
        if (serialOutInteger >= 50000)
        {
            display_count = 0x35;
            serialOutInteger = (serialOutInteger - 50000);
        }
        if (serialOutInteger >= 40000)
        {
            display_count = 0x34;
            serialOutInteger = (serialOutInteger - 40000);
        }
        if (serialOutInteger >= 30000)
        {
            display_count = 0x33;
            serialOutInteger = (serialOutInteger - 30000);
        }
        if (serialOutInteger >= 20000)
        {
            display_count = 0x32;
            serialOutInteger = (serialOutInteger - 20000);
        }
        if (serialOutInteger >= 10000)
        {
            display_count = 0x31;
            serialOutInteger = (serialOutInteger - 10000);
        }
        if (serialOutInteger < 10000)
        {
            putc(display_count);
        }
    }


// Thousands
//
    display_count = 0x30;
    if (serialOutInteger >= 9000)
    {
        display_count = 0x39;
        serialOutInteger = (serialOutInteger - 9000);
    }
    if (serialOutInteger >= 8000)
    {
        display_count = 0x38;
        serialOutInteger = (serialOutInteger - 8000);
    }
    if (serialOutInteger >= 7000)
    {
        display_count = 0x37;
        serialOutInteger = (serialOutInteger - 7000);
    }
    if (serialOutInteger >= 6000)
    {
        display_count = 0x36;
        serialOutInteger = (serialOutInteger - 6000);
    }
    if (serialOutInteger >= 5000)
    {
        display_count = 0x35;
        serialOutInteger = (serialOutInteger - 5000);
    }
    if (serialOutInteger >= 4000)
    {
        display_count = 0x34;
        serialOutInteger = (serialOutInteger - 4000);
    }
    if (serialOutInteger >= 3000)
    {
        display_count = 0x33;
        serialOutInteger = (serialOutInteger - 3000);
    }
    if (serialOutInteger >= 2000)
    {
        display_count = 0x32;
        serialOutInteger = (serialOutInteger - 2000);
    }
    if (serialOutInteger >= 1000)
    {
        display_count = 0x31;
        serialOutInteger = (serialOutInteger - 1000);
    }
    if (serialOutInteger < 1000)
    {
        putc(display_count);
    }
    
//
// Hundreds
//
    display_count = 0x30;
    if (serialOutInteger >= 900)
    {
        display_count = 0x39;
        serialOutInteger = (serialOutInteger - 900);
    }
    if (serialOutInteger >= 800)
    {
        display_count = 0x38;
        serialOutInteger = (serialOutInteger - 800);
    }
    if (serialOutInteger >= 700)
    {
        display_count = 0x37;
        serialOutInteger = (serialOutInteger - 700);
    }
    if (serialOutInteger >= 600)
    {
        display_count = 0x36;
        serialOutInteger = (serialOutInteger - 600);
    }
    if (serialOutInteger >= 500)
    {
        display_count = 0x35;
        serialOutInteger = (serialOutInteger - 500);
    }
    if (serialOutInteger >= 400)
    {
        display_count = 0x34;
        serialOutInteger = (serialOutInteger - 400);
    }
    if (serialOutInteger >= 300)
    {
        display_count = 0x33;
        serialOutInteger = (serialOutInteger - 300);
    }
    if (serialOutInteger >= 200)
    {
        display_count = 0x32;
        serialOutInteger = (serialOutInteger - 200);
    }
    if (serialOutInteger >= 100)
    {
        display_count = 0x31;
        serialOutInteger = (serialOutInteger - 100);
    }
    putc(display_count);
//
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