#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00;
        PORTA = 0xFF;
        DDRB = 0xFF;
        PORTB = 0x00;


    /* Insert your solution below */
    while (1) {
        tick();
    }
    return 1;
}



enum states{start, hash, hashRelease, yButton, unlock, lock} state;

void tick(){


        switch (state){

        case start:
                state = lock;
                PORTB = 0x00;
                break;

        case lock:
                PORTB=0x00;
                if ((PINA & 0x07) == 0x04){
                        state = hash;
                }

                else{
                state = lock;
                }

                break;
                
        case hash:
                if ((PINA & 0x07) == 0x02) {
                        state = yButton;
                }
                else {
                        state = lock;
                }
                break;

        case unlock:
                PORTB = 0x01;
                  
                if((PINA & 0x87) == 0x80){
                        state = lock;
                }
                else {
                        state = unlock;
                }
                break;

        default:

                PORTB = 0x00;
                state = lock;

        }
}
