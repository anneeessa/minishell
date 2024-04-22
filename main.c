/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:08:05 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/03/01 19:09:40 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchrq(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c > 255)
		c = c / 256;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (0);
}

void	mini_loop(t_data **data)
{
	while (1)
	{
		handle_signals();
		if (!init_data(data))
			continue ;
		if (!(*data)->copy_input[0])
			continue ;
		if (handle_db_quotes(data))
			continue ;
		handle_extra_spaces(&(*data)->copy_input, data);
		rm_quote(data);
		separate_characters(data, &(*data)->copy_input);
		if (!expand(data))
			continue ;
		if (!lex(data))
			continue ;
		if (!parser(data))
			continue ;
		if (!check_here_doc(data))
			continue ;
		handle_exc(data);
		free_memory(data, 0);
	}
}

void	increment_shlvl(t_data **data)
{
	int		i;
	char	*num;
	char	*sub;
	char	*new_shlvl;

	i = -1;
	sub = NULL;
	while ((*data)->env[++i])
	{
		if (!ft_strncmp((*data)->env[i], "SHLVL", 5))
		{
			sub = ft_substr((*data)->env[i], 6, 2);
			num = ft_itoa(ft_atoi(sub) + 1);
			new_shlvl = ft_strjoin(ft_strdup("SHLVL="), num);
			free((*data)->env[i]);
			(*data)->env[i] = new_shlvl;
			free(sub);
			free(num);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc > 1)
	{
		return (1);
	}
	(void)argv;
	data = (t_data *)malloc(sizeof(t_data));
	data->env = copy_env(env, 0);
	increment_shlvl(&data);
	data->exit_status = 0;
	g_exit_status = -2;
	mini_loop(&data);
	return (0);
}
