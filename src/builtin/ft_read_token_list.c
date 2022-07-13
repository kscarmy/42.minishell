/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:17 by guderram          #+#    #+#             */
/*   Updated: 2022/07/13 10:22:05 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_ret_last_token(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	ft_launch_cmd(t_data *data, t_token *token)
{
	if (token->cmd == 7)
		ft_exit(data, token);
	else
		g_return = 0;
	if (token->cmd == 1)
		ft_echo(data, token);
	if (token->cmd == 2)
		ft_pwd(data);
	if (token->cmd == 3)
		ft_export(data, token);
	if (token->cmd == 4)
		ft_env(data, token);
	if (token->cmd == 6 && token->prev == NULL && token->next == NULL)
		ft_cd(data, token);
	if (token->cmd == 8)
		ft_unset(data, token);
	if (token->cmd == 9)
		ft_is_bin(data, token);
}

t_token	*ft_read_token_list_while_pipe(t_data *data, t_token *t)
{
	ft_pipe_in(data);
	if (t->prev != NULL && t->prev->prev != NULL && t->prev->prev->prev != NULL)
		t = t->prev->prev->prev;
	else
		t = NULL;
	return (t);
}

t_token	*ft_read_token_list_while_redir_bis(t_data *data, t_token *t, int *fd)
{
	while (data->err == 0 && t != NULL && t->prev != NULL
		&& t->prev->prev != NULL
		&& (t->prev->sep == 3 || t->prev->sep == 5))
	{
		if (*fd != -10)
		{
			close (*fd);
			*fd = -10;
		}
		if (t->prev->prev == NULL || t->prev->prev->bin == NULL)
			data->err = 1230;
		if (t->prev->sep == 3)
			*fd = ft_create_open_file(data, t->prev->prev->bin[0], 1);
		else
			*fd = ft_create_open_file(data, t->prev->prev->bin[0], 0);
		if (t->prev->prev != NULL && t->prev->prev->prev != NULL
			&& (t->prev->prev->prev->sep == 3 || t->prev->prev->prev->sep == 5))
			t = t->prev->prev;
		else
			break ;
	}
	return (t);
}

t_token	*ft_read_token_list_while_redir(t_data *data, t_token *tok)
{
	int		fd;
	t_token	*t;

	fd = -10;
	t = tok;
	if (!(t != NULL && t->prev != NULL && t->prev->prev != NULL))
	{
		ft_putstr("bash: syntax error near unexpected token `newline'\n");
		g_return = 2;
		return (NULL);
	}
	t = ft_read_token_list_while_redir_bis(data, tok, &fd);
	if (tok != NULL && tok->cmd != -1)
	{
		ft_fd_redir(data, -10, fd);
		ft_launch_cmd(data, tok);
		ft_pipe_close_data_fd(data, 3);
	}
	if (t->prev != NULL && t->prev->prev != NULL && t->prev->prev->prev != NULL)
		t = t->prev->prev->prev;
	else
		t = NULL;
	return (t);
}
