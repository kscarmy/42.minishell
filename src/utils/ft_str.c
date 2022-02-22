/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:56:24 by guderram          #+#    #+#             */
/*   Updated: 2022/02/21 22:11:26 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*ft_malloc_str(t_data *data, int i) // malloc un str de taille i, le renplie de \0 et le return
{
	char	*str;
	int		u;

	u = 0;
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
	{
		data->err = 100;
		return (NULL);
	}
	while (u < i)
	{
		str[u] = '\0';
		u++;
	}
	str[u] = '\0';
	return (str);
}

void	ft_str_join_input(t_data *data, int i, int max) // malloc en recuperant la chaine token->str + la chaine input entre i et i + m
{
	int	u;
	char	*tmp;

	u = 0;
	while (data->token->arg[u])
		u++;
	tmp = ft_malloc_str(data, (u + max));
	u = 0;
	while (data->token->arg[u])
	{
		tmp[u] = data->token->arg[u];
		u++;
	}
	while (max > 0)
	{
		tmp[u] = data->input[i];
		u++;
		i++;
		max--;
	}
	ft_strdel(&data->token->arg);
	data->token->arg = tmp;
}


char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	// printf("strncpy : %d\n", n);
	// printf("strncpy 1 : %s\n", dest);
	while ((src[i]) && (i < n))
	{
		dest[i] = src[i];
		i++;
	}
	// printf("strncpy 2 : %s\n", dest);
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	// printf("strncpy 3 : %s\n", dest);
	return (dest);
}