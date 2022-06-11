/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:58:24 by guderram          #+#    #+#             */
/*   Updated: 2022/06/11 15:15:17 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_ret_dollar_single(void)
{
	char	*ret;

	ret = NULL;
	ret = malloc(sizeof(char *) * (2));
	if (ret == NULL)
		return (NULL);
	ret[0] = '$';
	ret[1] = '\0';
	return (ret);
}

char	*ft_ret_dollar_ret(t_data *data, char *str)
{
	int		i;
	char	*ret;

	i = 1;
	ret = NULL;
	while (str[i] && str[i] != ' ' && str[i] != '$'
		&& ft_is_separator(str, i) == 0
		&& str[i] != '\'' && str[i] != '\"' && str[i] != '/')
		i++;
	ret = ft_malloc_str(data, i);
	i = 1;
	while (str[i] && str[i] != ' '
		&& str[i] != '$' && ft_is_separator(str, i) == 0
		&& str[i] != '\'' && str[i] != '\"' && str[i] != '/')
	{
		ret[i - 1] = str[i];
		i++;
	}
	ret[i - 1] = '\0';
	return (ret);
}

char	*ft_ret_dollar(t_data *data, char *str)
{
	int		i;
	char	*ret;
	t_var	*var;

	i = 1;
	ret = NULL;
	if (str[1] == '\0' || str[1] == ' ' || str[1] == '\'' || str[1] == '\"')
		return (ft_ret_dollar_single());
	ret = ft_ret_dollar_ret(data, str);
	if (ft_str_size(ret) == 0)
		return (ret);
	var = ft_found_var_name(data, ret);
	if (var == NULL)
		return (NULL);
	ft_strdel(&ret);
	ret = ft_malloc_str(data, ft_str_size(var->value));
	i = 0;
	while (var->value && var->value[i])
	{
		ret[i] = var->value[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
