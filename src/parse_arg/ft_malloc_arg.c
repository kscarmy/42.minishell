/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:28:25 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 13:31:37 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_malloc_arg_bis(t_data *data, t_token *tok, int *u, int *cd)
{
	char	*tmp;

	tmp = NULL;
	if (data->input[data->i + *u] == '\"'
		&& data->input[data->i + *u + 1] != '\"')
	{
		tmp = ft_ret_double_quote(data, &data->input[data->i + *u], 0);
		if (ft_str_size(tmp) > 0)
			*u = *u + 2 + ft_str_size(tmp);
		while (data->input[data->i + *u] && ft_str_size(tmp) > 0
			&& data->input[data->i + *u] != '\"')
			*u = *u + 1;
		if (data->input[data->i + *u] == '\"')
			*u = *u + 1;
		if (ft_str_size(tmp) > 0)
			ft_copie_dest_src(tok, tmp);
		ft_strdel(&tmp);
		*cd = *cd + 1;
	}
}

void	ft_malloc_arg_bis_bis(t_data *data, t_token *tok, int *u, int *cd)
{
	char	*tmp;

	tmp = NULL;
	if (data->input[data->i + *u] == '\''
		&& data->input[data->i + *u + 1] != '\'')
	{
		tmp = ft_ret_simple_quote(data,
				&data->input[data->i + *u], 0);
		*u = *u + 2 + ft_str_size(tmp);
		ft_copie_dest_src(tok, tmp);
		ft_strdel(&tmp);
		*cd = *cd + 1;
	}
	else if ((data->input[data->i + *u] == '\"'
			&& data->input[data->i + *u + 1] == '\"')
		|| (data->input[data->i + *u] == '\''
			&& data->input[data->i + *u + 1] == '\''))
	{
		*u = *u + 2;
		*cd = *cd + 1;
	}
}

void	ft_malloc_arg_bbb(t_data *data, t_token *tok, int *u, int *cd)
{
	char	*tmp;

	tmp = NULL;
	if (data->input[data->i + *u] == '$')
	{
		tmp = ft_ret_dollar(data,
				&(data->input[data->i + *u]));
		if (tmp != NULL)
			ft_copie_dest_src(tok, tmp);
		ft_strdel(&tmp);
		*u = *u + 1;
		while (data->input[data->i + *u]
			&& data->input[data->i + *u] != ' '
			&& data->input[data->i + *u] != '$'
			&& ft_is_separator(data->input, (data->i + *u)) == 0
			&& data->input[data->i + *u] != '\"'
			&& data->input[data->i + *u] != '\'')
			*u = *u + 1;
		*cd = *cd + 1;
	}
}

void	ft_malloc_arg_pre_b(t_data *data, t_token *tok, int *u, int *cd)
{
	ft_malloc_arg_bis(data, tok, &*u, &*cd);
	if (*cd == 0)
		ft_malloc_arg_bis_bis(data, tok, &*u, &*cd);
	if (*cd == 0)
		ft_malloc_arg_bbb(data, tok, &*u, &*cd);
}

void	ft_malloc_arg(t_data *data, t_token *tok)
{
	int		i;
	int		u;
	int		size;
	int		cd;

	i = 0;
	u = 0;
	cd = 0;
	size = ft_size_of_arg(data);
	tok->arg = ft_malloc_str(data, size);
	if (size > 0 && tok->arg != NULL)
	{
		while (data->input[data->i + u]
			&& ft_is_separator(data->input, (data->i + u)) == 0)
		{
			ft_malloc_arg_pre_b(data, tok, &u, &cd);
			if (cd == 0)
				ft_malloc_arg_bbbb(data, tok, &u, &i);
		}
		while (tok->arg[i] && tok->arg[i] != '\0')
			i++;
		tok->arg[i] = '\0';
		data->i = data->i + u;
	}
	ft_malloc_arg_end(data, &u, &size);
}
