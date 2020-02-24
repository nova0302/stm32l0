/* observed component */
#ifndef OBSER_H
#define OBSER_H
#include <stdio.h>
#include <stdint.h>

typedef struct {
    int listener_count;
    /* array of function pointers */
    void (*listener_list[10])(uint32_t);
} Button;

void button_Init( Button *pButton );

void button_RemoveClickListener( Button *pButton,
                                 void (*fp)(uint32_t) );


void button_AddClickListener( Button *pButton,
                              void (*fp)(uint32_t) );


void button_Click( Button *pButton, uint32_t);

void observer1_OnClick( uint32_t i );
void observer2_OnClick( uint32_t i );

#endif /* OBSER_H */
