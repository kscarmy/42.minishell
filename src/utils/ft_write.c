/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 05:07:01 by guderram          #+#    #+#             */
/*   Updated: 2022/02/11 16:42:35 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_a_b(char a, char b) // compare a et b, renvoie 1 si ils sont identiques sinon 0
{
	if (a == b)
		return (1);
	else
		return (0);
}

int	ft_space(char *str, int i) // renvoie le nombre d espaces a sauter en partant de i
{
	int	u;

	u = 0;
	while (str[i + u] && str[i + u] == ' ')
	{
		u++;
	}
	return (u);
}
