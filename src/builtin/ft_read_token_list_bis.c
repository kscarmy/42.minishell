/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list_bis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:48:16 by guderram          #+#    #+#             */
/*   Updated: 2022/06/23 15:53:20 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_redirect_input(t_data *data, t_token *tok)
{
	int	fd;

	if (tok->prev == NULL || tok->prev->prev == NULL
		|| tok->prev->prev->arg == NULL)
		return (tok);
	fd = open(tok->prev->prev->arg, O_RDWR);
	if (fd < 0)
	{
		ft_putstr("bash: ");
		ft_putstr(tok->prev->prev->arg);
		ft_putstr(": No such file or directory\n");
		g_return = 1;
	}
	else
	{
		ft_fd_redir(data, fd, -10);
		ft_launch_cmd(data, tok);
		ft_pipe_close_data_fd(data, 0);
	}
	if (tok->prev != NULL && tok->prev->prev
		!= NULL && tok->prev->prev->prev != NULL)
		tok = tok->prev->prev;
	else
		tok = NULL;
	return (tok);
}

void	ft_read_token_list_bis(t_data *data, t_token *t)
{
	if (t != NULL && t->prev != NULL && t->prev->sep == 2)
	{
		ft_pipe_close_data_fd(data, 1);
		ft_pipe_out(data);
	}
	if (t != NULL && t->cmd != -1)
		ft_launch_cmd(data, t);
}

void	ft_read_token_list(t_data *data)
{
	t_token	*t;

	ft_print_token_list(data);
	t = ft_ret_last_token(data);
	while (data->exit == 0 && t != NULL)
	{
		t = ft_read_token_list_cat(data, t);
		if (t != NULL && t->prev != NULL
			&& (t->prev->sep == 3 || t->prev->sep == 5))
			t = ft_read_token_list_while_redir(data, t);
		if (t != NULL && t->prev != NULL && t->prev->sep == 4)
			t = ft_redirect_input(data, t);
		if (t != NULL && t->next != NULL && t->next->sep == 2)
			ft_pipe_in(data);
		if (t != NULL && t->prev == NULL)
			ft_pipe_close_data_fd(data, 1);
		if (t != NULL && t->prev != NULL && t->prev->sep == 6)
			t = ft_here_doc(data, t);
		ft_read_token_list_bis(data, t);
		if (t != NULL && t->prev != NULL)
			t = t->prev;
		else
			t = NULL;
	}
}

void	ft_print_token_list(t_data *data)
{
	t_token	*token;
	int		i;

	token = data->token;
	i = 0;
	printf("\n");
	while (token != NULL)
	{
		printf("-------------------------------\n");
		printf("Tok adr %p -- ", token);
		printf("cmd %d sep %d", token->cmd, token->sep);
		if (token->arg != NULL)
			printf(" arg '%s'", token->arg);
		while (token->bin != NULL && token->bin[i])
		{
			printf(" %p '%s'", token->bin[i], token->bin[i]);
			i++;
		}
		printf("\n");
		token = token->next;
	}
	printf("-------------------------------\n");
}
