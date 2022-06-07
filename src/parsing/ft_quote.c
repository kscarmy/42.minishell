/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 03:50:34 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 14:26:20 by guderram         ###   ########.fr       */
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

char	*ft_ret_double_quote(t_data *data, char *str, int incr)
{
	int		i;
	int 	u;
	char	*ret;
	char	*tmp;

	u = 0;
	i = 1;
	while (str[i] && str[i] != '\"')
		i++;
	if (incr == 1)
		data->i = data->i + i;
	i = 1;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1] == '"')
			u = u + 1;
		if (str[i] == '$')
		{
			tmp = ft_ret_dollar(data, &str[i]);
			u = u + ft_str_size(tmp);
			ft_strdel(&tmp);
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '$' && ft_is_separator(str, i) == 0 && str[i] != '\"' && str[i] != '\'')
				i++;
		}
		else
		{
			u++;
			i++;
		}
	}
	ret = ft_malloc_str(data, u);
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
			while (str[i] && str[i] != ' ' && str[i] != '$' && ft_is_separator(str, i) == 0 && str[i] != '\"' && str[i] != '\'')
				i++;
		}
		else if (str[i] == '$' && str[i + 1] == '"')
		{
			tmp = malloc(sizeof(char*) * (2));
			tmp[0] = '$';
			tmp[1] = '\0';
			ret = ft_str_cpy(ret, tmp);
			u = u + 1;
			ft_strdel(&tmp);
			i++;
		}
		else
		{
			ret[u] = str[i];
			u++;
			i++;
		}
	}
	ret[u] = '\0';
	return (ret);
}

char	*ft_ret_dollar(t_data *data, char *str)
{
	int		i;
	char	*ret;
	t_var	*var;

	i = 1;
	if (str[1] == '\0' || str[1] == ' ' || str[1] == '\'' || str[1] == '\"')
	{
		ret = malloc(sizeof(char*) * (2));
		ret[0] = '$';
		ret[1] = '\0';
		return(ret);
	}
	while (str[i] && str[i] != ' ' && str[i] != '$' && ft_is_separator(str, i) == 0 && str[i] != '\'' && str[i] != '\"')
		i++;
	ret = ft_malloc_str(data, i);
	i = 1;
	while (str[i] && str[i] != ' ' && str[i] != '$' && ft_is_separator(str, i) == 0 && str[i] != '\'' && str[i] != '\"')
	{
		ret[i - 1] = str[i];
		i++;
	}
	ret[i - 1] = '\0';
	if (ft_str_size(ret) == 0)
		return(ret);
	ft_strdel(&data->var->value);
	var = ft_found_var_name(data, ret);
	if (var == NULL)
		return (NULL);
	ft_strdel(&ret);
	ret = ft_malloc_str(data, ft_str_size(var->value));
	i = 0;
	while (var->value[i])
	{
		ret[i] = var->value[i];
		i++;
	}
	ft_strdel(&data->var->value);
	ret[i] = '\0';
	return (ret);
}
