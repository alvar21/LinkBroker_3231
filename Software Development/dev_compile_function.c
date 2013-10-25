void DEVcompile(char *filename){
	pid_t pid = fork();
	
	if(pid==0){
		static char *argv[]={"gcc", "-c", filename};
		execv("/usr/bin/gcc"), argv);
		exit(127);
	}
		
	else{
		waitpid(pid, 0, 0);
	}
		return;
}