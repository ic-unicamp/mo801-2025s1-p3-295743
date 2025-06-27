#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libbase/console.h>
#include <irq.h>
#include <libbase/uart.h>
#include <generated/csr.h>

#define TIMER_LOAD 0xFFFFFFFF

void multiply_matrices_sw(uint32_t *A, uint32_t *B_transposed, uint32_t *C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            uint32_t sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B_transposed[j * N + k];
            }
            C[i * N + j] = sum;
        }
    }
}

void medir_tempo_sw(void) {
    int N = 20; 
    uint32_t a[N*N];
    uint32_t b[N*N];
    uint32_t b_transposed[N*N];
    uint32_t c[N*N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i * N + j] = i + j;    
            b[i * N + j] = i * j;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            b_transposed[j * N + i] = b[i * N + j];
        }
    }

    printf("Matriz A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%6lu", (unsigned long)a[i * N + j]);
        }
        printf("\n");
    }

    printf("Matriz B (original):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%6lu", (unsigned long)b[i * N + j]);
        }
        printf("\n");
    }

    timer0_en_write(0);             
    timer0_load_write(0xFFFFFFFF);   
    timer0_reload_write(0xFFFFFFFF);
    timer0_en_write(1);              

    multiply_matrices_sw(a, b_transposed, c, N);

    timer0_update_value_write(1);
    unsigned int restante = timer0_value_read();
    unsigned int ciclos = 0xFFFFFFFF - timer0_value_read();
    uint64_t tempo_us = ((uint64_t)ciclos * 1000000) / CONFIG_CLOCK_FREQUENCY;

    printf("Tempo SW: %u ciclos (%llu us)\n", ciclos, tempo_us);

    printf("Resultado da multiplicação (Software) para uma matriz (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%6lu", (unsigned long)c[i * N + j]);
        }
        printf("\n");
    }
}

int main(void) {
    #ifdef CONFIG_CPU_HAS_INTERRUPT
        irq_setmask(0);
        irq_setie(1);
    #endif
    uart_init();
    
    printf("Iniciando multiplicação de matrizes em software...\n");
    medir_tempo_sw();
    
    return 0;
}