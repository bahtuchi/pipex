/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommehdiz <ommehdiz@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 08:29:30 by omed              #+#    #+#             */
/*   Updated: 2024/09/04 14:24:53 by ommehdiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

/// @brief Handles the child process of the pipeline.
/// Closes the write end of the pipe, duplicates the read end to STDOUT,
/// and redirects the input file to STDIN. Executes the command found 
/// from the command string, and exits on failure.
/// @param pipex Pipeline structure containing file descriptors + command info.
/// @param argv Command-line arguments.
/// @param envp Environment variables.
/// @warning Exits with failure status if command not found or execve fails.
void	child(t_pipeline *pipex, char **argv, char **envp)
{
	dup2(pipex->tube[1], STDOUT_FILENO);
	close(pipex->tube[1]);
	close(pipex->tube[0]);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->infile);
	pipex->command = ft_split(argv[2], ' ');
	pipex->command_path = command_to_path(pipex->splitted_path, pipex->command);
	if (pipex->command_path == NULL)
	{
		perror("Command not found");
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	execve(pipex->command_path, pipex->command, envp);
	perror("execve failed");
	free_all(pipex);
	exit(EXIT_FAILURE);
}

/// @brief Handles the parent process of the pipeline.
/// Closes the write end of the pipe, duplicates the read end to STDOUT,
/// and redirects the input file to STDIN. Executes the command found 
/// from the command string, and exits on failure.
/// @param pipex Pipeline structure containing file descriptors + command info.
/// @param argv Command-line arguments.
/// @param envp Environment variables.
/// @warning Exits with failure status if command not found or execve fails.
void	parent(t_pipeline *pipex, char **argv, char **envp)
{
	dup2(pipex->tube[0], STDIN_FILENO);
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	pipex->command = ft_split(argv[3], ' ');
	pipex->command_path = command_to_path(pipex->splitted_path, pipex->command);
	if (pipex->command_path == NULL)
	{
		perror("Command not found");
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	execve(pipex->command_path, pipex->command, envp);
	perror("execve failed");
	free_all(pipex);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipeline	pipex;

	file_checker(argc, argv);
	open_files(&pipex, argv);
	pipex.env_path = path_extract(envp); 
	pipex.splitted_path = ft_split(pipex.env_path, ':');
	setup_pipe_and_fork(&pipex, argv, envp);
	close(pipex.tube[1]); 
	close(pipex.tube[0]);
	waitpid(pipex.pid1, NULL, 0);
	close (pipex.infile);
	close(pipex.outfile);
	free_all(&pipex);
	return (0);
}
