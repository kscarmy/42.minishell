/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 05:07:01 by guderram          #+#    #+#             */
/*   Updated: 2022/06/26 18:32:44 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_a_b(char a, char b)
{
	if (a == b)
		return (1);
	else
		return (0);
}

int	ft_space(char *str, int i)
{
	int	u;

	u = 0;
	if (str == NULL)
		return (0);
	if (!str[i])
		return (0);
	while (str && str[i + u] && str[i + u] != '\0' && str[i + u] == ' ')
		u++;
	return (u);
}

void	ft_print_one_var(t_var *var)
{
	ft_putstr("declare -x ");
	ft_putstr(var->name);
	ft_putchar('=');
	ft_putchar('"');
	ft_putstr(var->value);
	ft_putchar('"');
	ft_putchar('\n');
}

int	ft_str_comp_ascii(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (str1[i] < str2[i])
		return (1);
	else
		return (2);
}
