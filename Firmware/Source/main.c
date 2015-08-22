#include <init.h>
#include <event.h>

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
        handleEvents();
    }

    return 0;
}
