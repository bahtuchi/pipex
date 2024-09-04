/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommehdiz <ommehdiz@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:48:12 by ommehdiz          #+#    #+#             */
/*   Updated: 2024/09/04 14:05:36 by ommehdiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

/// @brief Frees all dynamically allocated memory within the pipeline structure.
/// Frees the memory for the command array, 
/// splitted path array,and command path.
/// @param pipex Pipeline structure containing the pointers to be freed.
/// @warning Ensure that all pointers are properly allocated before freeing.
void	free_all(t_pipeline *pipex)
{
	int	i;

	i = 0;
	if (pipex->command) 
	{
		while (pipex->command[i]) 
		{
			free(pipex->command[i]);
			i++;
		}
		free(pipex->command);
	}
	i = 0;
	if (pipex->splitted_path)
	{
		while (pipex->splitted_path[i])
		{
			free(pipex->splitted_path[i]);
			i++;
		}
		free(pipex->splitted_path);
	}
	if (pipex->command_path) 
		free(pipex->command_path);
}

/// @brief Checks the validity of file inputs and argument count.
/// Ensures the function has exactly 4 arguments and checks if files exist 
/// and have appropriate read/write permissions.
/// @param argc Argument count.
/// @param argv Argument values (file paths).
/// @warning Exits with failure status if the argument count is incorrect, 
/// files are missing, or permissions are insufficient.
void	file_checker(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Function must have 4 Arguments!\n", 1);
		exit (EXIT_FAILURE);
	}
	if (access(argv[1], F_OK) == -1 || access(argv[4], F_OK) == -1)
	{
		ft_putstr_fd("Something wrong with your Files\n", 1);
		exit (EXIT_FAILURE);
	}
	else if (access(argv[1], R_OK) == -1 || access(argv[4], W_OK | R_OK) == -1)
	{
		ft_putstr_fd("Check your File permissions!\n", 1);
		exit (EXIT_FAILURE);
	}
}
