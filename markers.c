/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:06:39 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/23 16:48:29 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_hasfile_err(t_command **cmd)
{
	t_command	*temp;

	temp = (*cmd);
	while ((*cmd))
	{
		if (((*cmd)->input.type == LESS
				|| (*cmd)->input.type == LESS_LESS)
			&& access((*cmd)->input.filename, R_OK) == -1)
			(*cmd)->has_file_err = true;
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = temp;
}

void	mark_commands(t_data **data)
{
	t_command	*temp;
	int			return_value;

	temp = (*data)->command;
	return_value = 0;
	while ((*data)->command)
	{
		if (!(*data)->command->name)
		{
			(*data)->command = (*data)->command->next;
			continue ;
		}
		else if (ft_strchr((*data)->command->name, '/'))
			return_value = is_cmd_executable_without_perror
				((*data)->command->name);
		else if (is_builtin((*data)->command->name))
			return_value = 1;
		else
			return_value = find_command_without_perror(data,
					(*data)->command->name);
		if (return_value == -1 || return_value == -2)
			(*data)->command->is_runnable = false;
		(*data)->command = (*data)->command->next;
	}
	(*data)->command = temp;
}
