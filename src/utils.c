/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommehdiz <ommehdiz@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:39:39 by ommehdiz          #+#    #+#             */
/*   Updated: 2024/09/04 14:04:15 by ommehdiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

/// @brief Extracts the PATH variable from the environment variables.
/// Finds and returns the PATH string from the envp array, skipping 
/// the "PATH=" prefix.
/// @param envp Array of environment variables.
/// @return Pointer to the PATH value (excluding "PATH=" prefix).
/// @warning Assumes the PATH variable is present in the environment.
char	*path_extract(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	return (envp[i] + 5);
}

/// @brief Constructs the full path to a command by combining directories 
/// from the PATH with the command name.
/// Iterates through the splitted path directories, appending the command name,
/// and checks for execution permissions.
/// @param splitted_path Array of directories from the PATH variable.
/// @param cmd Command array (first element being the command name).
/// @return Full path to the command if found and executable, otherwise NULL.
/// @warning Returns NULL if memalloc fails or no executable 
/// command is found.
char	*command_to_path(char **splitted_path, char **cmd)
{
	char	*cmd_path;
	char	*command;
	int		i;

	i = 0;
	while (splitted_path[i])
	{
		cmd_path = ft_strjoin(splitted_path[i], "/");
		if (!cmd_path) 
			return (NULL);
		command = ft_strjoin(cmd_path, cmd[0]);
		free(cmd_path);
		if (!command) 
			return (NULL);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

/// @brief Finds the full executable path for a given 
/// command using the PATH environment variable.
/// Splits the PATH, constructs potential command paths,
/// and returns the valid executable path if found.
/// @param cmd The command to locate.
/// @param envp Environment variables array.
/// @return Full path to the command if found, otherwise NULL.
/// @warning Frees the splitted PATH array before returning.
/// Returns NULL on failure.
char	*full_path(char *cmd, char **envp)
{
	t_pipeline	pipex;
	int			i;

	pipex.splitted_path = ft_split(path_extract(envp), ':');
	pipex.command_path = command_to_path(pipex.splitted_path, &cmd);
	i = 0;
	while (pipex.splitted_path[i])
	{
		free(pipex.splitted_path[i]);
		i++;
	}
	free(pipex.splitted_path);
	return (pipex.command_path);
}
