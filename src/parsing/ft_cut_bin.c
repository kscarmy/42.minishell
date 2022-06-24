/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:45:12 by guderram          #+#    #+#             */
/*   Updated: 2022/06/24 13:43:19 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_bin(t_data *data, char *str)
{
	int	u;
	int	i;

	i = 1;
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	u = ft_bin_size(data);
	data->token->bin = (char **)malloc(sizeof(char *) * (u + 1));
	u = ft_space(data->input, data->i);
	data->token->bin[0] = ft_str_malloc_cpy(data, str);
	u = u + ft_space(data->input, data->i + u);
	while (data->input[data->i + u]
		&& ft_is_separator(data->input, data->i + u) == 0)
	{
		u = u + ft_space(data->input, data->i + u);
		data->token->bin[i] = ft_one_arg(data, u);
		u = ft_incre_one_arg(data, u);
		u = u + ft_space(data->input, data->i + u);
		i++;
	}
	data->token->bin[i] = NULL;
	data->i = data->i + u;
	return (1);
}

char	*ft_str_malloc_cpy(t_data *data, char	*str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_malloc_str(data, ft_str_size(str));
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_bin_size(t_data *data)
{
	int		nbr;
	int		u;

	u = 0;
	nbr = 1;
	while (data->input[data->i + u]
		&& ft_is_separator(data->input, data->i + u) == 0)
	{
		u = u + ft_space(data->input, data->i + u);
		u = ft_incre_one_arg(data, u);
		u = u + ft_space(data->input, data->i + u);
		nbr++;
	}
	data->token->cmd = 9;
	return (nbr);
}
