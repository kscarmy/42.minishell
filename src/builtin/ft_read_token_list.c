/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:17 by guderram          #+#    #+#             */
/*   Updated: 2022/06/08 11:49:05 by guderram         ###   ########.fr       */
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
	if (token->cmd == 1)
		ft_echo(data, token);
	if (token->cmd == 2)
		ft_pwd(data);
	if (token->cmd == 3)
		ft_export(data, token);
	if (token->cmd == 4)
		ft_env(data, token);
	if (token->cmd == 6)
		ft_cd(data, token);
	if (token->cmd == 7)
		ft_exit(data, token);
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
	while (data->err == 0 && t->prev != NULL
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
	}
	return (t);
}

t_token	*ft_read_token_list_while_redir(t_data *data, t_token *tok)
{
	int		fd;
	t_token	*t;

	fd = -10;
	t = tok;
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

// t_token	*ft_redirect_input(t_data *data, t_token *tok)
// {
// 	int	fd;

// 	if (tok->prev == NULL || tok->prev->prev == NULL
// 		|| tok->prev->prev->arg == NULL)
// 		return (tok);
// 	fd = open(tok->prev->prev->arg, O_RDWR);
// 	if (fd < 0)
// 	{
// 		ft_putstr("bash: ");
// 		ft_putstr(tok->prev->prev->arg);
// 		ft_putstr(": No such file or directory\n");
// 		g_return = 1;
// 	}
// 	else
// 	{
// 		ft_fd_redir(data, fd, -10);
// 		ft_launch_cmd(data, tok);
// 		ft_pipe_close_data_fd(data, 0);
// 	}
// 	if (tok->prev != NULL && tok->prev->prev
// 		!= NULL && tok->prev->prev->prev != NULL)
// 		tok = tok->prev->prev;
// 	else
// 		tok = NULL;
// 	return (tok);
// }

// void	ft_read_token_list_bis(t_data *data, t_token *t)
// {
// 	if (t != NULL && t->prev != NULL && t->prev->sep == 2)
// 	{
// 		ft_pipe_close_data_fd(data, 1);
// 		ft_pipe_out(data);
// 	}
// 	if (t != NULL && t->cmd != -1)
// 		ft_launch_cmd(data, t);
// }

// void	ft_read_token_list(t_data *data)
// {
// 	t_token	*t;

// 	t = ft_ret_last_token(data);
// 	while (data->exit == 0 && t != NULL)
// 	{
// 		if (t != NULL && t->prev != NULL
// 			&& (t->prev->sep == 3 || t->prev->sep == 5))
// 			t = ft_read_token_list_while_redir(data, t);
// 		if (t != NULL && t->prev != NULL && t->prev->sep == 4)
// 			t = ft_redirect_input(data, t);
// 		if (t != NULL && t->next != NULL && t->next->sep == 2)
// 		{
// 			ft_pipe_close_data_fd(data, 0);
// 			ft_pipe_in(data);
// 		}
// 		if (t != NULL && t->prev == NULL)
// 			ft_pipe_close_data_fd(data, 1);
// 		if (t != NULL && t->prev != NULL && t->prev->sep == 6)
// 			t = ft_here_doc(data, t);
// 		ft_read_token_list_bis(data, t);
// 		if (t != NULL && t->prev != NULL)
// 			t = t->prev;
// 		else
// 			t = NULL;
// 	}
// }

// void	ft_print_token_list(t_data *data)
// {
// 	t_token	*token;
// 	int		i;

// 	token = data->token;
// 	i = 0;
// 	printf("\n");
// 	while (token != NULL)
// 	{
// 		printf("-------------------------------\n");
// 		printf("Tok adr %p -- ", token);
// 		printf("cmd %d sep %d", token->cmd, token->sep);
// 		if (token->arg != NULL)
// 			printf(" arg '%s'", token->arg);
// 		while (token->bin != NULL && token->bin[i])
// 		{
// 			printf(" %p '%s'", token->bin[i], token->bin[i]);
// 			i++;
// 		}
// 		printf("\n");
// 		token = token->next;
// 	}
// 	printf("-------------------------------\n");
// }
