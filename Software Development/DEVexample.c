#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern password;
extern void xPrintGreeting();
extern void xSimpleArithmetic(int, int);
extern int xProduct3(int);
extern char yReturnLetter();
extern void ySimpleGreeting();
extern int yMultiplication(int);
/**
** This is a simple demonstration program for the Developer
** It uses components from two known software houses.
** Written by Danielle Page 20753669 Alvar Ongkowidjaja 20845163 Michael Piotrowski 20738843
**/

void devGreetings(void)
{
	printf("Greetings from the Developer.\n");
	}
	
int main(void)
{
	devGreetings();
	xPrintGreeting();
	ySimpleGreeting();
	xSimpleArithmetic(5, 6);
	char f;
	f = yReturnLetter();
	int r;
	r = xProduct3(12);
	int y;
	y = yMultiplication(77);
	printf("f = %c, r = %d, y = %d\n", f, r, y);
	return 1;
}
	
	
	
	
