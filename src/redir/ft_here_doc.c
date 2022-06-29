/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:17:02 by guderram          #+#    #+#             */
/*   Updated: 2022/06/27 16:04:34 by guderram         ###   ########.fr       */
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
	if (t->prev != NULL && t->prev->prev != NULL && t->prev->prev->prev != NULL)
		t = t->prev->prev->prev;
	else
		t = NULL;
	ft_pipe_close_data_fd(data, 3);
	return (t);
}

void	ft_heredoc_fork(t_token *t, int fd_in, int size)
{
	char	*tmp;
	int		ex;

	ex = 0;
	while (ex == 0 && g_return == 0)
	{
		printf("ft_heredoc_fork :\n");
		tmp = readline("> ");
		if (g_return == 0 && tmp == NULL)
		{
			ft_putstr("bash: warning: here-document (wanted `");
			ft_putstr(t->prev->prev->bin[0]);
			ft_putstr("')\n");
			break ;
		}
		if (g_return == 0 && ex == 0
			&& ft_strncmp(tmp, t->prev->prev->bin[0], size) == 0)
			ex++;
		else if (g_return == 0 && ex == 0)
		{
			ft_putstr_fd(tmp, fd_in);
			ft_putchar_fd('\n', fd_in);
		}
		ft_strdel(&tmp);
	}
	exit(0);
}

t_token	*ft_here_doc(t_data *data, t_token *t)
{
	pid_t	pid;
	int		fd_in;

	pid = fork();
	printf("ft_here_doc\n");
	ft_pipe_close_data_fd(data, 3);
	unlink(TMP_IN);
	if (pid == -1)
		data->err = 5000;
	else if (pid == 0)
	{
	fd_in = open(TMP_IN, O_CREAT | O_RDWR | O_APPEND, 00777);
	signal(SIGINT, ft_handler_heredoc);
	signal(SIGQUIT, ft_handler_heredoc);
	ft_heredoc_fork(t, fd_in, ft_str_size(t->prev->prev->bin[0]));
	}
	waitpid(pid, &g_return, 0);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	if (g_return != 130)
		return (ft_here_doc_bis(data, t));
	else
	{
				ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return (NULL);
}
