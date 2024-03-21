/*
 * tps65 for Raspberry Pi Pico
 *
 * @version     1.0.0
 * @author      greg@agilefrontiers.com
 * @copyright   2024
 * @licence     MIT
 *
 */
#include "main.h"

const uint LED_PIN = PICO_DEFAULT_LED_PIN;

int blink(int onms, int offms)
{
    gpio_put(LED_PIN, 1);
    sleep_ms(onms);
    gpio_put(LED_PIN, 0);
    sleep_ms(offms);
}

int main() {
    // Use for debugging
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(true) {
        blink(75, 500);
        printf("tps65 for Raspberry Pi Pico (c) 2024 Agile Frontiers\n");
        sleep_ms(1000);
    }
    return 0;
}
