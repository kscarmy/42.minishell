/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:25:07 by guderram          #+#    #+#             */
/*   Updated: 2022/06/09 09:37:57 by guderram         ###   ########.fr       */
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
	data->token->bin[u] = NULL;
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
	data->i = data->i + u;
	data->token->cmd = 3;
}

int	ft_cut_export(t_data *data)
{
	int	i;

	i = data->i;
	if (ft_strncmp(&data->input[i], "export", 6) != 0)
		return (0);
	i = i + 6;
	if (ft_str_after_cut(&data->input[i]) != 1)
		return (0);
	data->i = i;
	ft_create_export_token(data);
	return (1);
}
