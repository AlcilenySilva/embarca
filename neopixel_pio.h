#ifndef NEOPIXEL_PIO_H
#define NEOPIXEL_PIO_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Definição do número de LEDs e pino
#define LED_COUNT 25
#define LED_PIN 7

// Estrutura para representar um pixel (GRB)
typedef struct {
    uint8_t G, R, B;
} npLED_t;

// Declaração das funções
void npInit(uint pin);
void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b);
void npClear();
void npWrite();
void corridaEmLinhaReta();

#endif // NEOPIXEL_PIO_H
