void waveform_mrst4(void);



//Pinouts:   [F7    F6   F5      F4    F3     F2        F1      F0]
//Function:  [pdrst none rdparld rdclk rdtsth radrvalid rem_sel set]

//Pinouts:   [A7   A6   A5  A4   A3  A2  A1  A0]
//Function:  [none none tin tnin ckc ckb cka ckcal]

void waveform_mrst4()//MemoryResetTestsection
{
output_f(0b10000001);
output_a(0b00010000);
output_f(0b00000001);
delay_cycles(5);
output_a(0b00000000);
output_f(0b00000000);
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
output_a(0b00100010);
delay_cycles(5);
delay_cycles(5);
output_a(0b00010010);
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
voidwaveform_mrst4()//MemoryResetTestsection
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
tin_low();//t11
delay_us(2);//5,2
tnin_high();
delay_us(9);//37,18
tnin_low();
delay_us(9);//37,18
tin_high();
cka_high();
delay_us(6);//25,12
tin_low();
tnin_high();//t25
delay_us(6);//25,12
cka_low();
tnin_low();
delay_us(18);//75,36
tin_high();//t38
delay_us(6);//25,12
tin_low();
//delay_us(12);//25
}
*/