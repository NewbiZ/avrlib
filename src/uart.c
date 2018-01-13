#include <ringbuffer.h>

#include <avr/interrupt.h>
#include <avr/io.h>

#define F_CPU 8000000UL
#define BAUD 9600
#include <util/setbaud.h>

static ringbuffer_t __uart_rx;
static ringbuffer_t __uart_tx;
static int __echo;

void uart_init(size_t buffer_size, int echo) {
    /* Allocate RX/TX ring buffers */
    ringbuffer_init(&__uart_rx, buffer_size);
    ringbuffer_init(&__uart_tx, buffer_size);

    /* Remember echo flag */
    __echo = echo;

    /* Compute UART speed */
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    /* Disable 2x mode */
    UCSR0A &= ~_BV(U2X0);

    /* Enable 8bit data */
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);

    /* Enable RX and TX for UART */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);

    /* Enable UART RX interrupt */
    UCSR0B |= (1 << RXCIE0) | (1 << UDRIE0);

    /* Enable all interrupts */
    sei();
}

void uart_release() {
    /* TODO */
}

ISR(USART_RX_vect) {
    /* Write received byte to the RX ring buffer */
    char received = UDR0;
    ringbuffer_write(&__uart_rx, &received, 1);
    if (__echo) {
        /* Echo received bytes */
        ringbuffer_write(&__uart_tx, &received, 1);
    }
}

ISR(USART_UDRE_vect) {
    /* Read sent byte from the TX ring buffer */
    if (ringbuffer_empty(__uart_tx))
        return;
    char sent;
    ringbuffer_read(&__uart_tx, &sent, 1);
    UDR0 = sent;
}

size_t uart_read(char* buffer, size_t size) {
    /* Read received bytes from the RX rinf buffer */
    return ringbuffer_read(&__uart_rx, buffer, size);
}

size_t uart_write(const char* buffer, unsigned int size) {
    /* Write sent bytes to the TX ring buffer */
    return ringbuffer_write(&__uart_tx, buffer, size);
}
