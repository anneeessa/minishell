/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:04:37 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:04:37 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd_dir(char *full_path)
{
	struct stat	sb;

	if (stat(full_path, &sb) == -1)
		return (print_error("minishell: ", full_path, ": "), 0);
	if (S_ISDIR(sb.st_mode))
	{
		return (print_error2("minishell: ", full_path,
				": is a directory\n"), 0);
	}
	return (1);
}

void	run_cmd(t_data **data, t_command *command, char **full_path,
				t_command *temp_cmd)
{
	if (!command->name)
		return ;
	else if (is_builtin(command->name))
	{
		exe_b_cmd(command->name, command->args, data, temp_cmd);
		exit_from_child(data, temp_cmd, EXIT_SUCCESS);
	}
	else
	{
		if (is_cmd_dir(*full_path) == 0)
			exit_from_child(data, temp_cmd, 126);
		execve(*full_path, command->args, (*data)->env);
		exit_from_child(data, temp_cmd, EXIT_FAILURE);
	}
}

void	remove_qoutes(t_command **cmd)
{
	char		*str;
	t_command	*temp;
	int			i;

	temp = *cmd;
	while (*cmd)
	{
		i = -1;
		while ((*cmd)->args[++i] && !is_builtin((*cmd)->name))
		{
			str = ft_strdup((*cmd)->args[i]);
			if ((str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
				|| (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"'))
			{
				free((*cmd)->args[i]);
				(*cmd)->args[i] = ft_substr(str, 1,
						ft_strlen(str) - 2);
			}
			free(str);
		}
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
}

void	handle_exc(t_data **data)
{
	remove_qoutes(&(*data)->command);
	if ((!(*data)->command->next))
		exec_one_cmd(data, (*data)->command);
	else
		execute_multiple_cmd(data);
}
