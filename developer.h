/*
 CITS3231 Project 2013
 Name(s):           Alvar Ongkowidjaja, Danielle Page and Michael Piotrowski
 Student number(s): 
 Date:              October 2013
 */

//
// developer.h
//
//


#ifdef __linux__
	#define _POSIX_C_SOURCE 200809L // for strdup to work
	#include <linux/limits.h>
#elif __APPLE__
	#include <limits.h>
#endif

#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utime.h>
#include <ctype.h>

// flags for fileType.c
#define ISFILE		0
#define ISDIR		1
#define DNE 		2

// flags for largerFile.c
#define FILE1		0 // first file is larger
#define FILE2		1 // second file is larger
#define SAMESIZE	2

// flag for mostRecent.c
#define SAMEMTIME 	2

#define OPTLIST "lmvi:c" // for optarg to work, the option which requires it has to have ":" behind it

// output directory argument for mergedirs.c
#define OUTPUTDIR argv[argc-1]

extern char *filesummary(char*);

extern int  fileType	(char*);
extern int  largerFile	(char*, char*);
extern int  mostRecent	(char*, char*);

extern void copyFile	(char*, char*);
extern void listDir     (char*, char*);

// flags for command line options
bool cflag, dflag, iflag, lflag, mflag, vflag;

// pattern associated with the -i command line option
char *pattern;
