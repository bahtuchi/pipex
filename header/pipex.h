/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommehdiz <ommehdiz@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:26:55 by ommehdiz          #+#    #+#             */
/*   Updated: 2024/09/04 14:21:00 by ommehdiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
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

void	free_all(t_pipeline *pipex);
void	file_checker(int argc, char **argv);
char	*path_extract(char **envp);
char	*command_to_path(char **splitted_path, char **cmd);
char	*full_path(char *cmd, char **envp);
void	open_files(t_pipeline *pipex, char **argv);
void	setup_pipe_and_fork(t_pipeline *pipex, char **argv, char **envp);
void	child(t_pipeline *pipex, char **argv, char **envp);
void	parent(t_pipeline *pipex, char **argv, char **envp);

#endif