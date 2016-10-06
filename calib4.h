void waveform_calib4(void);

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