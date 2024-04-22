/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:06:24 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:06:24 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd_executable(char *str)
{
	int	is_error;

	is_error = 0;
	errno = 0;
	if (ft_strncmp(str, "./", 2) == 0)
	{
		if (access(str, X_OK) == 0)
			return (1);
		else
		{
			is_error = -1;
			print_error("minishell: ", str, ": ");
		}
	}
	else if (ft_strchr(str, '/'))
	{
		if (access(str, X_OK) == 0)
			return (1);
		else
		{
			is_error = -1;
			print_error("minishell: ", str, ": ");
		}
	}
	return (is_error);
}

int	is_non_b_command(char *str, t_data **data, int count_pipes)
{
	int	is_cmd_valid;
	int	is_executable;

	is_executable = is_cmd_executable(str);
	if (is_executable == -1 && count_pipes <= 0)
		return (-2);
	else if (is_executable == 1)
		return (1);
	is_cmd_valid = find_command(data, str);
	if (is_cmd_valid == 1)
		return (1);
	else if (is_cmd_valid == -2)
		return (-2);
	return (0);
}

static int	is_redirection(t_data **data, int i)
{
	if ((*data)->tokens[i].type == GREAT
		|| (*data)->tokens[i].type == GREAT_GREAT
		|| (*data)->tokens[i].type == LESS
		|| (*data)->tokens[i].type == LESS_LESS
		|| (*data)->tokens[i].type == DELIMITER)
		return (1);
	return (0);
}

int	command_present(t_data **data, int i, int token_len)
{
	if ((*data)->tokens[i].type == PIPE && i > 0)
	{
		if (++i >= token_len)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			(*data)->exit_status = 2;
			return (0);
		}
	}
	if (is_non_b_command((*data)->tokens[i].value, data, (*data)->no_of_pipes)
		== -2)
		return (-2);
	if ((is_non_b_command((*data)->tokens[i].value, data, (*data)->no_of_pipes)
			|| (*data)->tokens[i].type == B_COMMAND))
		return (1);
	if (is_redirection(data, i))
		return (1);
	if (!ft_strcmp((*data)->tokens[i].value, "$?"))
		return (1);
	return (-1);
}
