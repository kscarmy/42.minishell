/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:46:04 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 14:05:59 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_create_open_file(t_data *data, char *name, int create)
{
	int	fd;

	if (create == 1)
		unlink(name);
	fd = open(name, O_CREAT | O_RDWR | O_APPEND, 00777);
	if (fd < 0)
		data->err = 1234;
	return (fd);
}

void	ft_fd_redir(t_data	*data, int fd_in, int fd_out)
{
	if (fd_in > 0)
	{
		data->pipe->ofd_i = dup(0);
		data->pipe->fd_i = fd_in;
		dup2(data->pipe->fd_i, 0);
	}
	if (fd_out > 0)
	{
		data->pipe->ofd_o = dup(1);
		data->pipe->fd_o = fd_out;
		dup2(data->pipe->fd_o, 1);
	}
}
