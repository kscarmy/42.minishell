/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:38:29 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 22:40:02 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_minishell_bis(t_data *data)
{
	if (data->pwd != NULL)
		ft_strdel(&data->pwd);
	if (data->opwd != NULL)
		ft_strdel(&data->opwd);
	if (data->pipe != NULL)
	{
		free(data->pipe);
		data->pipe = NULL;
	}
	ft_free_data_env(data);
	data->env = NULL;
}

void	ft_free_minishell(t_data *data)
{
	t_var	*var;
	t_token	*tok;

	var = data->var;
	tok = data->token;
	while (var != NULL)
	{
		ft_delete_var(data, var);
		var = data->var;
	}
	while (tok != NULL)
	{
		tok = data->token;
		ft_delete_token(data, tok);
	}
	ft_free_minishell_bis(data);
}
