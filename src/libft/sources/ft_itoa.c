/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 05:26:42 by mourdani          #+#    #+#             */
/*   Updated: 2022/06/08 12:07:00 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static	int	ft_find_size(long n)
{
	int	compt;

	compt = 0;
	if (n <= 0)
	{
		n = n * -1;
		compt++;
	}
	while (n > 0)
	{
		n = n / 10;
		compt++;
	}
	return (compt);
}

char	*ft_itoa(int n)
{
	char		*rslt;
	long		store;
	int			i;
	int			j;

	store = n;
	rslt = malloc(sizeof(char) * (ft_find_size(n) + 1));
	if (!rslt)
		return (NULL);
	i = ft_find_size(n) - 1;
	j = 0;
	if (store < 0)
	{
		rslt[j] = '-';
		store = store * -1;
		j++;
	}
	while (i >= j)
	{
		rslt[i] = '0' + store % 10;
		store = store / 10;
		i--;
	}
	rslt[ft_find_size(n)] = '\0';
	return (rslt);
}
