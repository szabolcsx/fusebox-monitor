#include <init.h>

#include <sfr_helper.h>
#include <uart.h>
#include <adc.h>

#include <io_mapping.h>

#include <avr/io.h>

inline void initIO(void)       /* Ki- és bemeneti kapuk inicalizálása */
{
    //DDRD = 0xFF;

    _OUTPUT(D, 0);
    _OUTPUT(D, 1);
    _OUTPUT(D, 2);
    _OUTPUT(D, 3);
    _OUTPUT(D, 4);
    _OUTPUT(D, 5);
    _OUTPUT(D, 6);
    _OUTPUT(D, 7);
}

inline void initTimer0(void)   /* Timer0 modul inicializálása */
{
    _SB(PCICR, PCIE0);
    _SB(PCMSK0, PCINT0);

    _SB(TCCR0A, WGM01);
    OCR0A = 149;
    _SB(TIMSK0, OCIE0A);

    _SB(TCCR0B, CS00);
    _SB(TCCR0B, CS01); // 1:64 prescaler
}

inline void initA2D(void)      /* Analóg-digitális átalakító inicializálása */
{
    adcSetVoltageReference(ADC_VR_AVCC);
    adcSetPrescaler(ADC_PRESCALER128);
    adcEnable();
}

inline void initUART(void)     /* UART inicializálása */
{
    uartInit(BAUD_PS(9600));
    uartEnableTx();
}

inline void initLCD(void)      /* LCD kijelző inicializálása */
{
    lcdInit(&lcdHandle,
    LCD_4BIT_BUS | LCD_2LINE_MODE | LCD_5X7_DOTS_FORMAT,
    LCD_DISPLAY_ON | LCD_CURSOR_ON,
    LCD_INCREMENT);
}
