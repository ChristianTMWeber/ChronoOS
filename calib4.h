void waveform_calib4(void);


void waveform_calib4()
{
//Pinouts:   [A7 A6A A% A4 A3 A2 A1 A0]
//Function:  [none none tin tnin ckc ckb cka ckcal]
output_a(0b00000000);
output_a(0b00010000);
pdrst_high();
delay_cycles(1);
pdrst_low();
output_a(0b00000000);
output_a(0b00100000);
delay_cycles(1);
delay_cycles(1);
output_a(0b00100001);
output_a(0b00000001);
output_a(0b00010001);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
output_a(0b00000000);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
output_a(0b00101010);
delay_cycles(1);
delay_cycles(1);
output_a(0b00011010);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
output_a(0b00000000);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
output_a(0b00100000);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
delay_cycles(1);
output_a(0b00000000);
}
/*
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
*/