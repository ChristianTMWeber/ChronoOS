void waveform_idle4(void);

void waveform_idle4()
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