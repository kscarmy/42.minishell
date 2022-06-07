/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:35:31 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 22:43:34 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_data *data, t_token *token)
{
	ft_putstr(token->arg);
	if (token->option != 1)
		ft_putstr("\n");
	data->i = data->i;
}
