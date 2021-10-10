#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA  =0x00;
        PORTA = 0xFF;
        DDRC = 0xFF;
        PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
        tick();
    }
    return 1;
}

enum States {start, base, reset, plus, minus} state;

void tick(){


        switch (state){

                case start:
                        PORTC = 0x07;
                        state = base;
                        break;

                case base:
                        if((PINA & 0x01) == 0x01){
                                state = plus;
                        }
                        else if((PINA & 0x02)== 0x02){
                                state = minus;
                        }

                        else if((PINA & 0x03) == 0x03){
                                state = reset;
                        }
                        else{
                                state = base;
                        }
                        break;

                case plus:
                        if (PORTC < 0x09){
                                PORTC = PORTC + 0x01;
                        }

                        if ((PINA & 0x01)== 0x01){
                                state = plus;
                        }
                        else {
                                state = base;
                        }
                        break;

                case minus:
                        if(PORTC > 0x00) {
                                PORTC = PORTC - 0x01;
                        }

                        if((PINA & 0x02) == 0x02){
                                state = minus;
                        }

                        else {
                                state = base;
                        }

                        break;


                case reset:
                        PORTC = 0x00;
                        if((PINA & 0x03) == 0x03){
                                state = reset;
                        }
                        else{
                                state = base;
                        }
                        break;

                default:
                        PORTC = 0x07;
                        state = start;
                        break;

        }



}
