***README***

Directory structure:
SWH1: appendtemplate.c
	  SWH.c
	  SWH1component.c
	  SWH1licenses.txt
	  SWH1usedlicenses.txt

SWH2: s2appendtemplate.c
	  SWH2.c
	  SWH2component.c
	  SWH2licenses.txt
	  SWH2usedlicenses.txt
	  
linkbroker_software_support.c

Developer: SWH1licenses.txt
		   SWH2licenses.txt
		   DEVexample.c
		   dev_compile_function.c
		 

***IMPORTANT***
SWH.c and SWH2.c must be linked with the crypt library manually. A sample gcc compilation would be
	$ gcc SWH.c -lcrypto -o swh
	$ gcc SWH2.c -lcrypto -o swh2

Software houses' code are exact copies, except for a few file and function names changed. This is necessary for implementing authentication functions.

If you wish to run the software house code again, it is necessary to delete the following files:
	SWH1deliverable.c SWH1deliverable.o SWH2deliverable.c SWH2deliverable.o
	
To reset license uses, simply erase all content in used licenses.

Software house main functions take unencrypted license key as the only argument and produce 
an object file in the working directory ready to send.

The linkbroker support function takes in the names of object files (including the developer's file)
and produces an executable file in the working directory, ready to send. 

The DEVexample file is merely a test program. It requires no special compilation options.
	$ gcc -c DEVexample 

	will give you the .o file to send through to linkbroker.
 
The dev compile function will take the name of a c file and compile it using the above gcc call.
The .o file will be in the working directory.

Because of the dev compile and linkbroker support functions, please make sure the header files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
are included.
