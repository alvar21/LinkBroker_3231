/*
 CITS3231 Project 2013
 Name(s):           Alvar Ongkowidjaja, Danielle Page and Michael Piotrowski
 Student number(s): 20841563, 20753669, 20738843
 Date:              25 October 2013
 */

/*
 * Function for Linkbroker that takes any number of .o components
 * and links them together into an executable.
 * argv is composed of .o files and must include the developer's code
 * the final executable is created in the current directory.
 */


int make_executable(int argc, char *argv[])
{

    pid_t cpid = fork();
    if (cpid == 0)
    {

        //create argument array containing arguments to gcc
        static char *argv1[argc + 4];
        argv1[0] = "gcc";

        //code to support any number of object files
        for (int i = 0; i < argc + 1; i++)
        {
            argv1[i + 1] = argv[i];
        }

        //requires -lcrypt due to gcc dysfunction with crypt header file
        argv1[argc + 1] = "-lcrypt"
        argv1[argc + 2] = "-o"
        argv1[argc + 3] = "final_executable"
        
        //call gcc with the provided arguments
        execv("/usr/bin/gcc", argv1);
        exit(127);
    }
    else
    {
        waitpid(cpid, 0, 0);
    }

    return 0;
}
