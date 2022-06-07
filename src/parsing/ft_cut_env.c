/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 07:12:42 by mourdani          #+#    #+#             */
/*   Updated: 2022/06/07 15:15:42 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_env(t_data *data, int i)
{
	char	*str;
	int		u;

	u = 0;
	str = "env";
	i = i + ft_space(data->input, i);
	while (data->input[i] && data->input[i] != ' '
		&& ft_is_separator(data->input, i) == 0)
	{
		if (ft_is_a_b(data->input[i], str[u]) == 1)
			u++;
		i++;
	}
	if (u == 3)
	{
		data->i = data->i + 3 + ft_space(data->input, data->i);
		ft_create_env_token(data);
		return (1);
	}
	return (0);
}

void	ft_create_env_token(t_data *data)
{
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 4;
}
