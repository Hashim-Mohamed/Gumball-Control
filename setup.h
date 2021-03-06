
//defining adressess for Port B and D
// Start up adressess
#define RCGCGPIO (*((unsigned long *) 0x400FE608)) 
#define PRGPIO (*((unsigned long *) 0x400FEA08))
#define RCGCTIMER (*((unsigned long *) 0x400FE604)) 
#define PRTIMER (*((unsigned long *) 0x400FEA04))
//(For motors) Config GPIO Port B adressess (0x40005000)
#define PORTB_AFSEL (*((unsigned long *) 0x40005420))
#define PORTB_DEN (*((unsigned long *) 0x4000551C))
#define PORTB_PCTL (*((unsigned long *) 0x4000552C))
#define PORTB_DIR (*((unsigned long *) 0x40005400))
//(For keypad) Config GPIO Port D adressess (0x40007000)
#define PORTD_DIR (*((unsigned long *) 0x40007400))
#define PORTD_DEN (*((unsigned long *) 0x4000751C))
#define PORTD_PDR (*((unsigned long *) 0x40007514))
#define PORTD_DATA (*((unsigned long *) 0x400073FC))
//(For Display) Config GPIO Port E adressess (0x40024000)
#define PORTE_DIR (*((unsigned long *) 0x40024400))
#define PORTE_DEN (*((unsigned long *) 0x4002451C))
#define PORTE_DATA (*((unsigned long *) 0x400243FC))
#define PORTE_AFSEL (*((unsigned long *) 0x40024420))
#define PORTE_PCTL (*((unsigned long *) 0x4002452C))
//(For LEDs) Config GPIO Port C adressess (0x40006000)
#define PORTC_DIR (*((unsigned long *) 0x40006400))
#define PORTC_DEN (*((unsigned long *) 0x4000651C))
#define PORTC_DATA (*((unsigned long *) 0x400063FC))
//TIMERS (Timer base 0x400FE000, Timer0: 0x40030000, Timer1: 0x40031000)
#define TIMER0_CTL (*((unsigned long *) 0x4003000C))// PWM at PB 6 and 7
#define TIMER0_CFG (*((unsigned long *) 0x40030000))
#define TIMER0_TAMR (*((unsigned long *) 0x40030004))//PWM PB6
#define TIMER0_TAPR (*((unsigned long *) 0x40030038))
#define TIMER0_TAILR (*((unsigned long *) 0x40030028))
#define TIMER0_TAPMR (*((unsigned long *) 0x40030040))
#define TIMER0_TAMATCH (*((unsigned long *) 0x40030030))
#define TIMER0_TBMR (*((unsigned long *) 0x40030008))//PWM PB7
#define TIMER0_TBPR (*((unsigned long *) 0x4003003C))
#define TIMER0_TBILR (*((unsigned long *) 0x4003002C))
#define TIMER0_TBPMR (*((unsigned long *) 0x40030044))
#define TIMER0_TBMATCH (*((unsigned long *) 0x40030034))
#define TIMER1_CTL (*((unsigned long *) 0x4003100C))// PWM at PB 4 and 5
#define TIMER1_CFG (*((unsigned long *) 0x40031000))
#define TIMER1_TAMR (*((unsigned long *) 0x40031004))//PWM PB4
#define TIMER1_TAPR (*((unsigned long *) 0x40031038))
#define TIMER1_TAILR (*((unsigned long *) 0x40031028))
#define TIMER1_TAPMR (*((unsigned long *) 0x40031040))
#define TIMER1_TAMATCH (*((unsigned long *) 0x40031030))
#define TIMER1_TBMR (*((unsigned long *) 0x40031008))//PWM PB5
#define TIMER1_TBPR (*((unsigned long *) 0x4003103C))
#define TIMER1_TBILR (*((unsigned long *) 0x4003102C))
#define TIMER1_TBPMR (*((unsigned long *) 0x40031044))
#define TIMER1_TBMATCH (*((unsigned long *) 0x40031034))
#define TIMER2_CTL (*((unsigned long *) 0x4003200C))// PWM at PB 0 and 1
#define TIMER2_CFG (*((unsigned long *) 0x40032000))
#define TIMER2_RIS  (*((unsigned long *) 0x4003201C))// Sees if PB1 is high or if PB0 is high
#define TIMER2_TAMR (*((unsigned long *) 0x40032004))//PWM PB0
#define TIMER2_TAPR (*((unsigned long *) 0x40032038))
#define TIMER2_TAILR (*((unsigned long *) 0x40032028))
#define TIMER2_TAPMR (*((unsigned long *) 0x40032040))
#define TIMER2_TAMATCH (*((unsigned long *) 0x40032030))
#define TIMER2_TBMR (*((unsigned long *) 0x40032008))//PWM PB1
#define TIMER2_TBPR (*((unsigned long *) 0x4003203C))
#define TIMER2_TBILR (*((unsigned long *) 0x4003202C))
#define TIMER2_TBPMR (*((unsigned long *) 0x40032044))
#define TIMER2_TBMATCH (*((unsigned long *) 0x40032034))
// Uart Uart7 base: 0x40013000
//#define RCGCUART (*((unsigned long *) 0x400FE618))
//#define PRUART (*((unsigned long *) 0x400FEA18))
//#define UART7_DR (*((unsigned long *) 0x400133FC))
//#define UART7_FR (*((unsigned long *) 0x40013018))
//#define UART7_IBRD (*((unsigned long *) 0x40013024))
//#define UART7_FBRD (*((unsigned long *) 0x40013028))
//#define UART7_LCRH (*((unsigned long *) 0x4001302C))
//#define UART7_CTL (*((unsigned long *) 0x40013030))
//	
	
