/*
 * File: example.c
 * Project: dwm_pico_ws2812
 * -----
 * This source code is released under BSD-3 license.
 * Check LICENSE file for full list of conditions and disclaimer.
 * -----
 * Copyright 2023 - 2023 M.Kusiak (timax)
 */

#include "pico/stdlib.h"
#include "dwm_pico_ws2812/dwm_pico_ws2812.h"

#define NUM_PIXELS 8
#define WS2812_LEDSTRIP_PIN 16

#define PIXEL_CHECK_SPEED_MS 50

#define COLOR_NULL 0
#define COLOR_GREEN 16711680
#define COLOR_YELLOW 16776960
#define COLOR_RED 65280
#define COLOR_WHITE 16777215

/**
 * @brief       Performs check animation to test base colors for all LEDs in LED strip.
 * @attention   Blocking function!
 *
 * @param ledStrip LED strip.
 */
void ledStripCheck(const ledStrip_t *ledStrip)
{
    const uint32_t colors[] = {COLOR_GREEN, COLOR_YELLOW, COLOR_RED, COLOR_WHITE};
    uint8_t colorsLeft = (ledStrip->rgbw) ? 4 : 3;
    uint8_t colorPixelIndex;

    while (colorsLeft > 0)
    {
        for (uint8_t i = 0; i < ledStrip->pixelNumber * 2; i++)
        {
            for (uint8_t j = 0; j < ledStrip->pixelNumber; j++)
            {
                colorPixelIndex = (i < ledStrip->pixelNumber) ? i : ledStrip->pixelNumber * 2 - i - 1;

                if (j == colorPixelIndex)
                    ws2812PutPixel(ledStrip, colors[colorsLeft - 1]);
                else
                    ws2812PutPixel(ledStrip, COLOR_NULL);
            }
            sleep_ms(PIXEL_CHECK_SPEED_MS);
        }
        colorsLeft--;
    }
}

/**
 * @brief This function demonstrates why library is considered blocking.
 *
 * @param ledStrip LED strip.
 */
void ws2812BlockTest(const ledStrip_t *ledStrip)
{
    uint32_t greenValue = ws2812GetRGBValue(0, 255, 0);
    uint32_t redValue = ws2812GetRGBValue(255, 0, 0);
    uint32_t blueValue = ws2812GetRGBValue(0, 0, 255);

    // Clear led strip
    for (uint8_t i = 0; i < ledStrip->pixelNumber; i++)
        ws2812PutPixel(ledStrip, COLOR_NULL);

    // Approx 20ms of delay is needed
    sleep_ms(20);

    // This will lit 3 first pixels
    ws2812PutPixel(ledStrip, greenValue);
    ws2812PutPixel(ledStrip, redValue);
    ws2812PutPixel(ledStrip, blueValue);

    sleep_ms(3000);

    // Clear led strip
    for (uint8_t i = 0; i < ledStrip->pixelNumber; i++)
        ws2812PutPixel(ledStrip, COLOR_NULL);

    // Approx 20ms of delay is needed
    sleep_ms(20);

    // This will change first pixel 3 times
    ws2812PutPixel(ledStrip, greenValue);
    sleep_ms(1000);
    ws2812PutPixel(ledStrip, redValue);
    sleep_ms(1000);
    ws2812PutPixel(ledStrip, blueValue);
    sleep_ms(1000);
}

int main()
{
    const ledStrip_t *ledStrip = ws2812SetupLedStrip(false, WS2812_LEDSTRIP_PIN, NUM_PIXELS, pio0, 0);

    stdio_init_all();
    ws2812InitLedStrip(ledStrip);

    ws2812BlockTest(ledStrip);

    while (true)
    {
        ledStripCheck(ledStrip);
    }
}