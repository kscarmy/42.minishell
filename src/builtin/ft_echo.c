/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:35:31 by guderram          #+#    #+#             */
/*   Updated: 2022/06/24 15:09:23 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo_option(t_token *t, int u)
{
	int	i;
	int	x;

	i = u;
	x = i;
	while (t->arg[i])
	{
		if (t->arg[i] == '-')
			i++;
		else
			break ;
		while (t->arg[i] == 'n')
			i++;
		if (t->arg[i] == '\0')
			return (i);
		if (t->arg[i] != ' ')
			break ;
		else
		{
			i = i + ft_space(t->arg, i);
			x = i;
		}
	}
	return (x);
}

void	ft_echo(t_data *data, t_token *token)
{
	int	i;

	i = 0;
	if (token->arg)
		i = ft_space(token->arg, 0);
	if (token->arg && ft_echo_option(token, i) != i)
	{
		i = ft_echo_option(token, i);
		token->option = 1;
	}
	if (token->arg)
		ft_putstr(&token->arg[i]);
	if (token->option != 1)
		ft_putstr("\n");
	data->i = data->i;
}
