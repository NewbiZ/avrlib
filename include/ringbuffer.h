#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stddef.h>

typedef struct {
    size_t size;
    volatile char* head;
    volatile char* tail;
    volatile char* buffer;
} ringbuffer_t;

void ringbuffer_init(ringbuffer_t* rb, size_t size);
void ringbuffer_release(ringbuffer_t* rb);

size_t ringbuffer_size(const ringbuffer_t* rb);
size_t ringbuffer_read(ringbuffer_t* rb, char* buffer, size_t size);
size_t ringbuffer_write(ringbuffer_t* rb, const char* buffer, size_t size);
int ringbuffer_empty(const ringbuffer_t* rb);

#endif /* RINGBUFFER_H */
