#ifndef UART_H
#define UART_H

#include <stddef.h>

void uart_init(size_t buffer_size, int echo);
void uart_release();

size_t uart_read(char* buffer, size_t size);
size_t uart_write(const char* buffer, unsigned int size);

#endif /* UART_H */
