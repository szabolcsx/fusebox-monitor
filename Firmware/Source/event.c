#include <event.h>

#include <lcd2.h>
#include <io_mapping.h>
#include <flags.h>

inline void handleEvents(void)     /* Eseményel feldolgozása */
{
    if(eventFlags.updateLcdRequested)
    {
        eventFlags.updateLcdRequested = 0;

        lcdwStringAt(&lcdHandle, 1, 1, "Hello world!");
    }

    if(eventFlags.handlePinChangeRequested)
    {
        eventFlags.handlePinChangeRequested = 0;
    }
}
