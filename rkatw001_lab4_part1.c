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
        Tick();
    }
    return 1;
}







enum States {start, B0released, B1Pressed, B1Release, B0Pressed} state;

void tick(){


        switch (state){

        case start:
                state = B0released;
                PORTB = 0x01;

                break;

        case B0released:
                if((PINA & 0x01)== 0x01){
                        state = B1Pressed;
                }
                else{
                state = B0released;
                }
                break;

        case B1Pressed:

                PORTB = 0x02;

                if((PINA & 0x01)!= 0x01){
                        state = B1Release;
                }

                else {
                        state = B1Pressed;
                }

                break;


        case B1Release:

                if((PINA & 0x01) == 0x01){
                        state = B0Pressed;
                }

                else {

                        state = B1Release;

                }

                break;


        case B0Pressed:

                PORTB = 0x01;

                if ((PINA & 0x01) != 0x01){
                        state = B0released;
                }

                else{
                        state = B0Pressed;
                }

                break;

        default:
                state = start;
                PORTB = 0x01;
        break;


        }
}
