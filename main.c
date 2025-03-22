#include <stdio.h>
#include "pico/stdlib.h"
#include "neopixel_pio.h"
#include "buzzer.h"

int main() {
    stdio_init_all();

    // Inicializa LEDs e Buzzer
    npInit(LED_PIN);
    buzzerInit();

    uint led1_pos = 0;  // Primeira LED (vermelho)
    uint led2_pos = 1;  // Segunda LED (azul)
    
    while (1) {
        npClear(); // Limpa a matriz antes de acender os LEDs

        // Acende os LEDs nas posições atuais
        npSetLED(led1_pos, 255, 0, 0);  // Vermelho
        npSetLED(led2_pos, 0, 0, 255);  // Azul
        npWrite();

        // Toca uma nota da música enquanto os LEDs estão acendendo
        playNote(mario_theme[(led1_pos + led2_pos) % mario_theme_size].frequency, 
                 mario_theme[(led1_pos + led2_pos) % mario_theme_size].duration);

        // Avança para o próximo LED
        led1_pos = (led1_pos + 1) % LED_COUNT;
        led2_pos = (led2_pos + 1) % LED_COUNT;

        sleep_ms(100); // Ajusta o tempo da animação
    }
}