/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:06:53 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:06:53 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*getlast(t_command *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

bool	handle_unclosed_quotes(t_data **data)
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
		printf(" Error! unclosed quote");
		free((*data)->input);
		free((*data)->copy_input);
		if ((*data)->path)
			free((*data)->path);
		(*data)->exit_status = 2;
	}
	return (flag1 || flag2);
}
