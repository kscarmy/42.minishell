/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:25:07 by guderram          #+#    #+#             */
/*   Updated: 2022/06/25 16:40:55 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_create_export_token(t_data *data)
{
	int	u;
	int	i;

	i = 0;
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	u = ft_bin_size(data);
	data->token->bin = (char **)malloc(sizeof(char *) * (u + 1));
	// data->token->bin[u] = NULL;
	u = ft_space(data->input, data->i);
	ft_strdel(&data->token->arg);
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
	data->token->cmd = 3;
}

int	ft_cut_export(t_data *data, char *str)
{
	char	*arg;

	arg = "export";
	if (ft_str_size(str) != ft_str_size(arg))
		return (0);
	if (ft_strncmp(str, arg, ft_str_size(arg)) != 0)
		return (0);
	ft_create_export_token(data);
	return (1);
}
