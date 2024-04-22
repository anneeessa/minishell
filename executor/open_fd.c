/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:04:56 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/23 18:56:51 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_output_file(t_command *command)
{
	int	fd;

	if (!ft_strcmp(command->output.name, "file"))
	{
		fd = get_fd(command, command->output.type);
		if (fd >= 0)
			dup2(fd, STDOUT_FILENO);
		if (fd == -1)
			return (0);
		close(fd);
	}
	return (1);
}

static int	check_input_file(t_command *command)
{
	int	fd;

	if (!ft_strcmp(command->input.name, "here_doc"))
	{
		fd = open("libft/here_doc_temp", O_RDONLY);
		if (fd)
			dup2(fd, STDIN_FILENO);
		if (fd == -1)
			return (0);
		close(fd);
	}
	if (!ft_strcmp(command->input.name, "file"))
	{
		fd = get_fd(command, command->input.type);
		if (fd >= 0)
			dup2(fd, STDIN_FILENO);
		if (fd == -1)
			return (0);
		close(fd);
	}
	return (1);
}

int	open_fd(t_command *cmd)
{
	if (cmd->is_runnable == false || cmd->has_file_err)
		return (-1);
	if (!cmd->name)
		return (0);
	if (!check_input_file(cmd))
		return (0);
	if (!check_output_file(cmd))
		return (0);
	return (1);
}
