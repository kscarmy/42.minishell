/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:28:56 by guderram          #+#    #+#             */
/*   Updated: 2022/06/06 17:47:57 by guderram         ###   ########.fr       */
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

void	ft_malloc_arg(t_data *data, t_token *tok)
{
	int		i;
	int		u;
	int		size;
	char	*tmp;

	i = 0;
	u = 0;
	size = ft_size_of_arg(data);
	tok->arg = ft_malloc_str(data, size);
	if (size > 0 && tok->arg != NULL)
	{
		while (data->input[data->i + u]
			&& ft_is_separator(data->input, (data->i + u)) == 0)
		{
			if (data->input[data->i + u] == '\"'
				&& data->input[data->i + u + 1] != '\"')
			{
				tmp = ft_ret_double_quote(data,
						&data->input[data->i + u], 0);
				if (ft_str_size(tmp) > 0)
					u = u + 2 + ft_str_size(tmp);
				while (data->input[data->i + u]
					&& ft_str_size(tmp) > 0
					&& data->input[data->i + u] != '\"')
					u++;
				if (data->input[data->i + u] == '\"')
					u++;
				if (ft_str_size(tmp) > 0)
					ft_copie_dest_src(tok, tmp);
				ft_strdel(&tmp);
			}
			else if (data->input[data->i + u] == '\''
				&& data->input[data->i + u + 1] != '\'')
			{
				tmp = ft_ret_simple_quote(data,
						&data->input[data->i + u], 0);
				u = u + 2 + ft_str_size(tmp);
				ft_copie_dest_src(tok, tmp);
				ft_strdel(&tmp);
			}
			else if ((data->input[data->i + u] == '\"'
					&& data->input[data->i + u + 1] == '\"')
				|| (data->input[data->i + u] == '\''
					&& data->input[data->i + u + 1] == '\''))
				u = u + 2;
			else if (data->input[data->i + u] == '$')
			{
				tmp = ft_ret_dollar(data,
						&(data->input[data->i + u]));
				if (tmp != NULL)
					ft_copie_dest_src(tok, tmp);
				ft_strdel(&tmp);
				u++;
				while (data->input[data->i + u]
					&& data->input[data->i + u] != ' '
					&& data->input[data->i + u] != '$'
					&& ft_is_separator(data->input, (data->i + u)) == 0
					&& data->input[data->i + u] != '\"'
					&& data->input[data->i + u] != '\'')
					u++;
			}
			else
			{
				i = 0;
				while (tok->arg[i] && tok->arg[i] != '\0')
					i++;
				tok->arg[i] = data->input[data->i + u];
				if (data->input[data->i + u] == ' ')
					u = u + ft_space(data->input, data->i + u);
				else
					u++;
			}
		}
		while (tok->arg[i] && tok->arg[i] != '\0')
			i++;
		tok->arg[i] = '\0';
		data->i = data->i + u;
	}
	if (size == 0 && data->input[data->i + u] == '\"')
	{
		u++;
		while (data->input[data->i + u]
			&& data->input[data->i + u] != '\"')
			u++;
		if (data->input[data->i + u] == '\"')
			u++;
		data->i = data->i + u;
	}
	else if (size == 0)
		data->err = 200;
}

int	ft_incre_one_arg(t_data *data, int u)
{
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
	return (u);
}

