void waveform_calin4(void);

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