/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:35:41 by guderram          #+#    #+#             */
/*   Updated: 2022/06/25 14:56:00 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../src/libft/includes/libft.h"

# define BUFFER_SIZE_GNL 128
# define TMP_OUT ".minishell_tmp_out"
# define TMP_IN ".minishell_tmp_in"
# define TMP_HERE ".minishell_tmp_here_doc"

/*	***********	*/
/*	   data		*/
/*	***********	*/

typedef struct p_data
{
	int				dol;
	int				cat;
	int				exit;
	int				err;
	int				i;
	char			**env;
	char			*input;
	char			*pwd;
	char			*opwd;
	char			*tmp;
	struct p_token	*token;
	struct p_var	*var;
	struct p_pipe	*pipe;
}				t_data;

/*	**************	*/
/*		token		*/
/*	**************	*/

typedef struct p_token
{
	int				sep;
	int				cmd;
	int				option;
	char			**bin;
	char			*arg;
	struct p_token	*next;
	struct p_token	*prev;

}				t_token;

/*	**********	*/
/*		pipe	*/
/*	**********	*/

typedef struct p_pipe
{
	int				ofd_o;
	int				ofd_i;
	int				fd_o;
	int				fd_i;
}				t_pipe;

/*	**********	*/
/*		var		*/
/*	**********	*/

typedef struct p_var
{
	char			*name;
	char			*value;
	struct p_var	*next;
	struct p_var	*prev;
}				t_var;

/*	***********	*/
/*	   global	*/
/*	***********	*/

extern int			g_return;

/*	*************	*/
/*		INIT		*/
/*	*************	*/

/*	ft_init_token.c	*/
void	ft_init_token(t_data *data);
void	ft_add_new_token(t_data *data);
void	ft_free_token(t_data *data, t_token *token);
void	ft_delete_token(t_data *data, t_token *delete);

/*	ft_init_data.c	*/
int		ft_init_data(t_data *data, char **env);
void	ft_init_pipe(t_data *data);
void	ft_init_data_bis(t_data *data);

void	ft_create_var_var(t_data *data, char *str);
void	ft_init_data_pwd(t_data *data);

/*	ft_init_var.c	*/
void	ft_init_var(t_data *data);
void	ft_add_new_var(t_data *data);
void	ft_free_var(t_data *data, t_var *var);
void	ft_delete_var(t_data *data, t_var *delete);

/*	*****************	*/
/*		PARSE_ARG		*/
/*	*****************	*/

/*	ft_parse_arg.c	*/
int		ft_size_of_arg(t_data *data);
void	ft_size_of_arg_bis(t_data *data, int *i, int *u, int *cd);
void	ft_size_of_arg_bis_bis(t_data *data, int *u, int *cd);
int		ft_incre_one_arg(t_data *data, int u);
void	ft_malloc_builtin_arg(t_data *data, t_token *tok);

/*		ft_malloc_arg.c		*/
void	ft_malloc_arg(t_data *data, t_token *tok);
void	ft_malloc_arg_pre_b(t_data *data, t_token *tok, int *u, int *cd);
void	ft_malloc_arg_bis(t_data *data, t_token *tok, int *u, int *cd);
void	ft_malloc_arg_bis_bis(t_data *data, t_token *tok, int *u, int *cd);
void	ft_malloc_arg_bbb(t_data *data, t_token *tok, int *u, int *cd);

/*		ft_malloc_arg_bis.c		*/
void	ft_malloc_arg_bbbb(t_data *data, t_token *tok, int *u, int *i);
void	ft_malloc_arg_end(t_data *data, int *u, int *size);
char	*ft_one_simple_arg(t_data *data, int i);

/*		ft_one_arg.c		*/
char	*ft_one_arg(t_data *data, int u);
void	ft_one_arg_b(t_data *data, int u, int *i, int *cd);
void	ft_one_arg_bb(t_data *data, int u, int *i, int *cd);
void	ft_one_arg_bbb(t_data *data, int u, int *i, int *cd);
void	ft_one_arg_bbbb(t_data *data, int u, int *i, int *cd);

/*		ft_size_one_arg.c		*/
int		ft_size_one_arg(t_data *data, int s);
int		ft_size_one_arg_b(t_data *da, int s, int *u, int *ret);
int		ft_size_one_arg_bb(t_data *da, int s, int *u, int *ret);
int		ft_size_one_arg_bbb(t_data *da, int s, int *u);
int		ft_size_one_arg_bbbb(t_data *da, int s, int *u, int *ret);

/*	*************	*/
/*		UTILS		*/
/*	*************	*/

/*	ft_write.c	*/
int		ft_is_a_b(char a, char b);
int		ft_space(char *str, int i);
void	ft_print_one_var(t_var *var);
int		ft_str_comp_ascii(char *str1, char *str2);

