/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:16:44 by guderram          #+#    #+#             */
/*   Updated: 2022/06/24 13:44:56 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_echo(t_data *data, char *str)
{
	char	*arg;

	arg = "echo";
	if (ft_str_size(str) != ft_str_size(arg))
		return (0);
	if (ft_strncmp(str, arg, ft_str_size(arg)) != 0)
		return (0);
	ft_create_echo_token(data);
	return (1);
}

void	ft_create_echo_token(t_data *data)
{
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 1;
	ft_malloc_builtin_arg(data, data->token);
}
