/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:28:29 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 13:33:30 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_one_arg_b(t_data *data, int u, int *i, int *cd)
{
	char	*tmp;

	tmp = NULL;
	if (data->input[*i + u] == '\"'
		&& data->input[*i + u + 1] != '\"'
		&& data->input[*i + u + 1] != '\0')
	{
		tmp = data->tmp;
		data->tmp = ft_src_in_dest(data, data->tmp,
				ft_ret_double_quote(data, &data->input[*i + u], 0), 0);
		ft_strdel(&tmp);
		*i = *i + 1;
		while (data->input[*i + u] != '\"')
			*i = *i + 1;
		*i = *i + 1;
		*cd = *cd + 1;
	}
}

void	ft_one_arg_bb(t_data *data, int u, int *i, int *cd)
{
	char	*tmp;

	tmp = NULL;
	if (*cd == 0 && data->input[*i + u] == '\''
		&& data->input[*i + u + 1] != '\''
		&& data->input[*i + u + 1] != '\0')
	{
		tmp = data->tmp;
		data->tmp = ft_src_in_dest(data, data->tmp,
				ft_ret_simple_quote(data, &data->input[*i + u], 0), 0);
		ft_strdel(&tmp);
		*i = *i + 1;
		while (data->input[*i + u] != '\'')
			*i = *i + 1;
		*i = *i + 1;
		*cd = *cd + 1;
	}
	else if ((*cd == 0 && data->input[*i + u] == '\"'
			&& data->input[*i + u + 1] == '\"')
		|| (*cd == 0 && data->input[*i + u] == '\''
			&& data->input[*i + u + 1] == '\''))
	{
		*i = *i + 2;
		*cd = *cd + 1;
	}
}

void	ft_one_arg_bbb(t_data *data, int u, int *i, int *cd)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (*cd == 0 && data->input[*i + u] == '$')
	{
		tmp2 = ft_ret_dollar(data, &(data->input[*i + u]));
		if (ft_str_size(tmp2) > 0)
		{
			tmp = data->tmp;
			data->tmp = ft_src_in_dest(data, data->tmp, tmp2, 0);
			ft_strdel(&tmp);
		}
		*i = *i + 1;
		while (ft_is_separator(data->input, (*i + u)) == 0
			&& data->input[*i + u] && data->input[*i + u] != ' '
			&& data->input[*i + u] != '$')
			*i = *i + 1;
		*cd = *cd + 1;
	}
}

void	ft_one_arg_bbbb(t_data *data, int u, int *i, int *cd)
{
	char	*tmp;

	tmp = NULL;
	if (*cd == 0)
	{
		tmp = data->tmp;
		data->tmp = ft_src_in_dest(data, data->tmp,
				ft_one_simple_arg(data, *i + u), 0);
		ft_strdel(&tmp);
		while (data->input[*i + u] && data->input[*i + u] != ' '
			&& ft_is_separator(data->input, *i + u) == 0
			&& data->input[*i + u] != '\''
			&& data->input[*i + u] != '\"'
			&& data->input[*i + u] != '$')
			*i = *i + 1;
	}
}

char	*ft_one_arg(t_data *data, int u)
{
	int		i;
	int		cd;

	i = 0;
	cd = 0;
	data->tmp = ft_malloc_str(data, ft_size_one_arg(data, u));
	u = u + data->i;
	while (data->input[i + u] && data->input[i + u] != ' '
		&& ft_is_separator(data->input, i + u) == 0)
	{
		cd = 0;
		ft_one_arg_b(data, u, &i, &cd);
		ft_one_arg_bb(data, u, &i, &cd);
		ft_one_arg_bbb(data, u, &i, &cd);
		ft_one_arg_bbbb(data, u, &i, &cd);
	}
	return (data->tmp);
}
