/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:03:59 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:03:59 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_string(char **args, int j, int i)
{
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	i = 0;
	while (args[j][i])
	{
		if ((args[j][i] == '\'' && double_quote == false))
			single_quote = !single_quote;
		else if (args[j][i] == '\"' && single_quote == false)
			double_quote = !double_quote;
		else
			printf("%c", args[j][i]);
		i++;
	}
}

static void	ft_check(char **args, int i, int flag, int k)
{
	int	a;
	int	b;

	a = 0;
	while (args[i])
	{
		b = i;
		while (b > 0 && flag)
		{
			if (ft_strcmp(args[b], "-n") == 0)
			{
				a++;
				break ;
			}
			b--;
		}
		if ((i > 1 && !flag) || a > 1)
			printf(" ");
		write_string(args, i, k);
		i++;
	}
}

static void	cont(char **args, int i, int k, int flag)
{
	if (!args[1])
	{
		g_exit_status = 0;
		printf("\n");
		return ;
	}
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		i++;
		flag = 1;
	}
	ft_check(args, i, flag, k);
	if (!flag)
		printf("\n");
	g_exit_status = 0;
}

void	ft_echo(char **args, t_data **data)
{
	int		i;
	int		k;
	int		flag;

	i = 1;
	flag = 0;
	k = 0;
	cont(args, i, k, flag);
	(*data)->exit_status = g_exit_status;
}
