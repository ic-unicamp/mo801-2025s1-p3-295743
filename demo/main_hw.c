#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libbase/console.h>
#include <irq.h>
#include <libbase/uart.h>
#include <generated/csr.h> 


#define TIMER_LOAD 0xFFFFFFFF 

void medir_tempo_hw(void);
void multiply_matrices(uint32_t *A, uint32_t *B_transposed, uint32_t *C, int N);

void multiply_matrices(uint32_t *A, uint32_t *B_transposed, uint32_t *C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix_multiplier_reset_accum_write(1);

            for (int k = 0; k < N; k++) {
                uint32_t a_val = A[i * N + k];
                uint32_t b_val = B_transposed[j * N + k];

                matrix_multiplier_a_val_in_write(a_val);
                matrix_multiplier_b_val_in_write(b_val);

                matrix_multiplier_add_to_accum_write(1);
            }
            C[i * N + j] = matrix_multiplier_accum_out_read();
        }
    }
}
void medir_tempo_hw(void) {
    int N = 9; 
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
    for (int i = 0; i < N * N; i++) {
        printf("%6lu", (unsigned long)a[i]); 
        if ((i + 1) % N == 0) printf("\n");
    }

    printf("Matriz B (original):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%6lu", (unsigned long)b[i * N + j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N * N; i++) {
        c[i] = 0;
    }

    timer0_en_write(0);
    timer0_load_write(TIMER_LOAD);
    timer0_en_write(1);

    multiply_matrices(a, b_transposed, c, N);

    timer0_update_value_write(1);
    unsigned int restante = timer0_value_read();
    unsigned int ciclos = TIMER_LOAD - restante;
    unsigned int tempo_us = (ciclos * 1000000) / CONFIG_CLOCK_FREQUENCY;

    printf("Tempo HW: %u ciclos (%u us)\n", ciclos, tempo_us);

    printf("Resultado da multiplicação (Hardware) para uma matriz (%dx%d):\n", N, N);
    for (int i = 0; i < N * N; i++) {
        printf("%6lu", (unsigned long)c[i]);
        if ((i + 1) % N == 0) printf("\n");
    }
}

int main(void) {
    #ifdef CONFIG_CPU_HAS_INTERRUPT
        irq_setmask(0);
        irq_setie(1);
    #endif
    uart_init();
    printf("Iniciando multiplicação de matrizes via acelerador...\n");
    medir_tempo_hw();
    return 0;
}