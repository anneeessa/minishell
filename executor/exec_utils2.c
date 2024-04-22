/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:04:31 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:04:31 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_child_process(t_data **data, int status)
{
	int	i;

	i = -1;
	while ((++i < ((*data)->no_of_pipes + 1)))
	{
		wait(&status);
		if (WIFEXITED(status))
			(*data)->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			if (status != 13)
				(*data)->exit_status = 128 + WTERMSIG(status);
	}
	return ((*data)->exit_status);
}

void	display_file_error_msg(t_command *command, int token_type, int fd)
{
	if (token_type == LESS && fd == -1)
	{
		if (command->input.filename[
				ft_strlen(command->input.filename) - 1] == '/')
			print_error("minishell: ", command->input.filename, ": ");
	}
	if ((token_type == GREAT_GREAT || token_type == GREAT) && fd == -1)
	{
		if (command->output.filename[
				ft_strlen(command->output.filename) - 1] == '/')
			print_error("minishell: ", command->output.filename, ": ");
	}
}

int	get_fd(t_command *command, int token_type)
{
	int	fd;

	fd = 0;
	if (token_type == GREAT)
		fd = open(command->output.filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (token_type == GREAT_GREAT)
		fd = open(command->output.filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (token_type == LESS)
		fd = open(command->input.filename, O_RDONLY, 0777);
	display_file_error_msg(command, token_type, fd);
	return (fd);
}
