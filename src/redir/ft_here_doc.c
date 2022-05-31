/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:17:02 by guderram          #+#    #+#             */
/*   Updated: 2022/05/30 15:25:11 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token *ft_here_doc(t_data *data, t_token *t) // fonction de gestion de '<<'
{
	char *tmp;
	int exit;
	int size;
	int max = 0; // A SUPP
	int fd_in;

	// printf("here_doc : entree\n");
	exit = 0;
	size = ft_str_size(t->prev->prev->arg);
	unlink(TMP_IN);
	// pid_t	pid;
	// printf("size : %d\n", size);
	fd_in = open(TMP_IN, O_CREAT | O_RDWR | O_APPEND, 00777);
	ft_pipe_close_data_fd(data, 3);
	// pid = fork();
	// if (pid == -1)
	// 	printf("ERREUR FORK HERE DOC\n");
	// else if (pid == 0)
	// {
	while (exit == 0 && max < 5)
	{
		tmp = readline("> ");
		if (ft_strncmp(tmp, t->prev->prev->arg, size) == 0)
			exit++;
		else
		{
			// printf("tmp : <%s>\n", tmp);
			ft_putstr_fd(tmp, fd_in);
			ft_putchar_fd('\n', fd_in);
		}
		max++;
	}
	// }
	// waitpid(pid, &g_return, 0);
	close (fd_in);
	fd_in = open(TMP_IN, O_CREAT | O_RDWR | O_APPEND, 00777);
	ft_fd_redir(data, fd_in, -10);
	ft_launch_cmd(data, t);
	// printf("here_doc : sortie fork\n");
	if (t->prev != NULL && t->prev->prev != NULL && t->prev->prev->prev != NULL)
	{
		// printf("here_doc : if prev\n");
		t = t->prev->prev->prev;
	}
	else
	{
		// printf("here_doc : if else\n");
		t = NULL;
	}
	// printf("here_doc : sortie\n");
	ft_pipe_close_data_fd(data, 3);
	return (t);
}
