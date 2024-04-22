/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:48:36 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/29 15:46:30 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipes(t_data **data, t_token *tokens)
{
	int	i;

	i = -1;
	while (++i < tokens[0].tok_len)
		if (tokens[i].type == PIPE)
			(*data)->no_of_pipes++;
}

void	check_capitals(t_token *token, char **splitted, int tok_no)
{
	if (ft_strcmp(ft_tolower(splitted[tok_no]), "echo") == 0)
	{
		free((*token).value);
		(*token).value = ft_strdup("echo");
		(*token).type = B_COMMAND;
	}
	else if (ft_strcmp(ft_tolower(splitted[tok_no]), "env") == 0)
	{
		free((*token).value);
		(*token).value = ft_strdup("env");
		(*token).type = B_COMMAND;
	}
	else if (!ft_strcmp(ft_tolower(splitted[tok_no]), "pwd") && !tok_no)
	{
		free((*token).value);
		(*token).value = ft_strdup("pwd");
		(*token).type = B_COMMAND;
	}
	else
		(*token).type = UNKNOWN;
}

void	get_tokentype(t_token *token, char **splitted, int tok_no)
{
	if (ft_strcmp(splitted[tok_no], ">") == 0)
		(*token).type = GREAT;
	else if (ft_strcmp(splitted[tok_no], "<") == 0)
		(*token).type = LESS;
	else if (ft_strcmp(splitted[tok_no], ">>") == 0)
		(*token).type = GREAT_GREAT;
	else if (ft_strcmp(splitted[tok_no], "<<") == 0)
		(*token).type = LESS_LESS;
	else if (tok_no >= 1 && !ft_strcmp(splitted[tok_no - 1], "<<"))
		(*token).type = DELIMITER;
	else if (splitted[tok_no][0] == '|')
		(*token).type = PIPE;
	else if (ft_strcmp(splitted[tok_no], "echo") == 0
		|| ft_strcmp(splitted[tok_no], "cd") == 0
		|| ft_strcmp(splitted[tok_no], "pwd") == 0
		|| ft_strcmp(splitted[tok_no], "export") == 0
		|| ft_strcmp(splitted[tok_no], "unset") == 0
		|| ft_strcmp(splitted[tok_no], "env") == 0
		|| ft_strcmp(splitted[tok_no], "exit") == 0)
	{
		(*token).type = B_COMMAND;
	}
	else
		check_capitals(token, splitted, tok_no);
}

int	get_double_pointer_len(char **arr)
{
	int	length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}

void	build_tokens(t_data **data)
{
	char	**splitted;
	int		tok_no;
	t_token	*token;
	t_token	temp_tok;

	splitted = split_input((*data)->copy_input, ' ');
	tok_no = len_splitted(splitted);
	token = ft_calloc((tok_no + 1), sizeof(t_token));
	tok_no = -1;
	while (splitted[++tok_no])
	{
		temp_tok.value = ft_strdup(splitted[tok_no]);
		get_tokentype(&temp_tok, splitted, tok_no);
		token[tok_no].tok_len = len_splitted(splitted);
		token[tok_no].type = temp_tok.type;
		token[tok_no].value = temp_tok.value;
	}
	free_db_array(&splitted);
	(*data)->tokens = token;
}
