/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omed <omed@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 08:29:30 by omed              #+#    #+#             */
/*   Updated: 2024/09/03 21:11:03 by omed             ###   ########.fr       */
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
	char	**command;
	char	*command_path;
	char	**splitted_path;
	char	*env_path;
}	t_pipeline;

void free_all(t_pipeline *pipex)
{
	int	i;

	i = 0;
	if (pipex->command)
	{
		while(pipex->command[i])
		{
			free(pipex->command);
			i++;
		}
		free(pipex->command);
	}
	i = 0;
	if(pipex->splitted_path[i])
	{
		while(pipex->splitted_path[i])
		{	
			free(pipex->splitted_path[i]);
			i++;
		}
		free(pipex->splitted_path[i]);
	}
	if (pipex->command_path)
		free(pipex->command_path);	
}

void child(t_pipeline *pipex, char **argv,char **envp)
{
	dup2(pipex->tube[1], STDOUT_FILENO);
	close(pipex->tube[1]);
	close(pipex->tube[0]);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->infile);
	
	pipex->command = ft_split(argv[2], ' ');
	pipex->command_path = command_to_path(pipex->splitted_path, pipex->command);
	if (pipex->command_path == NULL) {
		perror("Command not found");
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	execve(pipex->command_path, pipex->command, envp);
	perror("execve failed");
	free_all(pipex);
	exit(EXIT_FAILURE);
}

void parent(t_pipeline *pipex, char **argv,char **envp)
{
	dup2(pipex->tube[0], STDIN_FILENO);
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	
	pipex->command = ft_split(argv[3], ' ');
	pipex->command_path = command_to_path(pipex->splitted_path, pipex->command);
	if (pipex->command_path == NULL) {
		perror("Command not found");
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	execve(pipex->command_path, pipex->command, envp);
	perror("execve failed");
	free_all(pipex);
	exit(EXIT_FAILURE);
}

char *path_extract(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	return (envp[i] + 5);
}

char	*command_to_path(char **splitted_path, char **cmd)
{
	char *cmd_path;
	char *command;
	int i;

	i = 0;
	while (splitted_path[i])
	{
		cmd_path = ft_strjoin(splitted_path[i], "/");
		if (!cmd_path) return NULL;

		command = ft_strjoin(cmd_path, cmd[0]);
		free(cmd_path);
		if (!command) return NULL;

		if (access(command, X_OK) == 0)
			return command;
		free(command);
		i++;
	}
	return (NULL);
}

char *full_path(char *cmd, char **envp)
{
	t_pipeline pipex;
	int	i;
	pipex.splitted_path = ft_split(path_extract(envp), ':');
	pipex.command_path = command_to_path(pipex.splitted_path, &cmd);
	
	i = 0;
	while(pipex.splitted_path[i])
	{
		free(pipex.splitted_path[i]);
		i++;	
	}
	free(pipex.splitted_path);
	return (pipex.command_path);
}


void file_checker(int argc, char **argv)
{
	
	if (argc != 5)
    {
		ft_putstr_fd("Function must have 4 Arguments!", 1);
		exit (EXIT_FAILURE);   
	}
	if (access(argv[1], F_OK) == -1 || access(argv[4], F_OK) == -1 )
    {
		ft_putstr_fd("Something wrong with your Files", 1);
		exit (EXIT_FAILURE);   
	}
	else if (access(argv[1], R_OK) == -1 || access(argv[4], W_OK | R_OK) == -1 )
    {
		ft_putstr_fd("Check your File permissions!", 1);
		exit (EXIT_FAILURE);   
	}
}



int main (int argc, char **argv, char **envp)
{
	t_pipeline pipex;

	file_checker(argc, argv);
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[4], O_RDWR);
	pipex.env_path = path_extract(envp);
	pipex.splitted_path = ft_split(path_extract(envp), ':');
	pipe(pipex.tube);
	pipex.pid1 = fork();
	if(pipex.pid1 == 0)
		child(pipex, argv, envp);
	else if (pipex.pid1 < 0)	
	{
		ft_putstr_fd("Forking didnt work", 1);
		exit (EXIT_FAILURE); 
	}
	else 
		parent(pipex, argv, envp);
	close(pipex.tube[1]); 
	close(pipex.tube[0]);
	waitpid(pipex.pid1, NULL, 0);
	free_all(pipex);
	return (0);
}
