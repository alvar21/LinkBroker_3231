/*
 CITS3231 Project 2013
 Name(s):           Alvar Ongkowidjaja, Danielle Page and Michael Piotrowski
 Student number(s): 20841563, 20753669, 20738843 
 Date:              25 October 2013
 */

 /*
  * This template is copied, then appended to by the software house, firstly by the encrypted license key
  * and secondly by the software component. 
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypt.h>

//Authentication check; 0 for unauthenticated, 1 for authenticated
int s1authnum = 0;

//This variable holds the encrypted licence key
char *s1encrypted_form_global = 
