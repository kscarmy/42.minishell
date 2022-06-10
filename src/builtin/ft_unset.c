/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:12:33 by guderram          #+#    #+#             */
/*   Updated: 2022/06/09 08:23:21 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_unset_malloc_str(t_data *data, char *str)
{
	char	*string;
	int		u;

	u = 0;
	while (str[u] && str[u] != ' ' && ft_is_separator(str, u) == 0)
		u++;
	string = ft_malloc_str(data, u);
	if (string != NULL)
		string = ft_strncpy(string, str, u);
	return (string);
}

void	ft_unset(t_data *data, t_token *token)
{
	t_var	*var;
	int		i;
	char	*str;

	i = 0;
	while (token->arg && token->arg[i])
	{
		i = i + ft_space(token->arg, i);
		str = ft_unset_malloc_str(data, &(token->arg[i]));
		if (str != NULL)
			var = ft_found_var_name(data, str);
		if (str != NULL && var != NULL)
			ft_delete_var(data, var);
		ft_strdel(&str);
		i++;
	}
}
