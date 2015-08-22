#include <io_mapping.h>

#include <avr/io.h>

lcdHandle_t lcdHandle =
{
    &PORTD, 6, // D4
    &PORTD, 7, // D5
    &PORTD, 2, // D6
    &PORTD, 3, // D7
    &PORTD, 4, // RS
    &PORTD, 5  // EN
};
