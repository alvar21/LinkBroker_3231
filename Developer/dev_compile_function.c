/*
 CITS3231 Project 2013
 Name(s):           Alvar Ongkowidjaja, Danielle Page and Michael Piotrowski
 Student number(s): 20841563, 20753669, 20738843
 Date:              25 October 2013
 */

void DEVcompile(char *filename)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        static char *argv[] = {"gcc", "-c", filename};
        execv("/usr/bin/gcc"), argv);
        exit(127);
    }

    else
    {
        waitpid(pid, 0, 0);
    }
    return;
}