/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:06:45 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:06:45 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_init(t_command **command, t_data **data, int i)
{
	(*command) = (t_command *)malloc(sizeof(t_command));
	(*command)->name = NULL;
	(*command)->name = ft_strdup((*data)->tokens[i].value);
	(*command)->next = NULL;
	(*command)->is_runnable = true;
	(*command)->has_file_err = false;
	(*command)->cmd_path = NULL;
	(*command)->prev = NULL;
	(*command)->args = NULL;
	(*command)->output.name = ft_strdup("stdout");
	(*command)->input.name = ft_strdup("stdin");
	(*command)->input.filename = NULL;
	(*command)->output.filename = NULL;
	(*command)->output.type = NONE;
	(*command)->input.type = NONE;
	(*command)->input.is_delimiter_in_quote = false;
}

static t_command	*create_command_str(t_data **data, int i)
{
	t_command	*command;

	cmd_init(&command, data, i);
	if (i > 1)
	{
		command->prev = getlast((*data)->command);
		if (command->prev->output.type == NONE)
		{
			free(command->prev->output.name);
			command->prev->output.name = ft_strdup("pipe");
			command->prev->output.type = PIPE;
			command->input.type = PIPE;
		}
	}
	if (i > 1)
	{
		free(command->input.name);
		command->input.name = ft_strdup("pipe");
		command->input.type = PIPE;
	}
	return (command);
}

void	construct_command(t_data **data, int *i, char **arg)
{
	char	*arg2;

	if ((*data)->tokens[*i].type == UNKNOWN
		|| (*data)->tokens[*i].type == B_COMMAND)
	{
		arg2 = ft_strjoin(ft_strdup("`"), (*data)->tokens[*i].value);
		(*arg) = ft_strjoin(*arg, arg2);
		free(arg2);
	}
	else if ((*data)->tokens[*i].type == GREAT
		|| (*data)->tokens[*i].type == LESS
		|| ((*data)->tokens[*i].type == GREAT_GREAT
			|| (*data)->tokens[*i].type == LESS_LESS))
		identify_redirections(data, i);
	else if ((*data)->tokens[*i].type == PIPE)
	{
		(getlast((*data)->command))->args = ft_split((*arg), '`');
		(*i)++;
		(getlast((*data)->command))->next = create_command_str(data, (*i)--);
		free(*arg);
		(*arg) = ft_strdup("`");
	}
}

int	check_command_exist(t_data **data, int i, int token_len)
{
	int		return_val;

	while (++i < token_len)
	{
		if ((i == 0 || (*data)->tokens[i].type == PIPE))
		{
			return_val = command_present(data, i, token_len);
			if (return_val == 0 || return_val == -2)
				return (0);
			if (return_val == 1)
				continue ;
			if ((*data)->tokens[i].type == PIPE)
				i++;
			if (return_val == -1 && (*data)->no_of_pipes >= 1)
			{
				print_error2("minishell: ", (*data)->tokens[i].value,
					": command not found\n");
				return (0);
			}
			print_error2("minishell: ", (*data)->tokens[i].value,
				": command not found\n");
			return (0);
		}
	}
	return (1);
}

int	parser(t_data **data)
{
	int			i;
	int			token_len;
	char		*arg;

	token_len = (*data)->tokens[0].tok_len;
	(*data)->splitted_path = ft_split((*data)->path, ':');
	if (!check_command_exist(data, -1, token_len))
	{
		if (errno == 13)
			(*data)->exit_status = 126;
		else
			(*data)->exit_status = 127;
		free_memory(data, 0);
		return (0);
	}
	i = -1;
	arg = ft_strdup("`");
	(*data)->command = create_command_str(data, 0);
	while (++i < token_len)
		construct_command(data, &i, &arg);
	(getlast((*data)->command))->args = ft_split(arg, '`');
	free(arg);
	mark_commands(data);
	update_hasfile_err(&(*data)->command);
	return (1);
}
