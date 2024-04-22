/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_path_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:06:32 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/23 14:51:03 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_full_path(char *dir, char *command, char *fullPath)
{
	int	dir_len;

	dir_len = ft_strlen(dir);
	fullPath = (char *)malloc((ft_strlen(dir) + 1) * sizeof(char));
	fullPath[ft_strlen(dir)] = '\0';
	fullPath = (char *)ft_memcpy(fullPath, dir, ft_strlen(dir));
	if (dir[dir_len - 1] != '/')
		fullPath = ft_strjoin(fullPath, "/");
	fullPath = ft_strjoin(fullPath, command);
	return (fullPath);
}

int	find_command(t_data **data, char *str)
{
	int		i;
	char	*full_path;

	i = -1;
	full_path = NULL;
	while ((*data)->splitted_path && (*data)->splitted_path[++i])
	{
		full_path = get_full_path((*data)->splitted_path[i], str, full_path);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				free(full_path);
				return (1);
			}
			else
			{
				print_error("minishell: ", full_path, ": ");
				free(full_path);
				return (-2);
			}
		}
		free(full_path);
	}
	return (0);
}

int	find_command_without_perror(t_data **data, char *str)
{
	int		i;
	char	*full_path;

	i = -1;
	full_path = NULL;
	while ((*data)->splitted_path && (*data)->splitted_path[++i])
	{
		full_path = get_full_path((*data)->splitted_path[i], str, full_path);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				free(full_path);
				return (1);
			}
			else
			{
				free(full_path);
				return (-1);
			}
		}
		free(full_path);
	}
	return (-2);
}

int	is_cmd_executable_without_perror(char *str)
{
	int	is_error;

	is_error = 0;
	if (ft_strncmp(str, "./", 2) == 0)
	{
		if (access(str, X_OK) == 0)
			return (1);
		else
			is_error = -1;
	}
	else if (ft_strchr(str, '/'))
	{
		if (access(str, X_OK) == 0)
			return (1);
		else
			is_error = -1;
	}
	return (is_error);
}
