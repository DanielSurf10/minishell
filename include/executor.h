/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:43:47 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/18 11:00:34 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define PATH_MAX 4096

//****************************************************************************//
//                                  Includes                                  //
//****************************************************************************//

# include "lexing.h"
# include "expander.h"
# include "parsing.h"
# include "minishell.h"

//****************************************************************************//
//                                  Structs                                   //
//****************************************************************************//

typedef struct s_builtin
{
	int		fd_redir;
	int		args_num;
	int		ret_code;
	char	*cmd;
	char	**argv;
	char	**envp;
}	t_builtin;

typedef struct s_cmd_for_fork
{
	int		fd_redir;
	int		args_num;
	int		ret_code;
	char	*cmd;
	char	**argv;
	char	**envp;
}	t_cmd_for_fork;

//****************************************************************************//
//                                 Functions                                  //
//****************************************************************************//

//****************************************************************************//
//                                 Execution                                  //
//****************************************************************************//

int		exec_or(t_exec_tree *tree, t_minishell *data);
int		exec_and(t_exec_tree *tree, t_minishell *data);
int		exec_tree(t_exec_tree *tree, t_minishell *data);
int		open_redir(char *path_to_file, int type);
int		is_directory(char *path);
int		exec_cmd(t_exec_tree *tree, t_minishell *data);
int		exec_cmd_fork(t_exec_tree *tree, t_minishell *data);
int		exec_pipe(t_exec_tree *tree, t_minishell *data);
char	**create_argv(t_exec_tree *tree, t_minishell *data);

//****************************************************************************//
//                                Built-ins                                   //
//****************************************************************************//

int		exec_builtin(t_exec_tree *tree, t_minishell *data);
int		is_built_in(t_exec_tree *tree);
int		verify_built_in(char *command);
int		builtin_echo(char *args[]);
int		builtin_pwd(void);
int		builtin_env(t_minishell *data);
int		builtin_export(char **argv, t_minishell *data);
int		builtin_unset(char **argv, t_envp_list **envp_list);
int		builtin_exit(char **argv, t_minishell *data);
int		builtin_cd(char *args[], t_minishell *data);
int		key_exist(char *key, t_envp_list *envp_list);
void	export_print_error_message(char *key_value);
void	print_envp(char **envp);
void	print_sorted_envp(t_minishell *data);

//****************************************************************************//
//                                  Fd_list                                   //
//****************************************************************************//

int		close_fd(int fd);
int		key_is_valid(char *key);
int		get_return_value(int status);
void	fd_list_add_fd(t_list **fd_list, int fd);
void	fd_list_close_clear(t_list **fd_list);
void	close_pipe(int *pipe_fd);
void	init_signals(void);
void	execution_signals(int pid);
void	heredoc_signals(void);

//****************************************************************************//
//                                  signals                                   //
//****************************************************************************//

void	sig_handler_heredoc(int signal);
void	sig_handler_sigint(int signal);
void	sig_handler_sigint(int signal);
void	sig_handler_redo_readline(int signal);

#endif
