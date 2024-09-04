#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../libft/libft.h"

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

void free_all(t_pipeline *pipex);
void child(t_pipeline *pipex, char **argv, char **envp);
void parent(t_pipeline *pipex, char **argv, char **envp);
char *path_extract(char **envp);
char *command_to_path(char **splitted_path, char **cmd);
char *full_path(char *cmd, char **envp);
void file_checker(int argc, char **argv);


void free_all(t_pipeline *pipex)
{
	int	i;

	if (pipex->command) {
		for (i = 0; pipex->command[i]; i++) {
			free(pipex->command[i]);
		}
		free(pipex->command);
	}
	
	if (pipex->splitted_path) {
		for (i = 0; pipex->splitted_path[i]; i++) {
			free(pipex->splitted_path[i]);
		}
		free(pipex->splitted_path);
	}
	
	if (pipex->command_path) {
		free(pipex->command_path);
	}
}

void child(t_pipeline *pipex, char **argv, char **envp)
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

void parent(t_pipeline *pipex, char **argv, char **envp)
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

char *command_to_path(char **splitted_path, char **cmd)
{
	char *cmd_path;
	char *command;
	int i = 0;
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
	return NULL;
}

char *full_path(char *cmd, char **envp)
{
	t_pipeline pipex;
	pipex.splitted_path = ft_split(path_extract(envp), ':');
	pipex.command_path = command_to_path(pipex.splitted_path, &cmd);
	
	int i = 0;
	while (pipex.splitted_path[i])
	{
		free(pipex.splitted_path[i]);
		i++;	
	}
	free(pipex.splitted_path);
	return pipex.command_path;
}

void file_checker(int argc, char **argv)
{
	if (argc != 5)
    {
		ft_putstr_fd("Function must have 4 Arguments!\n", 1);
		exit(EXIT_FAILURE);   
	}
	if (access(argv[1], F_OK) == -1 || access(argv[4], F_OK) == -1)
    {
		ft_putstr_fd("Something wrong with your Files\n", 1);
		exit(EXIT_FAILURE);   
	}
	else if (access(argv[1], R_OK) == -1 || access(argv[4], W_OK | R_OK) == -1)
    {
		ft_putstr_fd("Check your File permissions!\n", 1);
		exit(EXIT_FAILURE);   
	}
}

void open_files(t_pipeline *pipex, char **argv)
{
    pipex->infile = open(argv[1], O_RDONLY);
    if (pipex->infile < 0)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    
    pipex->outfile = open(argv[4], O_RDWR);
    if (pipex->outfile < 0)
    {
        perror("Error opening output file");
        close(pipex->infile);
        exit(EXIT_FAILURE);
    }
}
void setup_pipe_and_fork(t_pipeline *pipex, char **argv, char **envp)
{
    pipe(pipex->tube);
    pipex->pid1 = fork();
    
    if (pipex->pid1 == 0)
    {
        child(pipex, argv, envp);
    }
    else if (pipex->pid1 < 0)
    {
        perror("Forking failed");
        free_all(pipex);
        exit(EXIT_FAILURE);
    }
    else 
    {
        parent(pipex, argv, envp);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_pipeline pipex;

    file_checker(argc, argv);  // Check files and arguments
    open_files(&pipex, argv);  // Open input and output files
    
    pipex.env_path = path_extract(envp);  // Extract the PATH environment variable
    pipex.splitted_path = ft_split(pipex.env_path, ':');  // Split PATH into directories
    
    setup_pipe_and_fork(&pipex, argv, envp);  // Setup pipes and fork processes
    
    close(pipex.tube[1]); 
    close(pipex.tube[0]);
    
    waitpid(pipex.pid1, NULL, 0);  // Wait for the child process to finish
    
    close(pipex.infile);
    close(pipex.outfile);
    
    free_all(&pipex);  // Free allocated memory
    return 0;
}
