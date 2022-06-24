/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:50 by guderram          #+#    #+#             */
/*   Updated: 2022/06/24 13:45:04 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_parse_input_bis(t_data *data, int *found, char *str)
{
	if (*found == 0 && ft_cut_cd(data, str))
		*found = *found + 1;
	if (*found == 0 && ft_cut_echo(data, str) == 1)
		*found = *found + 1;
	if (*found == 0 && ft_cut_pwd(data, str) == 1)
		*found = *found + 1;
	if (*found == 0 && ft_cut_export(data, str) == 1)
		*found = *found + 1;
	if (*found == 0 && ft_cut_unset(data, str) == 1)
		*found = *found + 1;
}

int	ft_parse_input(t_data *data)
{
	int		found;
	char	*str;

	data->i = 0;
	found = 0;
	str = NULL;
	while (data->exit == 0 && found >= 0 && data->input[data->i])
	{
		found = 0;
		data->i = data->i + ft_space(data->input, data->i);
		if (ft_cut_redirects(data) != 1)
		{
			str = ft_one_arg(data, 0);
			data->i = data->i + ft_incre_one_arg(data, 0);
			if (found == 0 && ft_cut_exit(data, str))
				found++;
			if (found == 0 && ft_cut_env(data, str) == 1)
				found++;
			ft_parse_input_bis(data, &found, str);
			if (found == 0 && ft_cut_bin(data, str) == 1)
				found++;
			ft_strdel(&str);
		}
	}
	return (0);
}
