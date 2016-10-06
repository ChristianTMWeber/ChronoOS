void waveform_wrtsig(void);

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