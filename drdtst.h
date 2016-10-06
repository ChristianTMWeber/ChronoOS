void waveform_drdtst(void);

void waveform_drdtst()                       //Read the Chronopixel
{
    chrono_data = 0;
    cka_low();
    ckb_low();
    ckc_low();
    ckcal_low();
    rem_sel_low();
    rdtsth_low();
    pdrst_high();
    
    tnin_high();
    delay_us(2);//13 6 3
    tnin_low();
    delay_us(1);//13 6 3
    tin_high();
    radrvalid_high();
    delay_us(1);//8 4 2
    rdparld_high();
    delay_us(1);//5 2
    tin_low();                 //t10
    delay_us(1);//5 2
    rdclk_high();              //t11
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 2048);
    }
    delay_us(2);//15 7 4
    rdparld_low();             //t15
    delay_us(1);//12 6 3
    rdclk_low();
    delay_us(2);//15 8 4
    rdclk_high();              //t20
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 1024);
    }
    delay_us(1);//13 6 3
    radrvalid_low();           //t22
    delay_us(1);//13 6 3
    rdclk_low();               //t24
    delay_us(1);//20 10 5
    tnin_high();               //t27
    delay_us(1);//5 2
    rdclk_high();              //t28
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 512);
    }
    
    delay_us(1);//13 6 3
    tnin_low();                //t31
    delay_us(1);//5 2
    rdclk_low();               //t32
    delay_us(1);//13 6 3
    tin_high();                //t35
    delay_us(1);//13 6 3
    rdclk_high();              //t36
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 256);
    }
    
    delay_us(1);//13 6 3
    tin_low();                 //t38
    delay_us(1);//13 6 3
    rdclk_low();               //t40
    delay_us(2);//25 12 6
    rdclk_high();              //t44
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 128);
    }
    
    delay_us(2);//25 12 6
    rdclk_low();               //t48
    delay_us(2);//25 12
    rdclk_high();              //t52
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 64);
    }
    
    delay_us(1);//20 10 5
    tnin_high();               //t55
    delay_us(1);//5 2
    rdclk_low();               //t56
    delay_us(2);//20 10
    tnin_low();                //t59
    delay_us(1);//5 2
    rdclk_high();              //t61
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 32);
    }
    
    delay_us(1);//13 6 3
    tin_high();                //t63
    delay_us(1);//8 4 2
    rdclk_low();               //t64
    delay_us(1);//8 4 2
    tin_low();                 //t65
    delay_us(1);//5 2
    rdclk_high();              //t68
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 16);
    }
    
    delay_us(2);//25 12 6
    rdclk_low();               //t72
    delay_us(2);//25 12 6
    rdclk_high();              //t76
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 8);
    }
    
    delay_us(2);//25 12 6
    rdclk_low();               //t81
    delay_us(1);//13 6 3
    tnin_high();               //t84
    delay_us(1);//13 6 3
    rdclk_high();              //t85
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 4);
    }
    
    delay_us(1);//13 6 3
    tnin_low();                //t87
    delay_us(1);//13 6 3
    rdclk_low();               //t88
    delay_us(1);//13 6 3
    tin_high();                //t91
    delay_us(1);//13 6 3
    rdclk_high();              //t93
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 2);
    }
    
    delay_us(1);//13 6 3
    tin_low();                 //t94
    delay_us(1);//13 6 3
    rdclk_low();               //t96
    delay_us(2);//25 12 6
    rdclk_high();              //t100
    if(input(PIN_F6))
    {
        chrono_data = (chrono_data + 1);
    }
    
    delay_us(2);//25 12 6
    rdclk_low();               //t104
    delay_us(3);//25 12 6
    tnin_high();               //t110
    delay_us(3);//13 6
    tnin_low();                //t114
    delay_us(2);//25 12 6
    tin_high();                //t118
    delay_us(2);//25 12 6
    tin_low();                 //t122
//   delay_us(12);//25 12
    
}