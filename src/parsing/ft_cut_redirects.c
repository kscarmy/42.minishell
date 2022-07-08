/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:58:24 by guderram          #+#    #+#             */
/*   Updated: 2022/07/09 00:49:18 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_redirects(t_data *data)
{
	int	i;
	int	u;

	i = data->i;
	u = 0;
	u = u + ft_space(data->input, i);
	if (ft_is_separator(data->input, (i + u)) != 0)
	{
		ft_create_redirects_token(data,
			ft_is_separator(data->input, (i + u)));
		if (ft_is_separator(data->input, (i + u)) > 4)
			data->i = data->i + u + 2;
		else
			data->i = data->i + u + 1;
		return (1);
	}
	return (0);
}

void	ft_create_redirects_token(t_data *data, int i)
{
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->sep = i;
}
