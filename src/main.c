#define F_CPU 8000000UL
#define BAUD 9600

#include <avr/power.h>
#include <avr/io.h>
#include <util/delay.h>

void clock_init()
{
    clock_prescale_set(clock_div_1);
}

int main()
{
    clock_init();
    uart_init(128, 1);

    const char* str = "UART initialized";
    //uart_write(str, strlen(str));

    while (1) {}
}
