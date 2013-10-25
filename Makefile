# CITS3231 Project 2013
# Name(s):           Alvar Ongkowidjaja, Danielle Page and Michael Piotrowski
# Student number(s): 20841563, 20753669, 20738843
# Date:              25 October 2013

PROJECT =  developer
OBJ     =  developer.o softwareh.o SWH.o SWH2.o appendtemplate.o s2appendtemplate.o SWH1component.o\
SWH2component.o linkbroker_software_support.o DEVexample.o dev_compile_function.o
        

C99     =  gcc -std=c99
CFLAGS  =  -Wall -pedantic -lssl -lcrypto

$(PROJECT) : $(OBJ)
		$(C99) $(CFLAGS) -o $(PROJECT) $(OBJ)

%.o : %.c
	$(C99) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ)