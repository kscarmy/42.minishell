/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_bis_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:13:23 by guderram          #+#    #+#             */
/*   Updated: 2022/06/06 16:27:53 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_char(char *str, char c, int max)
{
	int	i;

	i = 0;
	while (str[i] && i < max)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_str_comp(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0
		&& ft_strncmp(str1, str2, ft_strlen(str2)) == 0)
		return (1);
	return (0);
}

int	ft_is_number(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	else
		return (0);
}
