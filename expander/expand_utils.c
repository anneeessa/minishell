/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:05:09 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:05:09 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_value(char *var_name, t_data **data)
{
	int		i;
	int		len_value;
	char	*var;
	char	*final_value;

	i = -1;
	while ((*data)->env[++i])
	{
		if (var_name[0] == '?')
			return (ft_itoa((*data)->exit_status));
		if (!ft_strncmp((*data)->env[i], var_name, ft_strlen(var_name)))
		{
			var = ft_strchr((*data)->env[i], '=');
			len_value = ft_strlen(var);
			final_value = ft_calloc(len_value, sizeof(char));
			len_value = -1;
			while (var[++len_value])
				final_value[len_value] = var[len_value + 1];
			return (final_value);
		}
	}
	return (NULL);
}

static char	*expand_tilda(char *var, size_t i, char **str)
{
	char	*result;
	int		end_of_var;
	size_t	j;

	result = ft_calloc((ft_strlen((*str)) + ft_strlen(var)), sizeof(char));
	i = -1;
	while ((++i < (ft_strlen((*str)))) && (*str)[i] != '~')
		result[i] = (*str)[i];
	end_of_var = i + 1;
	i--;
	j = -1;
	while (var[++j] && j < ft_strlen(var))
		result[++i] = var[j];
	while ((*str)[end_of_var])
		result[++i] = (*str)[end_of_var++];
	return (result);
}

void	replace_tilda(char **result, char *str, char *home)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '~')
		{
			*result = expand_tilda(home, 1, &str);
			return ;
		}
	}
}

int	replace_tilde_with_home(t_data **data)
{
	char	*result;
	char	*home;

	if (!ft_strchr((*data)->copy_input, '~'))
		return (0);
	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("$HOME environment variable not set.\n", 2);
		return (1);
	}
	result = NULL;
	replace_tilda(&result, (*data)->copy_input, home);
	free((*data)->copy_input);
	(*data)->copy_input = NULL;
	(*data)->copy_input = result;
	return (0);
}
