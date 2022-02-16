/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:56:24 by guderram          #+#    #+#             */
/*   Updated: 2022/02/16 11:23:49 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while ((src[i]) && (i < n))
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_is_separator(char *str, int i) // renvoie 0 si "c" n'est pas un separateur, sinon son code specifique
{
	if (str[i] == ';')
		return (1);
	if (str[i] == '|')
		return (2);
	if (str[i] == '>' && str[i + 1] != '>')
		return (3);
	if (str[i] == '<' && str[i + 1] != '<')
		return (4);
	if (str[i] == '>' && str[i + 1] == '>')
		return (5);
	if (str[i] == '<' && str[i + 1] == '<')
		return (6);
	return (0);
}