/*	ft_str.c	*/
void	ft_str_join_input(t_data *data, int i, int max);
char	*ft_strncpy(char *dest, char *src, int n);
int		ft_is_separator(char *str, int i);
char	*ft_malloc_str(t_data *data, int i);
int		ft_str_size(char *str);

/*	ft_str_bis_bis.c	*/
int		ft_check_char(char *str, char c, int max);
int		ft_str_comp(char *str1, char *str2);

/*	ft_str_bis.c	*/
int		ft_str_after_cut(char *str);
void	ft_copie_dest_src(t_token *tok, char *src);
char	*ft_src_in_dest(t_data *data, char *dest, char *src, char sep);
char	*ft_str_cpy(char *stra, char *strb);
char	*ft_src_in_dest_bis(char *dest, char *src, char *ret, char sep);

/*	ft_str_bis_bis.c	*/
int		ft_check_char(char *str, char c, int max);
int		ft_str_comp(char *str1, char *str2);
int		ft_is_number(char c);

/*	**************	*/
/*		PARSING		*/
/*	**************	*/

/*	ft_cut_unset.c	*/
int		ft_cut_unset(t_data *data, char *str);
void	ft_create_unset_token(t_data *data);

/*	ft_cut_export.c	*/
void	ft_create_export_token(t_data *data);
int		ft_cut_export(t_data *data, char *str);

/*	ft_cut_export_bis.c	*/
void	ft_create_export_token(t_data *data);
void	ft_export_in_bin(t_data *data, int nb);
int		ft_export_sizeof_arg(char	*str, int i);

/*	ft_cut_pwd.c	*/
int		ft_cut_pwd(t_data *data, char *str);
void	ft_create_pwd_token(t_data *data);

/*	ft_cut_input.c	*/
int		ft_parse_input(t_data *data);
void	ft_parse_input_interpret(t_data *data);
void	ft_parse_input_bis(t_data *data, int *found, char *str);

/*	ft_cut_echo.c	*/
int		ft_cut_echo(t_data *data, char *str);
void	ft_create_echo_token(t_data *data);

/*	ft_clear_token.c	*/
void	ft_clear_token_list(t_data *data);
void	ft_clear_for_new_input(t_data *data);

/*	ft_cut_env.c	*/
int		ft_cut_env(t_data *data, char *str);
void	ft_create_env_token(t_data *data);

/*	ft_cut_exit.c	*/
int		ft_cut_exit(t_data *data, char *str);
void	ft_create_exit_token(t_data *data);

/*	ft_cut_cd.c	*/
int		ft_cut_cd(t_data *data, char *str);
void	ft_create_cd_token(t_data *data);

/*	ft_cut_bin.c	*/
int		ft_cut_bin(t_data *data, char *str);
void	ft_create_bin_token(t_data *data);
void	ft_malloc_bin(t_data *data);
int		ft_bin_arg_size(t_data *data, int i);
int		ft_bin_count(t_data *data, int i);
char	*ft_str_malloc_cpy(t_data *data, char	*str);
int		ft_bin_size(t_data *data);

/*	history.c	*/
int		cut_history(t_data *data);
void	ft_create_history_token(t_data *data);

/*	cd.c		*/
int		cut_cd(t_data *data);
int		change_dir(t_data *data);
void	ft_create_cd_token(t_data *data);

/*	cut_str		*/
char	*cut_str(t_data *data, char *str);

/*	 quotes		*/
char	*put_env(t_data *data, char *str, int i);
char	*ft_quote(t_data *data, char *str, int i);

/*		 ft_cut_redirects		*/
int		ft_cut_redirects(t_data *data);
void	ft_create_redirects_token(t_data *data, int i);

t_token	*ft_here_doc(t_data *data, t_token *t);

/*		ft_pre_parsing.c		*/
int		ft_is_input_safe(char *str);
int		ft_is_input_safe_quotes(char *str, int *i);

/*		ft_quote.c		*/
char	*ft_ret_double_quote(t_data *data, char *str, int incr);
char	*ft_ret_dollar(t_data *data, char *str);
char	*ft_ret_simple_quote(t_data *data, char *str, int incr);
void	ft_ret_double_quote_size(t_data *data, char *str, int *i, int *u);
void	ft_ret_double_quote_fill(t_data *data, char *str, int *i, int *u);
void	ft_ret_double_quote_b(t_data *data, char *str, char *ret);

/*		ft_dol.c		*/
char	*ft_ret_dollar_single(void);
char	*ft_ret_dollar_ret(t_data *data, char *str);
char	*ft_ret_dollar_ret(t_data *data, char *str);

/*	**************	*/
/*		BUILTIN		*/
/*	**************	*/

