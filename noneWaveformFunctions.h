void read_chrono(void);

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





