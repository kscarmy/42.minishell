/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:50 by guderram          #+#    #+#             */
/*   Updated: 2022/06/09 09:55:20 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_parse_input_bis(t_data *data, int *found)
{
	if (*found == 0 && ft_cut_echo(data, data->i) == 1)
		*found = *found + 1;
	if (*found == 0 && ft_cut_pwd(data) == 1)
		*found = *found + 1;
	if (*found == 0 && ft_cut_export(data) == 1)
		*found = *found + 1;
	if (*found == 0 && ft_cut_unset(data, data->i) == 1)
		*found = *found + 1;
	if (*found == 0 && ft_cut_redirects(data) == 1)
		*found = *found + 1;
	if (*found == 0 && ft_cut_bin(data) == 1)
		*found = *found + 1;
}

int	ft_parse_input(t_data *data)
{
	int	found;

	data->i = 0;
	found = 0;
	while (data->exit == 0 && found >= 0 && data->input[data->i])
	{
		found = 0;
		data->i = data->i + ft_space(data->input, data->i);
		if (ft_str_size(&(data->input[data->i])) == 0)
			found++;
		if (found == 0 && ft_cut_exit(data))
			found++;
		if (found == 0 && ft_cut_env(data, data->i) == 1)
			found++;
		if (found == 0 && ft_cut_cd(data, data->i))
			found++;
		ft_parse_input_bis(data, &found);
	}
	return (0);
}
