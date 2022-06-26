/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:28:56 by guderram          #+#    #+#             */
/*   Updated: 2022/06/26 17:58:24 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_size_of_arg_bis_bis(t_data *data, int *u, int *cd)
{
	char	*tmp;

	tmp = NULL;
	if ((data->input[data->i + *u] == '\"'
			&& data->input[data->i + *u + 1] == '\"')
		|| (data->input[data->i + *u] == '\''
			&& data->input[data->i + *u + 1] == '\''))
	{
		*u = *u + 2;
		*cd = *cd + 1;
	}
	else if (*cd == 0 && data->input[data->i + *u] == '$')
	{
		tmp = ft_ret_dollar(data, &(data->input[data->i + *u]));
		if (ft_str_size(tmp) > 0)
			*u = *u + ft_str_size(tmp);
		else
			*u = *u + 1;
		ft_strdel(&tmp);
	}
}

void	ft_size_of_arg_bis(t_data *data, int *i, int *u, int *cd)
{
	if (data->input[data->i + *u] == '\"'
		&& data->input[data->i + *u + 1] != '\"'
		&& data->input[data->i + *u + 1] != '\0')
	{
		*i = ft_str_size(ft_ret_double_quote(data,
					&data->input[data->i + *u], 0));
		if (*i != 0)
			*u = *u + *i;
		while (i == 0 && data->input[data->i + *u] != '\"')
			*u = *u + 1;
		if (*i == 0)
			*u = *u + 1;
		*cd = *cd + 1;
	}
	else if (data->input[data->i + *u] == '\''
		&& data->input[data->i + *u + 1] != '\''
		&& data->input[data->i + *u + 1] != '\0')
	{
		u = u + ft_str_size(ft_ret_simple_quote(data,
					&data->input[data->i + *u], 0));
		*cd = *cd + 1;
	}
}

int	ft_size_of_arg(t_data *data)
{
	int		u;
	int		i;
	int		cd;

	u = 0;
	i = 0;
	cd = 0;
	while (ft_is_separator(data->input, (data->i + u)) == 0
		&& data->input[data->i + u])
	{
		ft_size_of_arg_bis(data, &i, &u, &cd);
		if (cd == 0)
			ft_size_of_arg_bis_bis(data, &u, &cd);
		else
			u++;
	}
	if (i != 0 && u == 0)
		u++;
	return (u);
}

int	ft_incre_one_arg(t_data *data, int u)
{
	// printf("ft_incre_one_arg : entree : data i : %d u %d <%s>\n", data->i, u, &data->input[data->i + u]);
	while (data->input[data->i + u]
		&& data->input[data->i + u] != ' '
		&& ft_is_separator(data->input, data->i + u) == 0)
	{
		
		if (data->input[data->i + u] == '\'')
		{
			u++;
			while (data->input[data->i + u]
				&& data->input[data->i + u] != '\'')
				u++;
			u++;
		}
		else if (data->input[data->i + u] == '\"')
		{
			u++;
			while (data->input[data->i + u]
				&& data->input[data->i + u] != '\"')
				u++;
			u++;
		}
		else
			u++;
	}
	// printf("ft_incre_one_arg : sortie : data i : %d u %d <%s>\n", data->i, u, &data->input[data->i + u]);
	return (u);
}

void	ft_malloc_builtin_arg(t_data *data, t_token *tok)
{
	int		u;
	char	*tmp;
	char	*tmp2;

	u = 0;
	tmp = NULL;
	tmp2 = NULL;
	tok->arg = NULL;
	while (data->input[data->i + u]
		&& ft_is_separator(data->input, data->i + u) == 0)
	{
		u = u + ft_space(data->input, data->i + u);
		tmp = ft_one_arg(data, u);
		if (tok->arg != NULL)
			tmp2 = tok->arg;
		if (data->input[data->i + u]
			&& ft_is_separator(data->input, data->i + u) == 0)
			tok->arg = ft_src_in_dest(data, tok->arg, tmp, ' ');
		else
			tok->arg = ft_src_in_dest(data, tok->arg, tmp, 0);
		u = ft_incre_one_arg(data, u);
		ft_strdel(&tmp2);
	}
	data->i = data->i + u;
}
