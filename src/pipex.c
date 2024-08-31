/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omed <omed@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 08:29:30 by omed              #+#    #+#             */
/*   Updated: 2024/08/31 23:46:13 by omed             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
# include "../libft/libft.h"


typedef struct s_pipeline
{
	int		infile;
	int		outfile;
	int		tube[2];
	int		pid1;
	int		pid2;
	char	*command;
	char	*command_path;
	char	**splitted_path;
	char	*env_path;
}	t_pipeline;


char *path_extract(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
	{
		i++;
	}
	return (envp[i] + 5);
}

char	*command_to_path(char **envp, char *cmd)
{
		t_pipeline pipex;

	//printf("%s", path_extract(envp));

	int i = 0;
	while(pipex.splitted_path[i])
	{
		if((ft_strncmp("/usr/bin", pipex.splitted_path[i], 8) == 0))
		{
			pipex.command_path = ft_strjoin(pipex.splitted_path[i], "/");
			pipex.command = ft_strjoin(pipex.command_path, cmd);
			free(pipex.splitted_path);
			free(pipex.command_path);
			if(access(pipex.command, X_OK) == 0)
				return(pipex.command);
			free(pipex.command);
			i++;
		}
	i++;
	}
}

char *full_path(char *cmd, char **envp)
{
	t_pipeline pipex;
	
	pipex.splitted_path = ft_split(path_extract(envp), ':');
	
	int	i;

	i = 0;
	while(pipex.splitted_path)
}

/*
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

//Maybe not needed
void	check_files(int argc, char **argv)
{

}

void	free_everything(t_pipeline pipeline)
{

}


char	*get_path(char **splitted_path, char *command)
{
	t_pipeline pipex;



}

char	*find_path(char **envp)
{
	t_pipeline pipex;

}


int main(int argc, char **argv, char **envp)
{
	t_pipeline pipex;


    if (argc != 5)
    {
		ft_putstr("Function must have 4 Arguments!");
		exit (EXIT_FAILURE);   
	}
	if (access(argv[1], R_OK) == -1)
	{
		ft_putstr("wrong Input-File");
		exit (EXIT_FAILURE);   
	}
	if (access(argv[5], W_OK || R_OK) == -1)
	{
		ft_putstr("wrong Output-File");
		exit (EXIT_FAILURE); 
	}
	if (pipe(pipex.tube) == -1)
	{
		return 1;
	}

	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
	{
		return 2;
	}
//child
	if (pipex.pid1 == 0)
	{
		dup2(pipex.tube[1], STDOUT_FILENO);
		close(pipex.tube[0]);
		close(pipex.tube[1]);
		execve("", NULL);
	}
//other child
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
	{
		dup2(pipex.tube[0], STDIN_FILENO);
		close(pipex.tube[0]);
		close(pipex.tube[1]);
		return 3;
	}


}*/

int main (int argc, char **argv, char **envp)
{
	t_pipeline pipex;

	/*if (argc != 5)
    {
		ft_putstr_fd("Function must have 4 Arguments!", 1);
		exit (EXIT_FAILURE);   
	}*/
	//printf("%s", path_extract(envp));
}
