/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:50 by guderram          #+#    #+#             */
/*   Updated: 2022/06/26 11:31:54 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_parse_input_bis(t_data *data, int *found, char *str)
{
	if (*found == 0 && ft_cut_exit(data, str))
		*found = *found + 1;
	if (*found == 0 && ft_cut_env(data, str) == 1)
		*found = *found + 1;
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

void	ft_parse_input_interpret(t_data *data, int i)
{
	int	size;
	// int i;
	int	dq;

	// i = 0;
	dq = 0;
	size = ft_incre_one_arg(data, i);
	data->dol = 0;
	while (data->input[data->i + i] && i <= size)
	{
		if (dq == 1 && data->input[data->i + i] == '\"')
			dq = 0;
		else if (data->input[data->i + i] == '\"')
			dq = 1;
		if (dq == 0 && data->input[data->i + i] == '$')
			data->dol = 1;
		i++;
	}
}

int	ft_parse_input(t_data *data)
{
	int		found;
	char	*str;

	// data->i = 0;
	found = 0;
	str = NULL;
	while (data->exit == 0 && found >= 0 && data->input[data->i])
	{
		found = 0;
		ft_parse_input_interpret(data, 0);
		data->i = data->i + ft_space(data->input, data->i);
		if (ft_cut_redirects(data) != 1)
		{
			str = ft_one_arg(data, 0);
			data->i = data->i + ft_incre_one_arg(data, 0);
			ft_parse_input_bis(data, &found, str);
			if (found == 0 && ft_cut_bin(data, str) == 1)
				found++;
			ft_strdel(&str);
		}
	}
	return (0);
}
