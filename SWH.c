/*
 CITS3231 Project 2013
 Name(s):           Alvar Ongkowidjaja, Danielle Page and Michael Piotrowski
 Student number(s): 20841563, 20753669, 20738843
 Date:              25 October 2013
 */

/*
 * This file contains the main functionality for the software house.
 * It creates a copy of the software component, generates an authentication key from unencrypted license
 * and compiles it into an object file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

//generate an authentication key
int genpass(char *unencrypted_license)
{
    unsigned long seed[2];
    char salt[] = "$1$........";
    const char *const seedchars =
        "./0123456789ABCDEFGHIJKLMNOPQRST"
        "UVWXYZabcdefghijklmnopqrstuvwxyz";
    char *password;
    int i;
    FILE *passfile = fopen("SWH1deliverable.c", "a");

    //Generate a seed based on system time
    seed[0] = time(NULL);
    seed[1] = getpid() ^ (seed[0] >> 14 & 0x30000);

    //Get printable characters
    for (i = 0; i < 8; i++)
        salt[3 + i] = seedchars[(seed[i / 5] >> (i % 5) * 6) & 0x3f];

    //encrypt the license
    password = crypt(unencrypted_license, salt);

    //Print the results to the passfile and close it
    fprintf(passfile, "\"%s\";\n", password);
    fclose(passfile);
    return 0;
}

//Append one file with the contents of another.
void append_file(char *appendee, char *appendage)
{
    FILE *f1 = fopen(appendee, "a");
    FILE *f2 = fopen(appendage, "r");
    char buff[BUFSIZ];

    while (fgets(buff, BUFSIZ, f2) != NULL)
    {
        fprintf(f1, "%s", buff);
    }

    fclose(f1);
    fclose(f2);
}

//Check if we have this license
int checkLicense(char *license)
{
    FILE *f = fopen("SWH1licenses.txt", "r");
    char buff[256];
    int found = 0;
    FILE *usedlicenses = fopen("SWH1usedlicenses.txt", "r");
    int ok = 0;
    //test if we have this license
    while (fgets(buff, 256, f) != NULL)
    {
        ok = strcmp (license, buff) == 0;
        if (ok == 1)
        {
            found = 1;
        }
    }
    fclose(f);

    //test if this license has already been used
    while (fgets(buff, 256, usedlicenses) != NULL)
    {
        ok = strcmp (license, buff) == 0;
        if (ok == 1)
        {
            found = 0;
        }
    }
    fclose(usedlicenses);
    return found;
}

//Add license to used licenses file.
void addUsed(char *license)
{
    FILE *f = fopen("SWH1usedlicenses.txt", "a");
    fprintf(f, "%s", license);
    fclose(f);
}

//Takes an unencrypted license as argument
int main(int argc, char **argv)
{
    if (checkLicense(argv[1]) == 1)
    {
        addUsed(argv[1]);
        //create SWH1deliverable.c with the contents from appendtemplate
        append_file("SWH1deliverable.c", "appendtemplate.c");
        //genpass(getpass("License key:\n"));
        //take an unencrypted license and make authentication key
        genpass(argv[1]);
        //append the component to our deliverable
        append_file("SWH1deliverable.c", "SWH1component.c");
        pid_t cpid = fork();
        if (cpid == 0)
        {
            //compile source code into object file with -lcrypt
            static char *argv1[] = {"gcc", "-c", "SWH1deliverable.c", "-lcrypt", "-o", "SWH1deliverable.o"};
            execv("/usr/bin/gcc", argv1);
            exit(127);
        }
        else
        {
            waitpid(cpid, 0, 0);
        }
    }

    return 0;
}