int	ft_size_one_arg(t_data *data, int s)
{
	int		u;
	int		ret;
	char	*tmp;

	u = 0;
	ret = 0;
	s = s + data->i;
	while (ft_is_separator(data->input, (s + u)) == 0
		&& data->input[s + u] && data->input[s + u] != ' ')
	{
		if (data->input[s + u] == '\"'
			&& data->input[s + u + 1] != '\"'
			&& data->input[s + u + 1] != '\0')
		{
			tmp = ft_ret_double_quote(data,
					&data->input[s + u], 0);
			ret = ret + ft_str_size(tmp);
			ft_strdel(&tmp);
			u++;
			while (data->input[s + u] != '\"')
				u++;
			u++;
		}
		else if (data->input[s + u] == '\''
			&& data->input[s + u + 1] != '\''
			&& data->input[s + u + 1] != '\0')
		{
			tmp = ft_ret_simple_quote(data,
					&data->input[s + u], 0);
			ret = ret + ft_str_size(tmp);
			ft_strdel(&tmp);
			while (data->input[s + u] != '\'')
				u++;
			u++;
		}
		else if ((data->input[s + u] == '\"'
				&& data->input[s + u + 1] == '\"')
			|| (data->input[s + u] == '\''
				&& data->input[s + u + 1] == '\''))
			u = u + 2;
		else if (data->input[s + u] == '$')
		{
			tmp = ft_ret_dollar(data,
					&(data->input[s + u]));
			if (ft_str_size(tmp) > 0)
			{
				ret = ret + ft_str_size(tmp);
				u++;
				while (ft_is_separator(data->input, (s + u)) == 0
					&& data->input[s + u]
					&& data->input[s + u] != ' '
					&& data->input[s + u] != '$')
					u++;
			}
			else
			{
				ret++;
				u++;
			}
			ft_strdel(&tmp);
		}
		else
		{
			u++;
			ret++;
		}
	}
	return (ret);
}

char	*ft_one_simple_arg(t_data *data, int i)
{
	char	*ret;
	int		j;

	j = 0;
	while (data->input[i + j] && data->input[i + j] != ' '
		&& ft_is_separator(data->input, i + j) == 0
		&& data->input[i + j] != '\'' && data->input[i + j] != '\"'
		&& data->input[i + j] != '$')
		j++;
	ret = ft_malloc_str(data, j);
	j = 0;
	while (data->input[i + j] && data->input[i + j] != ' '
		&& ft_is_separator(data->input, i + j) == 0
		&& data->input[i + j] != '\'' && data->input[i + j] != '\"'
		&& data->input[i + j] != '$')
	{
		ret [j] = data->input[i + j];
		j++;
	}
	ret [j] = '\0';
	return (ret);
}

char	*ft_one_arg(t_data *data, int u)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	ret = ft_malloc_str(data, ft_size_one_arg(data, u));
	u = u + data->i;
	while (data->input[i + u] && data->input[i + u] != ' '
		&& ft_is_separator(data->input, i + u) == 0)
	{
		if (data->input[i + u] == '\"'
			&& data->input[i + u + 1] != '\"'
			&& data->input[i + u + 1] != '\0')
		{
			tmp = ret;
			ret = ft_src_in_dest(data, ret,
					ft_ret_double_quote(data, &data->input[i + u], 0), 0);
			ft_strdel(&tmp);
			i++;
			while (data->input[i + u] != '\"')
				i++;
			i++;
		}
		else if (data->input[i + u] == '\''
			&& data->input[i + u + 1] != '\''
			&& data->input[i + u + 1] != '\0')
		{
			tmp = ret;
			ret = ft_src_in_dest(data, ret,
					ft_ret_simple_quote(data, &data->input[i + u], 0), 0);
			ft_strdel(&tmp);
			i++;
			while (data->input[i + u] != '\'')
				i++;
			i++;
		}
		else if ((data->input[i + u] == '\"'
				&& data->input[i + u + 1] == '\"')
			|| (data->input[i + u] == '\''
				&& data->input[i + u + 1] == '\''))
			i = i + 2;
		else if (data->input[i + u] == '$')
		{
			tmp2 = ft_ret_dollar(data, &(data->input[i + u]));
			if (ft_str_size(tmp2) > 0)
			{
				tmp = ret;
				ret = ft_src_in_dest(data, ret, tmp2, 0);
				ft_strdel(&tmp);
			}
			i++;
			while (ft_is_separator(data->input, (i + u)) == 0
				&& data->input[i + u] && data->input[i + u] != ' '
				&& data->input[i + u] != '$')
				i++;
		}
		else
		{
			tmp = ret;
			ret = ft_src_in_dest(data, ret,
					ft_one_simple_arg(data, i + u), 0);
			ft_strdel(&tmp);
			while (data->input[i + u] && data->input[i + u] != ' '
				&& ft_is_separator(data->input, i + u) == 0
				&& data->input[i + u] != '\''
				&& data->input[i + u] != '\"'
				&& data->input[i + u] != '$')
				i++;
		}
	}
	return (ret);
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
