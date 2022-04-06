/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:49:06 by guderram          #+#    #+#             */
/*   Updated: 2022/04/03 10:23:49 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"





// void	ft_init_pipe(t_data *data) // init les pipes
// {
// 	if (pipe(data->tube) < 0)
// 	{
// 		data->err = 10000;
// 		data->exit = 1;
// 	}
// }

void	ft_pipe_out(t_data *data) // redirige la sortie de la prochaine commande dans le TMP_OUT
{
	data->pipe->ofd_o = dup(1);
	// ft_pipe_close_data_fd(data, 1);
	unlink(TMP_OUT);
	open(TMP_OUT, O_CREAT, 00777);
	data->pipe->fd_o = open(TMP_OUT, O_RDWR);
	if (data->pipe->fd_o > 0)
	{
		// close(1);
		dup2(data->pipe->fd_o, 1);
	}
	else
		data->err = 10001;
	// ft_pipe_close_data_fd(data, 0);
}

void	ft_copy_fd(int fd_s, int fd_d) // copy le fd source dans le fd dest
{
	int	i;
	// int	ret;
	char	buff[2];

	i = 0;
	while(read(fd_s, buff, 1) > 0)
	{
		write(fd_d, buff, 1);
	}
	// printf
}

void	ft_pipe_in(t_data *data) // redirige l'entree de la prochaine commande dans le tmp_file
{
	int		out;
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	printf("pipe in\n");
	data->pipe->ofd_i = dup(0);
	// ft_pipe_close_data_fd(data, 0);
	out = open(TMP_OUT, O_RDWR);
	printf("pipe in2 %d\n", out);
	// while (out > 0 && get_next_line(out, &str) > 0 && i<5) // copie OUT dans str
	// 	i++;
	// printf("pipe in3\n");
	// i = 0;
	unlink(TMP_IN);
	open(TMP_IN, O_CREAT, 00777);
	data->pipe->fd_i = open(TMP_IN, O_RDWR);
	if (data->pipe->fd_i > 0)
		ft_copy_fd(out, data->pipe->fd_i);

	if (data->pipe->fd_i > 0)
	{
		close(0);
		dup2(data->pipe->fd_i, 0);
	}
	else
		data->err = 10001;
}

void	ft_pipe_close_data_fd(t_data *data, int	fd) // ferme le fd, si fd == 0 ferme out sinon in
{
	
	if (fd == 1 || fd == 3)
	{
		close(data->pipe->fd_o);
		data->pipe->fd_o = -10;
		dup2(data->pipe->ofd_o, 1);
		close(data->pipe->ofd_o);
		data->pipe->ofd_o = -10;
	}
	if (fd == 0 || fd == 3)
	{
		// // dup2(0, data->pipe->fd_o);
		// if (data->pipe->fd_i != STDOUT_FILENO)
		// 	close(data->pipe->fd_i);
		// data->pipe->fd_i = -10;
		// dup2(0, 0);
		close(data->pipe->fd_i);
		data->pipe->fd_i = -10;
		dup2(data->pipe->ofd_i, 0);
		close(data->pipe->ofd_i);
		data->pipe->ofd_i = -10;
	}
}
