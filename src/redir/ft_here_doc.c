/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:17:02 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 14:10:13 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_here_doc_bis(t_data *data, t_token *t, int fd_in)
{
	close (fd_in);
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

t_token	*ft_here_doc(t_data *data, t_token *t)
{
	char	*tmp;
	int		exit;
	int		size;
	int		fd_in;

	exit = 0;
	size = ft_str_size(t->prev->prev->bin[0]);
	unlink(TMP_IN);
	fd_in = open(TMP_IN, O_CREAT | O_RDWR | O_APPEND, 00777);
	ft_pipe_close_data_fd(data, 3);
	while (exit == 0)
	{
		tmp = readline("> ");
		if (ft_strncmp(tmp, t->prev->prev->bin[0], size) == 0)
			exit++;
		else
		{
			ft_putstr_fd(tmp, fd_in);
			ft_putchar_fd('\n', fd_in);
		}
		ft_strdel(&tmp);
	}
	return (ft_here_doc_bis(data, t, fd_in));
}
