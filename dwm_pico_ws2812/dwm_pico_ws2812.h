/*
 * File: dwm_pico_ws2812.h
 * Project: dwm_pico_ws2812
 * -----
 * This source code is released under BSD-3 license.
 * Check LICENSE file for full list of conditions and disclaimer.
 * -----
 * Copyright 2023 - 2023 M.Kusiak (timax)
 */

#ifndef DWM_PICO_WS2812_H
#define DWM_PICO_WS2812_H

#include "pico/stdlib.h"
#include "hardware/pio.h"

typedef struct
{
    bool rgbw;
    uint8_t pin;
    uint pixelNumber;
    PIO pio;
    uint stateMachine;
    uint offset;
} ledStrip_t;

ledStrip_t *ws2812SetupLedStrip(bool rgbw, uint8_t pin, uint pixelNumber, PIO pio, uint stateMachine);
void ws2812InitLedStrip(const ledStrip_t *ledStrip);
void ws2812PutPixel(const ledStrip_t *ledStrip, uint32_t pixelRGB);
uint32_t ws2812GetRGBValue(uint8_t red, uint8_t green, uint8_t blue);

#endif