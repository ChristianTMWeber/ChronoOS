void waveform_wrtsig(void);

// Pinouts:   [A7   A6   A5  A4   A3  A2  A1  A0]
// Function:  [none none tin tnin ckc ckb cka ckcal]

void waveform_wrtsig()
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
voidwaveform_wrtsig()
{
output_low(PIN_A1);//ckalow
output_low(PIN_A2);//ckblow
output_low(PIN_A3);//ckclow
output_low(PIN_A0);//ckclalow
output_low(PIN_F0);//setlow
output_low(PIN_F5);//rdparldlow
output_low(PIN_F4);//rdclklow
output_low(PIN_F2);//radrvalidlow
output_high(PIN_A4);//tninhigh
output_high(PIN_F7);//pdrsthigh
delay_us(5);
output_low(PIN_F7);//pdrstlow
delay_us(6);
output_low(PIN_A4);//tninlow
delay_us(1);
output_high(PIN_A5);//tinhigh
delay_us(2);
output_low(PIN_A5);//tinlowatt11
delay_us(1);
output_high(PIN_A4);//tninhigh
delay_us(2);
output_low(PIN_A4);//tninlow
delay_us(2);
output_high(PIN_A5);//tinhigh
delay_us(2);
output_high(PIN_A1);//ckahighatt24
delay_us(2);
output_low(PIN_A5);//tinlow
output_high(PIN_A4);//tninhighatt25
delay_us(2);
output_low(PIN_A1);//ckalow
delay_us(2);
output_low(PIN_A4);//tninlow
delay_us(1);
output_high(PIN_A5);//tinhighatt38
delay_us(2);
output_low(PIN_A5);//tinlow
}
*/