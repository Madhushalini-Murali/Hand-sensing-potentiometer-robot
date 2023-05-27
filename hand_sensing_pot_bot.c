#include<avr/io.h>
#include<util/delay.h>
void initialise()
{
	ADCSRA=ADCSRA|(0b00000001<<ADEN); // Enable ADC
	ADCSRA=ADCSRA|(0b00000001<<ADPS2);//Sampling rate select
	ADMUX|=(0b00000001<<REFS0);// Voltage reference
}
int read()
{
	int p=0b00000011; 
	ADMUX=ADMUX|p; // Input pin
	ADCSRA=ADCSRA|(0b00000001<<ADSC); //Start of Conversion
	while(ADCSRA&(0b00000001<<ADIF)==0); // Until conversion stops
	ADCSRA=ADCSRA|(0b00000001<<ADIF);// Clearing ADIF pin
	return(ADC);
}	
	
void main()
{
    DDRD=0b00000000;
	DDRB=0b11111111;
	PORTD=0b11111111;
	initialise();
	_delay_ms(50);
	unsigned int a,p,T,TON,TOFF;
	int c;
	while(1)
	{
		p=read();
		a=p/40;
		T=25.6;
		TOFF=a;
		TON=T-TOFF;
		c=PIND;
		if(c==0b11111110)
		{
			PORTB=0b00001010;
			_delay_ms(TON);
			PORTB=0b00000000;
			_delay_ms(TOFF);
	    }
		else
		{
			PORTB=0b00001010;
		    
		}
	}
}
	