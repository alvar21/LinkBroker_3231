/*
 CITS3231 Project 2013
 Name(s):           Alvar Ongkowidjaja, Danielle Page and Michael Piotrowski
 Student number(s): 
 Date:              October 2013
 */

//
//  developer.c
//
//

#include "developer.h"

static char *progname;

int main(int argc, char *argv[]) {
    lflag = false;
    mflag = false;
    vflag = false;
    iflag = false;
    cflag = false;
    dflag = false;	// no command line options supplied flag
    
    progname = argv[0];
	
    int opt;
    opterr = 0;
    
    while ((opt = getopt(argc, argv, OPTLIST)) != -1) {
        switch (opt) {
            case 'l':
                lflag = true;
                break;
            case 'm':
                mflag = true;
                break;
            case 'v':
                vflag = true;
                break;
            case 'i':
                iflag = true;
                pattern = strdup(optarg);
                break;
            case 'c':
                cflag = true;
                break;
            default:
                argc = -1;
        }
    }
	
	// If no options are provided then the default is '-m'.
	if (!lflag && !mflag && !vflag && !iflag && !cflag) {
	    mflag = !mflag;
	    dflag = !dflag;
	}
	
	// The options -l -m -i -c are to be used seperately.
	if (lflag + mflag + iflag + cflag > 1) {
	    fprintf(stderr, "-l -m -i -c are mutually exclusive. Please choose one to use.\n");
	    fprintf(stderr, "Usage: %s [-l|-m|-v|-i|-c] indirectory1 [indirectory2 ...] outdirectory\n", progname);
	    exit(EXIT_FAILURE);
	}
	
	// Program exits if there is not at least 1 input and 1 output directory.
	// optind is the index of the next element to be processed in argv.
	if (argc < optind + 2) {
	    fprintf(stderr, "Not enough arguments provided.\n");
	    fprintf(stderr, "Usage: %s [-l|-m|-v|-i|-c] indirectory1 [indirectory2 ...] outdirectory\n", progname);
	    exit(EXIT_FAILURE);
	}
	
	//  Creates output directory if it does not exist.
	if (!cflag && fileType(OUTPUTDIR) == DNE) {
	    if (vflag) printf("Output directory does not exist...creating output directory.\n");
		
	    if (mkdir(OUTPUTDIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
	    	fprintf(stderr, "Error creating output directory.");
	    	exit(EXIT_FAILURE);
	    }
	}
	if (cflag) {
	    char *temp = "__T_E_M_P__";
        // temporary directory created to hold files for processing 
	    if (mkdir(temp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
	    	fprintf(stderr, "Error creating output directory.");
	    	exit(EXIT_FAILURE);
	    }
        
        // this compares multiple input directories against the created temp
        // directory. It has the same effect as comparing within input dirs.
	    while (optind != argc - 1) {
            listDir(argv[optind++], temp);
        }

	    char *args[] = {"rm", "-R", temp, NULL};
	    execv("/bin/rm", args); // temporary directory deleted.
	}
	// Process each input directory.
	// optind is the index of the next element to be processed in argv.
	else {
        // this compares multiple input directories against the created/existing
        // out directory. It has the same effect as comparing within input dirs.
	    while (optind != argc - 1) {
            listDir(argv[optind++], OUTPUTDIR);
	    }
	}
	return 0;
}
