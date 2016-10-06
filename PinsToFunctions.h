void ckcal_high(void);
void ckcal_low(void);
void cka_high(void);
void cka_low(void);
void ckb_high(void);
void ckb_low(void);
void ckc_high(void);
void ckc_low(void);
void pdrst_high(void);
void pdrst_low(void);
void tnin_high(void);
void tnin_low(void);
void tin_high(void);
void tin_low(void);



void set_high(void);
void set_low(void);
void rem_sel_high(void);
void rem_sel_low(void);
void radrvalid_high(void);
void radrvalid_low(void);
void rdtsth_high(void);
void rdtsth_low(void);
void rdclk_high(void);
void rdclk_low(void);
void rdparld_high(void);
void rdparld_low(void);







void ckcal_high()
{
    output_high(PIN_A0);
}

void ckcal_low()
{
    output_low(PIN_A0);
}


void cka_high()
{
    output_high(PIN_A1);
}

void cka_low()
{
    output_low(PIN_A1);
}

void ckb_high()
{
    output_high(PIN_A2);
}

void ckb_low()
{
    output_low(PIN_A2);
}


void ckc_high()
{
    output_high(PIN_A3);
}

void ckc_low()
{
    output_low(PIN_A3);
}


void tnin_high()
{
    output_high(PIN_A4);
}

void tnin_low()
{
    output_low(PIN_A4);
}

void tin_high()
{
    output_high(PIN_A5);
}

void tin_low()
{
    output_low(PIN_A5);
}

//
// PORT F IMAGE
//

void set_high()
{
    output_high(PIN_F0);
}

void set_low()
{
    output_low(PIN_F0);
}

void rem_sel_high()
{
    output_high(PIN_F1);
}

void rem_sel_low()
{
    output_low(PIN_F1);
}

void radrvalid_high()
{
    output_high(PIN_F2);
}

void radrvalid_low()
{
    output_low(PIN_F2);
}

void rdtsth_high()
{
    output_high(PIN_F3);
}

void rdtsth_low()
{
    output_low(PIN_F3);
}

void rdclk_high()
{
    output_high(PIN_F4);
}

void rdclk_low()
{
    output_low(PIN_F4);
}

void rdparld_high()
{
    output_high(PIN_F5);
}

void rdparld_low()
{
    output_low(PIN_F5);
}

void pdrst_high()
{
    output_high(PIN_F7);
}

void pdrst_low()
{
    output_low(PIN_F7);
}



void rdout()
{
}