int Delay(void)
{
	int i,n ; //Does nothing 1 million times
	n= 0x4C4B40;
	for(i=0;i<=n;i++)
	{
			__nop();
		
	}

	return(0);
}
int RunMotor1(void)
{
	int i,n, x;
	i = 0xE666;
	n = i + 0x199A; //last PWM value 10% difference
	PORTC_DATA = PORTC_DATA | 0x10; //signals that motor 1 is on by activating led (PC4)
	while (i>=0x3333) //until 70% is reached
	{
		TIMER0_CTL = TIMER0_CTL & ~ 0x1;
		TIMER0_TAMATCH = TIMER0_TAMATCH & ~ n;
		TIMER0_TAMATCH = TIMER0_TAMATCH | i;//10%
		TIMER0_CTL = TIMER0_CTL | 0x1;
		Delay();
		i = i - 0x199A; // next match
    n = i + 0x199A; // previous match		
	}	
	x= i+ 0x199A;
	while (x<= 0xE666)// goes back to 0
	{
		TIMER0_CTL = TIMER0_CTL & ~ 0x1;
		TIMER0_TAMATCH = TIMER0_TAMATCH & ~ n;
		TIMER0_TAMATCH = TIMER0_TAMATCH | x;//10%
		TIMER0_CTL = TIMER0_CTL | 0x1;
		Delay();
		n = x;
		x = x + 0x199A;
	}
	TIMER0_CTL = TIMER0_CTL & ~ 0x1;
	PORTC_DATA = PORTC_DATA & ~ 0x10;// deactivates led when motor is done
	return(0);
}	
int RunMotor2(void)
{
	int i,n, x;
	i = 0xE666;
	n = i + 0x199A; //last PWM value 10% difference
	PORTC_DATA = PORTC_DATA | 0x20; //PC5 activates column 2 led
	while (i>=0x3333) //until 70% is reached
	{
		TIMER0_CTL = TIMER0_CTL & ~ 0x100;
		TIMER0_TBMATCH = TIMER0_TBMATCH & ~ n;
		TIMER0_TBMATCH = TIMER0_TBMATCH | i;//10%
		TIMER0_CTL = TIMER0_CTL | 0x100;
		Delay();
		i = i - 0x199A; // next match
    n = i + 0x199A; // previous match		
	}	
	x= i+ 0x199A;
	while (x<= 0xE666)// goes back to 0
	{
		TIMER0_CTL = TIMER0_CTL & ~ 0x100;
		TIMER0_TBMATCH = TIMER0_TBMATCH & ~ n;
		TIMER0_TBMATCH = TIMER0_TBMATCH | x;//10%
		TIMER0_CTL = TIMER0_CTL | 0x100;
		Delay();
		n = x;
		x = x + 0x199A;
	}
	TIMER0_CTL = TIMER0_CTL & ~ 0x100;
	PORTC_DATA = PORTC_DATA & ~ 0x20;
	return(0);
}	
int RunMotor3(void)
{
	int i,n, x;
	i = 0xE666;
	n = i + 0x199A; //last PWM value 10% difference
	PORTC_DATA = PORTC_DATA | 0x40; //PC6 activates column 3 led
	while (i>=0x3333) //until 70% is reached
	{
		TIMER1_CTL = TIMER1_CTL & ~ 0x1;
		TIMER1_TAMATCH = TIMER1_TAMATCH & ~ n;
		TIMER1_TAMATCH = TIMER1_TAMATCH | i;//10%
		TIMER1_CTL = TIMER1_CTL | 0x1;
		Delay();
		i = i - 0x199A; // next match
    n = i + 0x199A; // previous match		
	}	
	x= i+ 0x199A;
	while (x<= 0xE666)// goes back to 0
	{
		TIMER1_CTL = TIMER1_CTL & ~ 0x1;
		TIMER1_TAMATCH = TIMER1_TAMATCH & ~ n;
		TIMER1_TAMATCH = TIMER1_TAMATCH | x;//10%
		TIMER1_CTL = TIMER1_CTL | 0x1;
		Delay();
		n = x;
		x = x + 0x199A;
	}
	TIMER1_CTL = TIMER1_CTL & ~ 0x1;
	PORTC_DATA = PORTC_DATA & ~ 0x40;
	return(0);
}	
int RunMotor4(void)
{
	int i,n, x;
	i = 0xE666;
	n = i + 0x199A; //last PWM value 10% difference
	PORTC_DATA = PORTC_DATA | 0x80; //PC7 activates column 4 led
	while (i>=0x3333) //until 70% is reached
	{
		TIMER1_CTL = TIMER1_CTL & ~ 0x100;
		TIMER1_TBMATCH = TIMER1_TBMATCH & ~ n;
		TIMER1_TBMATCH = TIMER1_TBMATCH | i;//10%
		TIMER1_CTL = TIMER1_CTL | 0x100;
		Delay();
		i = i - 0x199A; // next match
    n = i + 0x199A; // previous match		
	}	
	x= i+ 0x199A;
	while (x<= 0xE666)// goes back to 0
	{
		TIMER1_CTL = TIMER1_CTL & ~ 0x100;
		TIMER1_TBMATCH = TIMER1_TBMATCH & ~ n;
		TIMER1_TBMATCH = TIMER1_TBMATCH | x;//10%
		TIMER1_CTL = TIMER1_CTL | 0x100;
		Delay();
		n = x;
		x = x + 0x199A;
	}
	TIMER1_CTL = TIMER1_CTL & ~ 0x100;
	PORTC_DATA = PORTC_DATA & ~ 0x80; //Led deactivates at end of function
	return(0);
}	
	
