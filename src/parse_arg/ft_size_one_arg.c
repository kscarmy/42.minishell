/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_one_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:28:34 by guderram          #+#    #+#             */
/*   Updated: 2022/06/11 18:48:24 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_size_one_arg_b(t_data *da, int s, int *u, int *ret)
{
	char	*tmp;
	int		cd;

	tmp = NULL;
	cd = 0;
	if (da->input[s + *u] == '\"' && da->input[s + *u + 1] != '\"'
		&& da->input[s + *u + 1] != '\0')
	{
		tmp = ft_ret_double_quote(da,
				&da->input[s + *u], 0);
		*ret = *ret + ft_str_size(tmp);
		ft_strdel(&tmp);
		*u = *u + 1;
		while (da->input[s + *u] != '\"')
			*u = *u + 1;
		*u = *u + 1;
		cd ++;
	}
	return (cd);
}

int	ft_size_one_arg_bb(t_data *da, int s, int *u, int *ret)
{
	char	*tmp;
	int		cd;

	tmp = NULL;
	cd = 0;
	if (da->input[s + *u] == '\''
		&& da->input[s + *u + 1] != '\''
		&& da->input[s + *u + 1] != '\0')
	{
		tmp = ft_ret_simple_quote(da,
				&da->input[s + *u], 0);
		*ret = *ret + ft_str_size(tmp);
		ft_strdel(&tmp);
		while (da->input[s + *u] != '\'')
			*u = *u + 1;
		*u = *u + 1;
		cd++;
	}
	return (cd);
}

int	ft_size_one_arg_bbb(t_data *da, int s, int *u)
{
	if ((da->input[s + *u] == '\"'
			&& da->input[s + *u + 1] == '\"')
		|| (da->input[s + *u] == '\''
			&& da->input[s + *u + 1] == '\''))
	{
		*u = *u + 2;
		return (1);
	}
	return (0);
}

int	ft_size_one_arg_bbbb(t_data *da, int s, int *u, int *ret)
{
	char	*tmp;

	tmp = NULL;
	if (da->input[s + *u] != '$')
		return (0);
	tmp = ft_ret_dollar(da, &(da->input[s + *u]));
	if (ft_str_size(tmp) > 0)
	{
		*ret = *ret + ft_str_size(tmp);
		*u = *u + 1;
		while (ft_is_separator(da->input, (s + *u)) == 0
			&& da->input[s + *u] && da->input[s + *u] != ' '
			&& da->input[s + *u] != '$')
			*u = *u + 1;
	}
	else
	{
		*ret = *ret + 1;
		*u = *u + 1;
	}
	ft_strdel(&tmp);
	return (1);
}

int	ft_size_one_arg(t_data *data, int s)
{
	int		u;
	int		ret;
	int		cd;

	u = 0;
	ret = 0;
	s = s + data->i;
	while (ft_is_separator(data->input, (s + u)) == 0
		&& data->input[s + u] && data->input[s + u] != ' ')
	{
		cd = 0;
		cd = ft_size_one_arg_b(data, s, &u, &ret);
		if (cd == 0)
			cd = ft_size_one_arg_bb(data, s, &u, &ret);
		if (cd == 0)
			cd = ft_size_one_arg_bbb(data, s, &u);
		if (cd == 0)
			cd = ft_size_one_arg_bbbb(data, s, &u, &ret);
		if (cd == 0)
		{
			u++;
			ret++;
		}
	}
	return (ret);
}
