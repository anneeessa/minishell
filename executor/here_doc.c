/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:04:49 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/23 23:05:57 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_and_putstr(t_command *cmd, t_data **data, char **line, int fd1)
{
	char	*expanded;

	if (cmd->input.is_delimiter_in_quote)
		expanded = ft_strdup(*line);
	else
		expanded = check_expansion(*line, data);
	write(fd1, expanded, ft_strlen(expanded));
	write(fd1, "\n", 1);
	free(*line);
	free(expanded);
}

void	signaled_here_doc(t_data **data, int fd1)
{
	g_exit_status = 127;
	unlink("libft/here_doc_sig");
	unlink("libft/here_doc_temp");
	dup2((*data)->input_fd, STDIN_FILENO);
	close((*data)->input_fd);
	close(fd1);
	free_memory(data, 0);
}

int	get_here_doc(t_command *cmd, t_data **data)
{
	int		fd1;
	char	*line;

	fd1 = open("libft/here_doc_temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (g_exit_status == EXIT_HERE_DOC)
			return (signaled_here_doc(data, fd1), 0);
		if (!line)
		{
			g_exit_status = 0;
			break ;
		}
		if (ft_strcmp(line, cmd->input.filename) == 0)
			break ;
		expand_and_putstr(cmd, data, &line, fd1);
	}
	close(fd1);
	return (1);
}

int	check_here_doc(t_data **data)
{
	t_command	*temp;

	temp = (*data)->command;
	while ((*data)->command)
	{
		if (!ft_strcmp((*data)->command->input.name, "here_doc"))
		{
			(*data)->command->has_file_err = false;
			signal(SIGINT, sigint_here_doc_handler);
			(*data)->input_fd = dup(STDIN_FILENO);
			if (get_here_doc((*data)->command, data) == 0)
				return (0);
			close((*data)->input_fd);
		}
		(*data)->command = (*data)->command->next;
	}
	(*data)->command = temp;
	return (1);
}
