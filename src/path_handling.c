/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommehdiz <ommehdiz@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:02:20 by ommehdiz          #+#    #+#             */
/*   Updated: 2024/09/04 14:09:17 by ommehdiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

/// @brief Opens the input and output files for the pipeline.
/// Opens the input file in read-only mode and the output file
/// in read-write mode. 
/// Exits with an error message if either file cannot be opened.
/// @param pipex Pipeline structure containing file descriptors.
/// @param argv Argument values containing file paths.
/// @warning Exits with failure status if file opening fails.
/// Closes the input file if the output file fails to open.
void	open_files(t_pipeline *pipex, char **argv)
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

/// @brief Sets up a pipe and forks a child process for the pipeline.
/// Creates a pipe, forks the process, and executes the child or 
/// parent function based on the fork result.
/// @param pipex Pipeline structure containing pipe and process information.
/// @param argv Argument values for command execution.
/// @param envp Environment variables.
/// @warning Exits with failure status if pipe creation or forking fails. 
/// Frees allocated memory on fork failure.

void	setup_pipe_and_fork(t_pipeline *pipex, char **argv, char **envp)
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
		parent(pipex, argv, envp);
}
