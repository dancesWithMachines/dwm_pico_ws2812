/*
 * File: dwm_pico_ws2812.c
 * Project: dwm_pico_ws2812
 * -----
 * This source code is released under BSD-3 license.
 * Check LICENSE file for full list of conditions and disclaimer.
 * -----
 * Copyright 2023 - 2023 M.Kusiak (timax)
 */

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#include "dwm_pico_ws2812.h"

#define DEFAULT_FREQUENCY 800000

/**
 * @brief SetupsLED strip. Fills stuct with necessary values.
 *
 * @param rgbw          true if strip is made of RGBW LEDs (separate white color), false for RGB.
 * @param pin           pin to whichLED strip is connected.
 * @param pixelNumber   number of pixels in aLED strip.
 * @param pio           pio, refer to RP2040 manual for explanation.
 * @param stateMachine  state machine number, refer to RP2040 manual for explanation.
 * @return ledStrip_t*  pointer to set upLED strip.
 */
ledStrip_t *ws2812SetupLedStrip(bool rgbw, uint8_t pin, uint pixelNumber, PIO pio, uint stateMachine)
{
    ledStrip_t *ledStrip = malloc(sizeof(ledStrip_t));

    if (ledStrip)
        *ledStrip = (ledStrip_t){.rgbw = rgbw,
                                 .pin = pin,
                                 .pixelNumber = pixelNumber,
                                 .pio = pio,
                                 .stateMachine = stateMachine,
                                 .offset = pio_add_program(pio, &ws2812_program)};

    return ledStrip;
}
/**
 * @brief InitiateLED strip.
 *
 * @param ledStripLED strip to be initiated.
 */
void ws2812InitLedStrip(const ledStrip_t *ledStrip)
{
    ws2812_program_init(ledStrip->pio, ledStrip->stateMachine, ledStrip->offset, ledStrip->pin, DEFAULT_FREQUENCY, ledStrip->rgbw);
}

/**
 * @brief       Set a color for single pixel inLED strip.
 *              Multiple calls will result in multiple pixels being lit.
 * @details     Must wait about 20ms for next call, otherwise next pixel will be set.
 * @attention   Blocking function!
 *
 * @param ledStrip LED strip struct.
 * @param pixelRGB  RGB value.
 */
void ws2812PutPixel(const ledStrip_t *ledStrip, uint32_t pixelRGB)
{
    pio_sm_put_blocking(ledStrip->pio, ledStrip->stateMachine, pixelRGB << 8u);
}

/**
 * @brief Get RGB value from individual colors.
 *
 * @param red           red color value.
 * @param green         green color value.
 * @param blue          blue color value.
 * @return uint32_t     RGB value.
 */
uint32_t ws2812GetRGBValue(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((uint32_t)(red) << 8) |
           ((uint32_t)(green) << 16) |
           (uint32_t)(blue);
}
