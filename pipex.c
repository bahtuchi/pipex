
/*
functions to be used:
dup2() - replaces open file descriptors
access() - checks whether a process has permission
			to access a file or directory
execve() - system call, that allows to execute another
			programm from current program
fork() - system call that creates a new process
pipe() - creates unidirectional data channel that
		is used for interprocess communication
unlink() - removes a file from file system
waitpid() - lets the parent process wait for pid-Specific child to finish
wait() - waits for any process to finish
 */


int main(int ac, char **av, char **env)
{
    if (ac != 5)
        return (1);

	

}