/*	ft_echo.c	*/
void	ft_echo(t_data *data, t_token *token);
int		ft_echo_option(t_token *t, int u);

/*	ft_read_token_list.c	*/
t_token	*ft_read_token_list_while_pipe(t_data *data, t_token *t);
void	ft_launch_cmd(t_data *data, t_token *token);
t_token	*ft_ret_last_token(t_data *data);
void	ft_print_token_list(t_data *data);
t_token	*ft_read_token_list_while_redir(t_data *data, t_token *tok);
t_token	*ft_redirect_input(t_data *data, t_token *tok);
t_token	*ft_read_token_list_while_redir_bis(t_data *data, t_token *t, int *fd);
int		ft_while_token(t_data *data);

/*	ft_read_token_list_bis.c	*/
t_token	*ft_redirect_input(t_data *data, t_token *tok);
void	ft_read_token_list_bis(t_data *data, t_token *t);
void	ft_read_token_list(t_data *data);
void	ft_print_token_list(t_data *data);

/*	ft_read_token_list_bis_bis.c	*/
t_token	*ft_read_token_list_cat(t_data *data, t_token *tok);
int		ft_read_token_list_cat_while(t_token *t);

/*	ft_pwd.c	*/
void	ft_pwd(t_data *data);

/*	ft_env.c	*/
void	ft_env(t_data *data, t_token *token);

/*	ft_unset.c	*/
void	ft_unset(t_data *data, t_token *token);
char	*ft_unset_malloc_str(t_data *data, char *str);

/*	ft_export.c	*/
int		ft_export_bin_equal(char *str);
void	ft_export_in_var(t_data *data, t_token *token, int i);
void	ft_parse_export_name(t_data *data, t_token *token, int i);
void	ft_export(t_data *data, t_token *token);

/*	ft_cd.c	*/
void	ft_cd(t_data *data, t_token *token);
void	ft_cd_home(t_data *data);
void	ft_cd_goto_path(t_data *data, char *path);
void	ft_cd_goto_opwd(t_data *data, char *path);
void	ft_cd_goto_path_bis(t_data *data);

/*	ft_cd.c	*/
void	ft_cd_from_data_to_var_opwd(t_data *data);
void	ft_cd_from_data_to_var_pwd(t_data *data);

/*	ft_exit.c	*/
int		ft_resize_g_return(int i);
void	ft_exit(t_data *data, t_token *token);
void	ft_exit_bis(t_data *data, t_token *tok, int i, int ret);

/*	**********	*/
/*		VAR		*/
/*	**********	*/

/*	ft_var.c	*/
t_var	*ft_found_var_name(t_data *data, char *str);
void	ft_disp_all_var(t_data *data, char sep, int export);

/*	ft_var_sort.c	*/
t_var	*ft_found_first_var(t_data *data);

/*	**********	*/
/*		BIN		*/
/*	**********	*/

/*	ft_bin.c	*/
char	*ft_malloc_one_var(t_data *data, t_var *var);
void	ft_malloc_var(t_data *data);
int		ft_bin_path(t_data *data, t_var *var, t_token *tok, int i);
void	ft_free_data_env(t_data *data);
void	ft_bin_path_bis(t_data *data, t_token *tok, int *u, int *y);

/*	ft_bin_bis.c	*/
void	ft_bin_execve(t_data *data, t_token *token);
void	ft_arg_path_bin(t_data *data, t_token *token);
void	ft_is_bin(t_data *data, t_token *token);
void	ft_is_bin_bis(t_data *data, t_token *token, t_var *var, int *i);

/*	**********	*/
/*	 Signals	*/
/*	**********	*/
void	ft_handler(int sig);
void	ft_handler_heredoc(int sig);
void	ft_handler_pid(int sig);
void	ft_init_signals(void);

/*	*******	*/
/*	 REDIR	*/	
/*	*******	*/

/*	ft_pipe.c	*/
void	ft_pipe_out(t_data *data);
void	ft_pipe_in(t_data *data);
void	ft_pipe_close_data_fd(t_data *data, int fd);
void	ft_copy_fd(int fd_s, int fd_d);

/*	ft_in_file.c	*/
int		ft_create_open_file(t_data *data, char *name, int create);
void	ft_fd_redir(t_data	*data, int fd_in, int fd_out);

/*		ft_here_doc.c	*/
t_token	*ft_here_doc(t_data *data, t_token *t);
void	ft_heredoc_fork(t_token *t, int fd_in, int size);
t_token	*ft_here_doc_bis(t_data *data, t_token *t);

/*	*******	*/
/*	 FREE	*/
/*	*******	*/

/*	ft_free.c	*/
void	ft_free_minishell(t_data *data);
void	ft_free_minishell_bis(t_data *data);

#endif
