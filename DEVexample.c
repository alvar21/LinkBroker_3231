/*
 CITS3231 Project 2013
 Name(s):           Alvar Ongkowidjaja, Danielle Page and Michael Piotrowski
 Student number(s): 20841563, 20753669, 20738843
 Date:              25 October 2013
 */

/*
 * This is a simple demonstration program for the Developer
 * It uses components from two known software houses.
 */

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




