/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:40:29 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/29 15:53:26 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_free(t_data **data, char *str, char *value, int free_only)
{
	if (!free_only)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd("\'\n", 2);
		(*data)->exit_status = 2;
	}
	free((*data)->input);
	free((*data)->copy_input);
	free((*data)->path);
	free_tokens(data);
}

void	print_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	perror("");
}

void	print_error2(char *s1, char *s2, char *s3)
{
	int	flag;

	flag = 0;
	if ((s2[0] == '\"' && s2[ft_strlen(s2) - 1] == '\"')
		|| (s2[0] == '\'' && s2[ft_strlen(s2) - 1] == '\''))
	{
		s2 = ft_substr(s2, 1, ft_strlen(s2) - 2);
		flag = 1;
	}
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	if (flag)
		free(s2);
}

void	free_command(t_command *command)
{
	t_command	*next;

	while (command)
	{
		next = command->next;
		if (command->name)
			free(command->name);
		free(command->input.name);
		free(command->output.name);
		free(command->input.filename);
		free(command->output.filename);
		if (command->args != NULL)
			free_db_array(&command->args);
		free(command);
		command = next;
	}
}

void	free_memory(t_data **data, int free_env)
{
	unlink("libft/here_doc_temp");
	unlink("libft/here_doc_sig");
	free((*data)->input);
	free((*data)->copy_input);
	if ((*data)->path)
		free((*data)->path);
	if ((*data)->splitted_path)
		free_db_array(&(*data)->splitted_path);
	free_tokens(data);
	free_command((*data)->command);
	if (free_env)
	{
		free_db_array(&(*data)->env);
		free(*data);
	}
}
