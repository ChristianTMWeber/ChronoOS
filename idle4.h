void waveform_idle4(void);

// Pinouts:   [A7   A6   A5  A4   A3  A2  A1  A0]
// Function:  [none none tin tnin ckc ckb cka ckcal]

void waveform_idle4()
{
output_a(0b00000000);
output_a(0b00010000);
pdrst_high();
delay_cycles(5);
pdrst_low();
output_a(0b00000000);
output_a(0b00100000);
delay_cycles(5);
delay_cycles(5);
output_a(0b00100000);
output_a(0b00000000);
output_a(0b00010000);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
output_a(0b00000000);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
output_a(0b00100000);
delay_cycles(5);
delay_cycles(5);
output_a(0b00010000);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
output_a(0b00000000);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
output_a(0b00100000);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
delay_cycles(5);
output_a(0b00000000);
}


/*
voidwaveform_idle4()
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
*/