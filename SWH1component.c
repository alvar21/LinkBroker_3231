/*
 CITS3231 Project 2013
 Name(s):           Alvar Ongkowidjaja, Danielle Page and Michael Piotrowski
 Student number(s): 20841563, 20753669, 20738843
 Date:              25 October 2013
 */

/*
 * This is a simple set of functions for Software House 1
 * They are intended for demonstration purposes only, apart from the authcheck and s1auth functions
 * Each individual function in this component does an authentication check.
 * This leaves authentication theoretically out of the developer's control
 * They also can't steal a single function of the component.
 */

//Authenticate the current user
void s1auth(void)
{

    char *result;
    int ok;

    /* Read in the user's license and encrypt it,
       passing the expected password in as the salt. */
    result = crypt(getpass("License key for Software House 1:"), s1encrypted_form_global);

    /* Test the result. */
    ok = strcmp (result, s1encrypted_form_global) == 0;
    if (ok == 1)
    {
        s1authnum = 1;
    }


    puts(ok ? "Access granted.\n" : "Access denied.\n");
    return;
}

//Check whether or not we have authenticated the current user.
int s1authcheck()
{
    if (s1authnum != 1)
    {
        s1auth();
    }
    return s1authnum;
}

// Prints a string to the terminal
void xPrintGreeting(void)
{
    int c = s1authcheck();
    if (c == 1)
    {
        printf("This simple function is part of Software House 1's components.\n");
    }
}

//Sums h and y, printing the result to the terminal
void xSimpleArithmetic(int h, int y)
{
    int c = s1authcheck();
    if (c == 1)
    {
        int x = h + y;
        printf("The sum of %d and %d is %d.\n", h, y, x);
    }
}

//Multiplies h by 3, prints its purpose to the terminal, then returns j
int xProduct3(int h)
{
    int c = s1authcheck();
    if (c == 1)
    {
        int j = h * 3;
        printf("This function returns %d multiplied by 3 to the calling program.\n", h);
        return j;
    }
}

