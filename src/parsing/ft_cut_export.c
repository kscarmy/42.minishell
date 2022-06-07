/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:25:07 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 15:22:35 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_export(t_data *data)
{
	char	*str;
	int		u;
	int		i;

	i = data->i;
	u = 0;
	str = "export";
	while (data->input[i] && data->input[i] != ' ')
	{
		if (ft_is_a_b(data->input[i], str[u]) == 1)
			u++;
		i++;
	}
	if (u == 6)
	{
		data->i = data->i + u;
		ft_create_export_token(data);
		return (1);
	}
	return (0);
}

void	ft_parse_export(t_data *data)
{
	int	i;
	int	m;

	i = data->i;
	m = 0;
	while (data->input[i] && ft_is_separator(data->input, i) == 0)
	{
		if (ft_is_export(data->input, i) != 0)
		{
			m = ft_is_export(data->input, i);
			ft_str_join_input(data, i, m);
			i = i + m;
		}
		m = 0;
		i++;
	}
}

int	ft_is_export(char *str, int i)
{
	int	equal;

	equal = 0;
	while (str[i] && str[i] != ' ' && ft_is_separator(str, i) != 1)
	{
		if (str[i] == '=' && str[i + 1] != ';'
			&& str[i + 1] != ' ' && str[i - 1] != ';' && str[i - 1] != ' ')
			equal++;
		i++;
	}
	if (equal == 1)
		return (i);
	return (0);
}

int	ft_export_count_equal(t_data *data)
{
	int	i;
	int	equal;

	i = data->i;
	equal = 0;
	while (data->input[i] && ft_is_separator(data->input, i) == 0)
	{
		if (data->input[i] == '=' && ft_is_separator(data->input,
				(i - 1)) == 0 && data->input[i - 1] != ' ')
		{
			equal++;
			while (data->input[i] && ft_is_separator(data->input, i) == 0
				&& data->input[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (equal);
}
