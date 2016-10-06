void waveform_mrst4(void);

void waveform_mrst4()            // Memory Reset Test section
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
    tin_low();                 //t11
    delay_us(2);//5,2
    tnin_high();
    delay_us(9);//37,18
    tnin_low();
    delay_us(9);//37,18
    tin_high();
    cka_high();
    delay_us(6);//25,12
    tin_low();
    tnin_high();               //t25
    delay_us(6);//25,12
    cka_low();
    tnin_low();
    delay_us(18);//75,36
    tin_high();                //t38
    delay_us(6);//25,12
    tin_low();
//   delay_us(12);//25
}