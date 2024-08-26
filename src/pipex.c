
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

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>


typedef struct s_pipeline
{
	int		infile;
	int		outfile;
	int		tube[2];
	int		pid1;
	int		pid2;
	char	**command;
	char	**command_path;
	char	**splitted_path;
	char	*env_path;
}	t_pipeline;

void ft_putstr(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		write(1, str + i, 1);
		i++;
	}
}



void	check_files(int argc, char **argv)
{

}

void	free_everything(t_pipeline pipeline)
char	*get_path(char **splitted_path, char *command)
char	*find_path(char **envp)


int main(int argc, char **argv, char **envp)
{
    if (argc != 5)
    {
		ft_putstr("Function must have 4 Arguments!");
		exit (EXIT_FAILURE);   
	}
	if (access(argv[1], R_OK) == -1)
	{
		ft_putstr("wrong Input-File");
	}
	if (access(argv[5], W_OK) == -1)
	{
		ft_putstr("wrong Output-File");
	}
	

}
