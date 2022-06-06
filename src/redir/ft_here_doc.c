/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:17:02 by guderram          #+#    #+#             */
/*   Updated: 2022/06/06 13:27:42 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token *ft_here_doc(t_data *data, t_token *t) // fonction de gestion de '<<'
{
	char *tmp;
	int exit;
	int size;
	// int max = 0; // A SUPP
	int fd_in;

	// printf("here_doc : entree\n");
	exit = 0;
	size = ft_str_size(t->prev->prev->bin[0]);
	unlink(TMP_IN);
	// printf("size : %d\n", size);
	fd_in = open(TMP_IN, O_CREAT | O_RDWR | O_APPEND, 00777);
	ft_pipe_close_data_fd(data, 3);
	while (exit == 0)
	{
		// printf ("1 exit : %d\n", exit);
		tmp = readline("> ");
		if (ft_strncmp(tmp, t->prev->prev->bin[0], size) == 0)
		{
			exit++;
			// printf ("2 exit : %d\n", exit);
		}
		else
		{
			// printf("tmp : <%s>\n", tmp);
			ft_putstr_fd(tmp, fd_in);
			ft_putchar_fd('\n', fd_in);
		}
		// printf ("3 exit : %d\n", exit);
		// max++;
	}
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
	// printf("here_doc : sortie\n");
	return (t);
}
