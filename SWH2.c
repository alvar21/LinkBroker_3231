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
 *
 * SWH2.c is a copy of SWH.c with variable names changed to reflect a different software house
 * Please see SWH.c for comments.
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
 
int
genpass(char *unencrypted_license)
{
    unsigned long seed[2];
    char salt[] = "$1$........";
    const char *const seedchars =
        "./0123456789ABCDEFGHIJKLMNOPQRST"
        "UVWXYZabcdefghijklmnopqrstuvwxyz";
    char *password;
    int i;
    FILE *passfile = fopen("SWH2deliverable.c", "a");

    /* Generate a (not very) random seed.
       You should do it better than this... */
    seed[0] = time(NULL);
    seed[1] = getpid() ^ (seed[0] >> 14 & 0x30000);

    /* Turn it into printable characters from `seedchars'. */
    for (i = 0; i < 8; i++)
        salt[3 + i] = seedchars[(seed[i / 5] >> (i % 5) * 6) & 0x3f];

    /* Take the unencrypted license and encrypt it. */
    password = crypt(unencrypted_license, salt);

    /* Print the results to passfile. */
    fprintf(passfile, "\"%s\";\n", password);
    fclose(passfile);
    return 0;
}

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
    FILE *f = fopen("SWH2licenses.txt", "r");
    char buff[256];
    int found = 0;
    FILE *usedlicenses = fopen("SWH2usedlicenses.txt", "r");
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
    FILE *f = fopen("SWH2usedlicenses.txt", "a");
    fprintf(f, "%s", license);
    fclose(f);
}

int main(int argc, char **argv)
{
    if (checkLicense(argv[1]) == 1)
    {
        addUsed(argv[1]);
        append_file("SWH2deliverable.c", "s2appendtemplate.c");
        genpass(getpass("License key:\n"));
        append_file("SWH2deliverable.c", "SWH2component.c");
        pid_t cpid = fork();
        if (cpid == 0)
        {
            static char *argv1[] = {"gcc", "-c", "SWH2deliverable.c", "-lcrypt", "-o", "SWH2deliverable.o"};
            execv("/usr/bin/gcc", argv1);
            //static char *argv2[]={"gcc", "SWH2deliverable.o", "-lcrypt", "-o", "SWH2deliverable"};
            //execv("/usr/bin/gcc", argv2);
            exit(127);
        }
        else
        {
            waitpid(cpid, 0, 0);
        }
    }
    return 0;
}
