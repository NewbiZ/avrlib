#include <ringbuffer.h>

#include <stdlib.h>

void ringbuffer_init(ringbuffer_t* rb, size_t size) {
    rb->size = 0;
    if ((rb->buffer = (char*)malloc(size))) {
        rb->size = size;
    }
    rb->head = rb->tail = rb->buffer;
}

void ringbuffer_release(ringbuffer_t* rb) {
    free((char*)rb->buffer);
}

size_t ringbuffer_size(const ringbuffer_t* rb) {
    return rb->size;
}

size_t ringbuffer_read(ringbuffer_t* rb, char* buffer, size_t size) {
    size_t count = 0;
    while ((rb->head != rb->tail) && (count < size)) {
        *buffer++ = *rb->head++;
        ++count;
        if (rb->head >= rb->buffer+rb->size)
            rb->head = rb->buffer;
    }
    return count;
}

size_t ringbuffer_write(ringbuffer_t* rb, const char* buffer, size_t size) {
    size_t count = 0;
    while (count++ < size) {
        *rb->tail++ = *buffer++;
        if (rb->tail >= rb->buffer+rb->size)
            rb->tail = rb->buffer;
        if (rb->tail == rb->head) {
            ++rb->head;
            if (rb->head >= rb->buffer+rb->size)
                rb->head = rb->buffer;
        }
    }
    return count-1;
}

int ringbuffer_empty(const ringbuffer_t* rb) {
    return rb->head == rb->tail;
}
