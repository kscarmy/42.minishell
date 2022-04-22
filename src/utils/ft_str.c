/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:56:24 by guderram          #+#    #+#             */
/*   Updated: 2022/04/22 01:00:06 by guderram         ###   ########.fr       */
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

int		ft_str_size(char *str) // renvoie la taille d'un str
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_check_char(char *str, char c, int max) // verifie si c est dans str avec max
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

int	ft_str_comp(char *str1, char *str2) // compare les deux strings, renvoie 1 si strictement identiques, sinon 0.
{
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0
		&& ft_strncmp(str1, str2, ft_strlen(str2)) == 0)
		return (1);
	return (0);
}

int		ft_str_after_cut(char *str) // compare le premier caractere de str avec les caracteres devant se trouver apres un argument
{
	// printf ("str after cut '%s'\n", str);
	if (str[0] == '\0')
		return (1);
	if (str[0] == ' ')
		return (1);
	if (ft_is_separator(str, 0) != 0)
		return (1);
	return (0);
}

void	ft_copie_dest_src(t_token *tok, char *src) // copie dans dest ce que contient source A LA SUITE DE DEST : SI PAS DE PLACE TEMPI !
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	// printf ("dest <%s> src <%s>\n", *dest, src);
	// printf("TEST\n");
	while (tok->arg[i] != '\0')
		i++;
	// printf("TEST\n");
	// printf("i %d ", i);
	// printf("TEST\n");
	while (src[u] != '\0')
	{
		// printf("A TEST\n");
		tok->arg[i + u] = src[u];
		// i++;
		u++;
		// printf("B TEST\n");
	}
	// printf("TEST\n");
	// printf("i %d u %d\n", i, u);
	// printf ("dest <%s> src <%s>\n", *dest, src);
}
