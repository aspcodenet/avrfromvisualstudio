#include <stdio.h>

void uart_init(void);

int uart_putchar(char chr, FILE* stream);

char uart_getchar(void);