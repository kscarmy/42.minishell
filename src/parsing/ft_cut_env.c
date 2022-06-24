/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 07:12:42 by mourdani          #+#    #+#             */
/*   Updated: 2022/06/24 13:43:59 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_env(t_data *data, char *str)
{
	char	*arg;

	arg = "env";
	if (ft_str_size(str) != ft_str_size(arg))
		return (0);
	if (ft_strncmp(str, arg, ft_str_size(arg)) != 0)
		return (0);
	ft_create_env_token(data);
	return (1);
}

void	ft_create_env_token(t_data *data)
{
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 4;
}