int setup(void)
{
//int i = 0xE666;
// Starts up GPIO Ports B and D and E and C
	RCGCGPIO = RCGCGPIO | 0x1E;
	
	while( (PRGPIO & 0x1E) != 0x1E){};
	
// Configure Port B (& ~ is bit clear)
//////////////////////////////////// PWM MOTOR TIMERS ////////////////////////////////////////////////////////////////////////////
	PORTB_DIR = PORTB_DIR | 0xF0 ; // Pins 4,5,6,7 are outputs 
	PORTB_AFSEL = PORTB_AFSEL | 0xF0 ; //PINS 4,5,6,7 of port B will be PWM signals for the motors 
	PORTB_DEN = PORTB_DEN | 0xF0; 
	PORTB_PCTL = PORTB_PCTL | 0x77770000;// Now port B, pins 4,5,6,7 should be PWM signals 2,3 are normal for now

// Start up timers 0,1 aka bits 0,1 
	RCGCTIMER = RCGCTIMER | 0x3 ;
	
	while( (PRTIMER & 0x3) !=0x3) {};	

// configure timer 0 (PB6=A) (PB7=B)
	TIMER0_CTL = TIMER0_CTL & ~ 0x101 ; // Timers 0 A(0x1) and B(0x100) are disabled
	TIMER0_CTL = TIMER0_CTL & ~ 0x4040; // PWM signal is NOT inverted
	TIMER0_CFG = TIMER0_CFG | 0x4;// Two 16 bit PWM signals
// For Port B pin 6 (TIMER 0A)	
	TIMER0_TAMR = TIMER0_TAMR | 0xA; // Periodic PWM output
	TIMER0_TAPR = TIMER0_TAPR | 0x100; // Prescale
	TIMER0_TAILR = TIMER0_TAILR | 0xFFFF; // Preload
	TIMER0_TAMATCH = TIMER0_TAMATCH & ~ 0xFFFF; //For some reason sets to FFFF must clear match value
	TIMER0_TAPMR = TIMER0_TAPMR | 0x100; // Match prescale value (I think this is the prescale value?)
// For Port B Pin 7 (TIMER 0B) (Same configuration as before)
	TIMER0_TBMR = TIMER0_TBMR | 0xA; 
	TIMER0_TBPR = TIMER0_TBPR | 0x100; 
	TIMER0_TBILR = TIMER0_TBILR | 0xFFFF; 
	TIMER0_TBMATCH = TIMER0_TBMATCH & ~ 0xFFFF;
	TIMER0_TBPMR = TIMER0_TBPMR | 0x100; 
// configure timer 1 (PB4=A) (PB5=B)
	TIMER1_CTL = TIMER1_CTL & ~ 0x101 ; // Timers 1 A(0x1) and B(0x100) are disabled
	TIMER1_CTL = TIMER1_CTL & ~ 0x4040; // PWM signal is NOT inverted
	TIMER1_CFG = TIMER1_CFG | 0x4;// Two 16 bit PWM signals
// For Port B Pin 4 (TIMER 1A) (Same configuration as before)
	TIMER1_TAMR = TIMER1_TAMR | 0xA; 
	TIMER1_TAPR = TIMER1_TAPR | 0x100;
	TIMER1_TAILR = TIMER1_TAILR | 0xFFFF; 
	TIMER1_TAMATCH = TIMER1_TAMATCH & ~ 0xFFFF; 
	TIMER1_TAPMR = TIMER1_TAPMR | 0x100;
// For Port B Pin 5 (TIMER 1B) (Same configuration as before)
	TIMER1_TBMR = TIMER1_TBMR | 0xA; 
	TIMER1_TBPR = TIMER1_TBPR | 0x100; 
	TIMER1_TBILR = TIMER1_TBILR | 0xFFFF; 
	TIMER1_TBMATCH = TIMER1_TBMATCH & ~ 0xFFFF; 
	TIMER1_TBPMR = TIMER1_TBPMR | 0x100;	
////////////////////Test/////////////////////////////////
	//RunMotor1(); // Enable PWM PB6 (TIMER 0A)
	//RunMotor2(); // Enable PWM PB7 (TIMER 0B)
	//RunMotor3(); // Enable PWM PB4 (TIMER 1A)
	//RunMotor4(); // Enable PWM PB5 (TIMER 1B)
//////////////////////////////////////////////	KEYPAD PINS //////////////////////////////////////////////////////////////////////
	// Port D pin 3 will be an output to the keypad rows and 0,1,2 are inputs from the keypad columns 6 reads the other row
	PORTD_DIR = PORTD_DIR | 0x48; // pins 3 and 6  are  outputs
	PORTD_DIR = PORTD_DIR & ~ 0x7;// pins 0,1,2 are definitely inputs
	PORTD_PDR = PORTD_PDR | 0x7; // If switches are pressed pins 0,1,2 will return high logic and pin 6 reads not gate output
	PORTD_DEN = PORTD_DEN | 0x4F; // pins (0,1,2,3,6) are digitally enabled
	
//////////////////////////////// LED Control /////////////////////////////////////////////////////////////////////////////////////
	//Use port C to control the leds
	PORTC_DIR = PORTC_DIR | 0xF0; // pins 4,5,6,7 are outputs
	PORTC_DEN = PORTC_DEN | 0xF0; // digitally enabled pins 4,5,6,7
	PORTC_DATA = PORTC_DATA & ~0xD;// clears all pins for sure 
	//PORTE_DATA = PORTE_DATA | 0x2;  //PE1 activates column 1 led
	//PORTE_DATA = PORTE_DATA | 0x4; //PE2 activates column 2 led
	//PORTE_DATA = PORTE_DATA | 0x8; //PE3 activates column 3 led
	//PORTE_DATA = PORTE_DATA | 0x10; //PE4 activates column 4 led
//////////////////////////////// UART terra term (incomplete)////////////////////////////////////////////////////////////////////////////////
//  PORTE_DEN = PORTE_DEN | 0x3;
//	PORTE_AFSEL = PORTE_AFSEL | 0x3;
//	PORTE_PCTL = PORTE_PCTL | 0x00000011; //pins 0 and 1 are uart
//	RCGCUART = RCGCUART | 0x80;// start up uart7
//	
//	while( (PRUART & 0x80) != 0x80){};
//	UART7_CTL = UART7_CTL & ~0x1; // disable uart
//  UART7_IBRD = UART7_IBRD | 0x1A; //Baudrate of 38400
//	UART7_FBRD = UART7_FBRD | 0x3;
//	UART7_LCRH = UART7_LCRH | 0x48;// 7 bits, no parity, 2 stop bits prescale 16
//	UART7_CTL = UART7_CTL | 0x1;// re enable uart
//		
//	
//while(UART7_FR == 0x20){};
////	if (UART7_FR ==0){
//			UART7_DR = UART7_DR | 'H';
//	//}
//		

return(0);
}




