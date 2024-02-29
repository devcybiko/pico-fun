/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

const uint LED_PIN = PICO_DEFAULT_LED_PIN;

int blink(int onms, int offms)
{
    gpio_put(LED_PIN, 1);
    sleep_ms(onms);
    gpio_put(LED_PIN, 0);
    sleep_ms(offms);
}
int main()
{
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true)
    {
        blink(75, 500);
    }
#endif
}
