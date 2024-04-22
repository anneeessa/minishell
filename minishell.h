/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:15:51 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/29 15:46:01 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_HERE_DOC 300

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <limits.h>
# include <stdbool.h>
# include <dirent.h>
# include "libft/libft.h"

int	g_exit_status;

typedef enum s_tokenstype
{
	NONE = -1,
	B_COMMAND,
	PIPE,
	GREAT,
	LESS,
	GREAT_GREAT,
	LESS_LESS,
	UNKNOWN,
	DELIMITER,
}	t_tokenstype;

typedef struct s_token
{
	t_tokenstype	type;
	int				tok_len;
	char			*value;
}	t_token;

typedef struct s_redirection
{
	char			*name;
	char			*filename;
	t_tokenstype	type;
	bool			is_delimiter_in_quote;
}	t_redirection;

typedef struct s_command
{
	char				*name;
	char				**args;
	char				*cmd_path;
	bool				is_runnable;
	bool				has_file_err;
	t_redirection		input;
	t_redirection		output;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	char		*input;
	char		**env;
	char		*copy_input;
	int			no_of_pipes;
	char		*path;
	int			input_fd;
	t_token		*tokens;
	int			exit_status;
	char		**splitted_path;
	t_command	*command;
	int			stop_heredoc;
	int			*pipe_end;
	int			*p_end;
	int			export_fds[2];
	char		**env_sorted;
}	t_data;

// init.c
char		**copy_env(char **envp, int add);
int			only_space(char *input, t_data **data);
int			init_data(t_data **data);
void		check_exit_status(t_data **data);

// space_quote.c
bool		handle_db_quotes(t_data **data);
void		handle_extra_spaces(char **copy_of_input, t_data **data);
char		*remove_extra_space_2(char **input, char **result, int j);
int			if_quote(char **input, char **result, int *j, int *i);

//seperate_char.c
int			separate_characters(t_data **data, char	**input);
void		separate_characters_utils(char *input, int *i, int *j,
				char **result);
void		separate(char **result, char *input, int *i, int *j);

void		mini_loop(t_data **data);
int			main(int argc, char **argv, char **env);
void		increment_shlvl(t_data **data);

//lexer.c
int			lex(t_data **data);
char		*remove_quote_cwd(t_data **data, int i);
int			check_dir_existance(t_data **data, t_token *tokens, int i,
				char *str);

//lexer1.c
char		**split_input(char *str, char c);
void		splitting(char *str, int i, char ***strings, char c);
char		*ft_word(char *str, char c);
int			count_strings(char *str, char c);
int			len_inside_quote(char *str, int i, char c);

//token.c
int			len_splitted(char **splitted);
void		count_pipes(t_data **data, t_token *tokens);
void		check_capitals(t_token *token, char **splitted, int tok_no);
void		get_tokentype(t_token *token, char **splitted, int tok_no);
void		build_tokens(t_data **data);

//syntax.c
int			syntax_errors(t_data **data, t_token *tokens, int i);
int			check_syntax_error2(t_data **data, t_token *tokens, int i);
int			check_cmd_exist(t_data **data, t_token *tokens, int i);

//free.c
void		free_db_array(char ***str);
void		free_tokens(t_data **data);
void		perror_free(t_data **data, char *str, char *value, int free_only);
void		print_error(char *s1, char *s2, char *s3);
void		print_error2(char *s1, char *s2, char *s3);
void		free_memory(t_data **data, int free_env);

// quote.c
void		copy_till_quote(char *str, char **result, int *i, int *j);
void		quote3(char ***arr, int *i, int *j, bool *quote);
void		rm_quote2(char ***arr, int i, bool quote);
void		rm_quote(t_data **data);

// dir.c +3 static fn
int			is_directory(int count_pipes, char *str, t_tokenstype type,
				bool *is_pipe);
char		*get_directory(char *value);

// // parser.c
int			parser(t_data **data);
void		construct_command(t_data **data, int *i, char **arg);
int			check_command_exist(t_data **data, int i, int token_len);

// marker.c
void		update_hasfile_err(t_command **cmd);
void		mark_commands(t_data **data);

// parsing_utils.c
t_command	*getlast(t_command *lst);
int			get_double_pointer_len(char **arr);
bool		handle_unclosed_quotes(t_data **data);

//redirections.c
void		identify_redirections(t_data **data, int *i);
void		if_output_ri(t_data **data, int *i, t_command *cmd,
				t_tokenstype type);
void		if_here_doc(t_command *cmd, t_data **data, int *i);
char		*remove_quotes(const char	*str, t_command *cmd);

//full_path_handler.c
int			find_command(t_data **data, char *str);
int			find_command_without_perror(t_data **data, char *str);
char		*get_full_path(char *dir, char *command, char *fullPath);
int			is_cmd_executable_without_perror(char *str);

//check_command.c
int			is_non_b_command(char *str, t_data **data, int count_pipes);
int			command_present(t_data **data, int i, int token_len);

void		handle_signals(void);
void		signal_controller(int sig_num);

//executor.c
void		handle_exc(t_data **data);
void		exe_b_cmd(char *command_name, char **command_arguments, \
			t_data **data, t_command *temp);
void		run_cmd(t_data **data, t_command *command, \
			char **full_path, t_command	*temp_cmd);

// builtin
void		ft_echo(char **arguments, t_data **data);
void		ft_pwd(void);
void		ft_cd(char **arguments, t_data **data);
void		ft_exit(t_data **data, char **args);
void		ft_env(char **arg, t_data **data);

//export && export utils
void		ft_export(t_data **data, char **arguments);
int			len_char(char *str, char c);
void		sort_envp(t_data **data, char c);
void		put_envp(char **env, t_data **data, int i);

//unset
void		ft_unset(char **args, t_data **data);

//free
// void		free_double_array(char ***str);
void		free_tokens(t_data **data);
void		free_command(t_command *command);
void		free_memory(t_data **data, int free_env);

// exec_utils
void		ft_create_pipe(t_data **data);
int			get_pid(t_command *cmd);
int			is_builtin(char *command_name);
void		close_pipes(t_data **data, int i);
char		*find_fullpath(t_data **data, t_command *command, \
			char **full_path);
int			wait_child_process(t_data **data, int status);

//exec_multiple_cmds
void		execute_multiple_cmd(t_data **data);
void		exit_from_child(t_data **data, t_command *temp_cmd,
				int e_status);

//exec_sngle_cmd
void		exec_one_cmd(t_data **data, t_command *command);

// fd_handler.c
int			get_fd(t_command *command, int token_type);
int			open_fd(t_command *command);

//here doc
int			get_here_doc(t_command *cmd, t_data **data);
int			check_here_doc(t_data **data);

//signal handler
void		handle_signals(void);
void		rl_replace_line(const char *text, int clear_undo);
void		child_signal_handler(int num);
void		signal_controller(int sig_num);
void		here_doc_signal(int sig_num);
void		child_signals(t_command *cmd);
void		sigint_here_doc_handler(int sig);
void		sigint_child_here_doc_handler(int sig);

//expander
char		*search_value(char *var_name, t_data **data);
int			expand(t_data **data);
char		*check_expansion(char *arg, t_data **data);
void		expand_variable(char **result, size_t *i, t_data **data);
char		*find_var_name(char *result, size_t *i);
int			replace_tilde_with_home(t_data **data);

#endif