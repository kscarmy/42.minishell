/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:15:08 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 15:43:25 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_input_safe_quotes(char *str, int *i)
{
	if (str[*i] == '\"')
	{
		*i = *i + 1;
		while (str[*i] && str[*i] != '\"')
			*i = *i + 1;
		if (str[*i] == '\0')
			return (0);
	}
	else if (str[*i] == '\'')
	{
		*i = *i + 1;
		while (str[*i] && str[*i] != '\'')
			*i = *i + 1;
		if (str[*i] == '\0')
			return (0);
	}
	return (1);
}

int	ft_is_input_safe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_input_safe_quotes(str, &i) == 0)
			return (0);
		else if (str[i] == '\\')
			return (0);
		else if (str[i] == ';')
			return (0);
		i++;
	}
	return (1);
}
