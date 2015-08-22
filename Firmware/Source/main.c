#include <init.h>
#include <lcd2.h>
#include <io_mapping.h>
#include <flags.h>

#include <avr/interrupt.h>

int main(void)
{
    initIO();
    initTimer0();
    initA2D();
    initUART();
    initLCD();

    sei();

    while(1)
    {
        if(eventFlags.updateLcdRequested)
        {
            eventFlags.updateLcdRequested = 0;

            lcdwStringAt(&lcdHandle, 1, 1, "Hello world!");
        }
    }

    return 0;
}
