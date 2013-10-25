#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypt.h>

/**
** This template is copied, then appended to by the software house, firstly by the encrypted license key
** and secondly by the software component. 
** Written by Alvar Ongkowidjaja 20845163 Michael Piotrowski 20738843 Danielle Page 20753669
**/

//Authentication check; 0 for unauthenticated, 1 for authenticated
int s1authnum = 0;

//This variable holds the encrypted licence key
char *s1encrypted_form_global = 
