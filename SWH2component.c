/*
 CITS3231 Project 2013
 Name(s):           Alvar Ongkowidjaja, Danielle Page and Michael Piotrowski
 Student number(s): 20841563, 20753669, 20738843
 Date:              25 October 2013
 */

/*
 * This is a simple set of functions for Software House 2
 * They are intended for demonstration purposes only, apart from the authcheck and s1auth functions
 * Each individual function in this component does an authentication check.
 * This leaves authentication theoretically out of the developer's control
 * They also can't steal a single function of the component.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void s2auth(void)
{

    char *result;
    int ok;

    /* Read in the user's license and encrypt it,
       passing the expected password in as the salt. */
    result = crypt(getpass("License key for Software House 2:"), s2encrypted_form_global);

    /* Test the result. */
    ok = strcmp (result, s2encrypted_form_global) == 0;
    if (ok == 1)
    {
        s2authnum = 1;
    }


    puts(ok ? "Access granted.\n" : "Access denied.\n");
    return;
}

int s2authcheck()
{
    if (s2authnum != 1)
    {
        s2auth();
    }
    return s2authnum;
}

//Returns one character
char yReturnLetter(void)
{
    int c = s2authcheck();
    if (c == 1)
    {
        char c = 'c';
        return c;
    }
}

//Prints to terminal a simple greeting
void ySimpleGreeting(void)
{
    int c = s2authcheck();
    if (c == 1)
    {
        printf("This function was made by Software House 2. We are very proud of it.\n");
    }
}

int yMultiplication(int r)
{
    int c = s2authcheck();
    if (c == 1)
    {
        int h = r * 7;
        printf("This function multiplies %d by 7 and returns the result.\n", r);
        return h;
    }
}
