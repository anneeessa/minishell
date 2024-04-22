/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:03:33 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:03:33 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	my_atoi(const char *nptr)
{
	int			i;
	long long	result;
	int			sign;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] != '\0' && (nptr[i] == ' ' || nptr[i] == '\''
			|| (nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == '\"'
			|| nptr[i] == '+' || nptr[i] == '-'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (sign == -1 && (result * 10 + (nptr[i] - '0') - 1) == (LLONG_MAX))
			return (0);
		if (result > (LLONG_MAX - (nptr[i] - '0')) / 10)
			return (ft_putstr_fd(" numeric argument required\n", 2), -1);
		result = (result * 10) + (nptr[i++] - '0');
	}
	return (sign * result);
}

static void	check_digit(char *arg, size_t *j, t_data **data)
{
	while (arg[(*j)])
	{
		if (!ft_isdigit(arg[(*j)]) && arg[(*j)] != '+'
			&& arg[(*j)] != '-' && arg[(*j)] != '\''
			&& arg[(*j)] != '\"')
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			(*data)->exit_status = 255;
			break ;
		}
		(*j)++;
	}
}

static void	if_with_digit(char *arg, t_data **data)
{
	int	result;

	result = my_atoi(arg);
	if (result == 0)
		(*data)->exit_status = 0;
	if (result > 0)
		(*data)->exit_status = result % 256;
	else if (result < 0 && result != -1)
		(*data)->exit_status = 156;
	else if (result == -1)
		(*data)->exit_status = 255;
}

void	ft_exit(t_data **data, char **args)
{
	size_t	j;
	int		exit_status;

	j = 0;
	exit_status = 0;
	if ((*data)->no_of_pipes <= 0)
		printf("exit\n");
	if (get_double_pointer_len(args) > 2)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		(*data)->exit_status = 1;
	}
	if (args[1])
		check_digit(args[1], &j, data);
	if (get_double_pointer_len(args) == 2 && j == ft_strlen(args[1]))
		if_with_digit(args[1], data);
	if ((*data)->input_fd >= 0)
		close((*data)->input_fd);
	exit_status = (*data)->exit_status;
	free_memory(data, 1);
	exit(exit_status);
}
