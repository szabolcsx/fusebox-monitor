#include <avr/interrupt.h>

#include <counter.h>
#include <flags.h>

ISR(TIMER0_COMPA_vect)
{
    counterUpdateLcd++;

    if(counterUpdateLcd >= 50)
    {
        counterUpdateLcd = 0;
        eventFlags.updateLcdRequested = 1;
    }
}
