#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13
#define BOTAO 5

volatile int estado = 0;
volatile bool pode_mudar = true; // Controle para evitar reinício durante a execução

// Função de callback do temporizador
int64_t timer_callback(alarm_id_t id, void *user_data) {
    if (estado == 0) {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_AMARELO, 1);
        gpio_put(LED_VERDE, 1);
        estado = 1;
    } else if (estado == 1) {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_AMARELO, 1);
        gpio_put(LED_VERDE, 0);
        estado = 2;
    } else if (estado == 2) {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_AMARELO, 0);
        gpio_put(LED_VERDE, 0);
        estado = 3;
    } else {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_AMARELO, 0);
        gpio_put(LED_VERDE, 0);
        estado = 0;
        pode_mudar = true; // Permite nova ativação pelo botão
        return 0;
    }
    add_alarm_in_ms(3000, timer_callback, NULL, false); // Reagendar temporizador
    return 0;
}

// Interrupção do botão
void botao_callback(uint gpio, uint32_t events) {
    if (pode_mudar) {
        pode_mudar = false; // Impede nova ativação até o ciclo terminar
        estado = 0; // Garante que o ciclo inicie corretamente
        add_alarm_in_ms(1, timer_callback, NULL, false); // Inicia o ciclo imediatamente
    }
}

int main() {
    stdio_init_all();

    gpio_init(LED_VERMELHO);
    gpio_init(LED_AMARELO);
    gpio_init(LED_VERDE);
    gpio_init(BOTAO);

    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);

    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, true, &botao_callback);

    while (1) {
        tight_loop_contents(); // Mantém o loop principal ativo sem consumo excessivo
    }
}

