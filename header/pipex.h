/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommehdiz <ommehdiz@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:26:55 by ommehdiz          #+#    #+#             */
/*   Updated: 2024/08/25 15:33:54 by ommehdiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	char	**command_path;
	char	**splitted_path;
	char	*env_path;
}	t_pipeline;

void	ft_putstr(char *str);
void	free_everything(t_pipeline pipeline);
char	*get_path(char **splitted_path, char *command);
char	*find_path(char **envp);
void	check_files(int argc, char **argv);

#endif