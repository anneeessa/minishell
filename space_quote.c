/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:59:33 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/29 16:32:05 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_quote(char **input, char **result, int *j, int *i)
{
	if ((*input)[*i] == '\'')
	{
		(*result)[(*j)++] = (*input)[*i];
		while ((*input)[++(*i)] != '\'')
			(*result)[(*j)++] = (*input)[*i];
		(*result)[(*j)++] = (*input)[*i];
		return (1);
	}
	else if ((*input)[*i] == '\"')
	{
		(*result)[(*j)++] = (*input)[*i];
		while ((*input)[++(*i)] != '\"')
			(*result)[(*j)++] = (*input)[*i];
		(*result)[(*j)++] = (*input)[*i];
		return (1);
	}
	return (0);
}

char	*remove_extra_space_2(char **copy_of_input, char **result, int j)
{
	int		i;
	bool	prev_space;

	prev_space = false;
	i = -1;
	while ((*copy_of_input)[++i] != '\0')
	{
		if (if_quote(copy_of_input, result, &j, &i))
			continue ;
		else if ((*copy_of_input)[i] == 32 || (*copy_of_input)[i] == 9)
		{
			if (!prev_space)
			{
				(*result)[j++] = 32;
				prev_space = true;
			}
		}
		else
		{
			(*result)[j++] = (*copy_of_input)[i];
			prev_space = false;
		}
	}
	return ((*result));
}

void	handle_extra_spaces(char **input, t_data **data)
{
	char	*result;
	int		j;

	result = ft_calloc (ft_strlen(*input) + 1, sizeof(char));
	j = 0;
	result = remove_extra_space_2(input, &result, j);
	free(*input);
	(*data)->copy_input = result;
}

bool	handle_db_quotes(t_data **data)
{
	bool	flag1;
	bool	flag2;
	int		i;

	flag1 = false;
	flag2 = false;
	i = -1;
	while ((*data)->input[++i])
	{
		if ((*data)->input[i] == '\'' && !flag2)
			flag1 = !flag1;
		else if ((*data)->input[i] == '\"' && !flag1)
			flag2 = !flag2;
	}
	if (flag1 || flag2)
	{
		printf("\n Error! unclosed quote\n");
		free((*data)->input);
		free((*data)->copy_input);
		if ((*data)->path)
			free((*data)->path);
		(*data)->exit_status = 2;
	}
	return (flag1 || flag2);
}

void	free_tokens(t_data **data)
{
	int	t_len;
	int	i;

	t_len = (*data)->tokens[0].tok_len;
	i = -1;
	while (++i < t_len && (*data)->tokens[i].value)
		free((*data)->tokens[i].value);
	free((*data)->tokens);
}
