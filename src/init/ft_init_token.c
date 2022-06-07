/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 03:14:08 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 22:32:18 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_init_token(t_data *data)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		data->err = 101;
	else
	{
		token->sep = -1;
		token->cmd = -1;
		token->option = -1;
		token->arg = NULL;
		token->bin = NULL;
		token->next = NULL;
		token->prev = NULL;
	}
	data->token = token;
}

void	ft_add_new_token(t_data *data)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		data->err = 101;
	else
	{
		new->sep = -1;
		new->cmd = -1;
		new->option = -1;
		new->arg = NULL;
		new->bin = NULL;
		new->next = data->token;
		data->token = new;
		new->prev = NULL;
		new->next->prev = new;
	}
}

void	ft_free_token(t_data *data, t_token *token)
{
	int	i;

	i = 0;
	if (token->arg != NULL)
	{
		free (token->arg);
		token->arg = NULL;
	}
	while (token->bin && token->bin[i] != NULL)
	{
		free (token->bin[i]);
		token->bin[i] = NULL;
		i++;
	}
	if (token->bin != NULL)
	{
		free (token->bin);
		token->bin = NULL;
	}
	data->i = data->i;
}

void	ft_delete_token(t_data *data, t_token *delete)
{
	if (delete == NULL)
		data->err = 102;
	if (data->token != NULL && delete != NULL)
	{
		ft_free_token(data, delete);
		if (delete->next == NULL && delete->prev != NULL)
			delete->prev->next = NULL;
		if (delete->prev == NULL && delete->next != NULL)
		{
			data->token = delete->next;
			delete->next->prev = NULL;
		}
		if (delete->prev == NULL && delete->next == NULL)
			data->token = NULL;
		if (delete->next != NULL && delete->prev != NULL)
		{
			delete->prev->next = delete->next;
			delete->next->prev = delete->prev;
		}
		if (delete && delete != NULL)
		{
			free (delete);
			delete = NULL;
		}
	}
}
