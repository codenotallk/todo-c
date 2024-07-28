#ifndef DISPLAY_BASE_H_
#define DISPLAY_BASE_H_

typedef struct 
{
    void (*show) (char *message);
} display_base_t;

#endif/* DISPLAY_BASE_H_ */
