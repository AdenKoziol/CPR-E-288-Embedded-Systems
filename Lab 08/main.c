#include "lcd.h"
#include "Timer.h"
#include "adc.h"

/**
 * main.c
 */
int main(void)
{
    adc_init();
    lcd_init();
    int value;
    char message[20];
    int averages[10];
    int i = 0;
    while(i < 10)
    {
        value = adc_read();
        averages[i] = value;
        timer_waitMillis(1000);
        i++;
//        sprintf(message, "%d", value);
//        lcd_clear();
//        lcd_home();
//        lcd_puts(message);


    }
    int j;
    int averag;
    for(j = 0; j < 10; j++)
    {
        averag += averages[i];
    }
    averag /= 10;
    sprintf(message, "%d", averag);
    lcd_clear();
    lcd_home();
    lcd_puts(message);

	return 0;
}
