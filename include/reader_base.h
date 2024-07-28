#ifndef READER_BASE_H_
#define READER_BASE_H_

#include <stdint.h>

typedef struct 
{
    void (*read) (char *buffer, uint8_t size);
} reader_base_t;

#endif/* READER_BASE_H_ */
