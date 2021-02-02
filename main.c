
#include "setup.h"

/********************* MAIN ****************************/
int main(void)
{	
  setup();

	while (1){//Controlling the columns via the keypad where RIC=0x1 is PB0 is high and RIC=0x100 is PB1
	//For keypad PD6 for row 0(pin2), PD0 pin3(column 0),PD1 pin1(column 1),PD2 pin5(column2),PD3 pin7(row 1)
		PORTD_DATA = PORTD_DATA & ~0x8;// stops checking 2nd row(keypad)
		PORTD_DATA = PORTD_DATA | 0x40;// starts checking top row(keypad)
		if(PORTD_DATA == 0x41){//(pin D3 and 6 and pin D0 are high) would be keypad key 1
			RunMotor1(); // Enable PWM PB6 (TIMER 0A) corresponding led on PE1
		}
		else if (PORTD_DATA == 0x42){//(pin D3 and pin D1 are high)would be keypad key 2
			RunMotor2(); // Enable PWM PB7 (TIMER 0B)	corresponding led on PE2	
		}
		else if (PORTD_DATA == 0x44 ){//(pin D3 and pin D2 are high)would be keypad key 3
			RunMotor3(); // Enable PWM PB4 (TIMER 1A) corresponding led on PE3
		}
		PORTD_DATA = PORTD_DATA & ~0x40;//stops checking top row
		PORTD_DATA = PORTD_DATA | 0x8;// starts checking 2nd row
		if (PORTD_DATA == 0x9 ){//(pin D3 and pin D6 are high)would be keypad key 4
			RunMotor4(); // Enable PWM PB5 (TIMER 1B) corresponding led on PE4
		}
	}
}


