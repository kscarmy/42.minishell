/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:17:02 by guderram          #+#    #+#             */
/*   Updated: 2022/07/09 00:39:16 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_here_doc_bis(t_data *data, t_token *t)
{
	int	fd_in;

	fd_in = 0;
	fd_in = open(TMP_IN, O_CREAT | O_RDWR | O_APPEND, 00777);
	ft_fd_redir(data, fd_in, -10);
	ft_launch_cmd(data, t);
	ft_pipe_close_data_fd(data, 3);
	t = t->prev->prev;
	while (t != NULL)
	{
		if (t->prev != NULL && t->prev->sep == 6 && t->prev->prev != NULL)
			t = t->prev->prev;
		else
			t = NULL;
	}	
	return (t);
}

void	ft_heredoc_fork(char *str, int fd_in)
{
	char	*tmp;
	int		ex;

	ex = 0;
	while (ex == 0 && g_return == 0)
	{
		tmp = readline("> ");
		if (g_return == 0 && tmp == NULL)
		{
			ft_putstr("bash: warning: here-document (wanted `");
			ft_putstr(str);
			ft_putstr("')\n");
			break ;
		}
		if (g_return == 0 && ex == 0
			&& ft_strncmp(tmp, str, ft_str_size(str)) == 0)
			ex++;
		else if (g_return == 0 && ex == 0)
		{
			ft_putstr_fd(tmp, fd_in);
			ft_putchar_fd('\n', fd_in);
		}
		ft_strdel(&tmp);
	}
}

t_token	*ft_here_doc(t_data *data, t_token *t)
{
	printf("ft_here_doc\n");
	signal(SIGINT, ft_handler_heredoc);
	signal(SIGQUIT, ft_handler_heredoc);
	ft_here_doc_multi(data, t);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	if (g_return != 130)
		return (ft_here_doc_bis(data, t));
	else
	{
		ft_putstr_fd("\n", 1);
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return (NULL);
}

void	ft_here_doc_multi(t_data *d, t_token *t)
{
	pid_t	pid;
	int		fd_in;

	t = t->prev->prev;
	pid = fork();
	if (pid == -1)
		d->err = 5000;
	else if (pid == 0)
	{
		while (t != NULL)
		{
			ft_pipe_close_data_fd(d, 3);
			unlink(TMP_IN);
			fd_in = open(TMP_IN, O_CREAT | O_RDWR | O_APPEND, 00777);
			ft_heredoc_fork(t->bin[0], fd_in);
			if (t->prev != NULL && t->prev->sep == 6 && t->prev->prev != NULL)
				t = t->prev->prev;
			else
				t = NULL;
			close (fd_in);
		}
		exit(0);
	}
	waitpid(pid, &g_return, 0);
}
