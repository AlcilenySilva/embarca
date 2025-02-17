#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "ws2818b.pio.h"

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

// Definição de pixel GRB
struct pixel_t {
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin) {
  // Cria programa PIO.
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  // Toma posse de uma máquina PIO.
  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0) {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  // Inicia programa na máquina PIO obtida.
  ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < LED_COUNT; ++i) {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}

/**
 * Limpa o buffer de pixels.
 */
void npClear() {
  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(i, 0, 0, 0);
}

/**
 * Escreve os dados do buffer nos LEDs.
 */
void npWrite() {
  // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
  for (uint i = 0; i < LED_COUNT; ++i) {
    pio_sm_put_blocking(np_pio, sm, leds[i].G);
    pio_sm_put_blocking(np_pio, sm, leds[i].R);
    pio_sm_put_blocking(np_pio, sm, leds[i].B);
  }
  sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

/**
 * Atribui as cores para as LEDs em movimento.
 */
void corridaEmLinhaReta() {
  // LEDs com cores diferentes
  uint8_t cor1_R = 255, cor1_G = 0, cor1_B = 0;  // Primeira LED (vermelha)
  uint8_t cor2_R = 0, cor2_G = 0, cor2_B = 255;  // Segunda LED (azul)

  // Define o número total de LEDs na matriz (5x5 = 25 LEDs)
  uint led1_pos = 0;  // Posição inicial da primeira LED
  uint led2_pos = 1;  // Posição inicial da segunda LED (logo após a primeira)

  // Corre por toda a linha de LEDs
  for (uint i = 0; i < LED_COUNT; ++i) {
    npClear(); // Limpa a matriz

    // Acende o primeiro LED com a cor vermelha
    npSetLED(led1_pos, cor1_R, cor1_G, cor1_B);
    // Acende o segundo LED com a cor azul
    npSetLED(led2_pos, cor2_R, cor2_G, cor2_B);

    // Atualiza a matriz
    npWrite();
    
    sleep_ms(300); // Espera 300ms para a animação (mais lento)

    // Atualiza a posição das LEDs para simular a corrida
    led1_pos++;
    led2_pos++;

    // Quando o primeiro LED chegar ao final, ele volta para o início
    if (led1_pos >= LED_COUNT) led1_pos = 0;

    // Quando o segundo LED chegar ao final, ele volta para o início
    if (led2_pos >= LED_COUNT) led2_pos = 0;
  }
}

int main() {
  // Inicializa entradas e saídas.
  stdio_init_all();

  // Inicializa a matriz de LEDs NeoPixel.
  npInit(LED_PIN);

  while (true) {
    corridaEmLinhaReta(); // Chama a função para a corrida em linha reta
  }
}