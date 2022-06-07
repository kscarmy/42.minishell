/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 03:50:34 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 17:58:44 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_ret_simple_quote(t_data *data, char *str, int incr)
{
	int		i;
	char	*ret;

	i = 1;
	while (str[i] && str[i] != '\'')
		i++;
	if (incr == 1)
		data->i = data->i + i;
	ret = ft_malloc_str(data, i);
	i = 1;
	while (str[i] && str[i] != '\'')
	{
		ret[i - 1] = str[i];
		i++;
	}
	ret[i - 1] = '\0';
	return (ret);
}

void	ft_ret_double_quote_size(t_data *data, char *str, int *i, int *u)
{
	char	*tmp;

	tmp = NULL;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$' && str[*i + 1] == '"')
			*u = *u + 1;
		if (str[*i] == '$')
		{
			tmp = ft_ret_dollar(data, &str[*i]);
			*u = *u + ft_str_size(tmp);
			ft_strdel(&tmp);
			*i = *i + 1;
			while (str[*i] && str[*i] != ' '
				&& str[*i] != '$' && ft_is_separator(str, *i) == 0
				&& str[*i] != '\"' && str[*i] != '\'')
				*i = *i + 1;
		}
		else
		{
			*u = *u + 1;
			*i = *i + 1;
		}
	}
}

void	ft_ret_double_quote_else(char *ret, char *str, int *i, int *u)
{
	char	*tmp;

	tmp = NULL;
	if (str[*i] == '$' && str[*i + 1] == '"')
	{
		tmp = malloc(sizeof(char *) * (2));
		tmp[0] = '$';
		tmp[1] = '\0';
		ret = ft_str_cpy(ret, tmp);
		*u = *u + 1;
		ft_strdel(&tmp);
		*i = *i + 1;
	}
	else
	{
		ret[*u] = str[*i];
		*u = *u + 1;
		*i = *i + 1;
	}
}

void	ft_ret_double_quote_b(t_data *data, char *str, char *ret)
{
	int		i;
	int		u;
	char	*tmp;

	i = 1;
	u = 0;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1] != '"')
		{
			tmp = ft_ret_dollar(data, &str[i]);
			ret = ft_str_cpy(ret, tmp);
			u = u + ft_str_size(tmp);
			ft_strdel(&tmp);
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '$'
				&& ft_is_separator(str, i) == 0
				&& str[i] != '\"' && str[i] != '\'')
				i++;
		}
		else
			ft_ret_double_quote_else(ret, str, &i, &u);
	}
	ret[u] = '\0';
}

char	*ft_ret_double_quote(t_data *data, char *str, int incr)
{
	int		i;
	int		u;
	char	*ret;

	u = 0;
	i = 1;
	while (str[i] && str[i] != '\"')
		i++;
	if (incr == 1)
		data->i = data->i + i;
	i = 1;
	ft_ret_double_quote_size(data, str, &i, &u);
	ret = ft_malloc_str(data, u);
	ft_ret_double_quote_b(data, str, ret);
	return (ret);
}
