/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:56:24 by guderram          #+#    #+#             */
/*   Updated: 2022/06/06 16:14:18 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_separator(char *str, int i)
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

char	*ft_malloc_str(t_data *data, int i)
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

void	ft_str_join_input(t_data *data, int i, int max)
{
	int		u;
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

int	ft_str_size(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str != NULL && str[i] && str[i] != '\0')
		i++;
	return (i);
}

// int	ft_check_char(char *str, char c, int max)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && i < max)
// 	{
// 		if (str[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_str_comp(char *str1, char *str2)
// {
// 	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0
// 		&& ft_strncmp(str1, str2, ft_strlen(str2)) == 0)
// 		return (1);
// 	return (0);
// }

// int	ft_str_after_cut(char *str)
// {
// 	if (str[0] == '\0')
// 		return (1);
// 	if (str[0] == ' ')
// 		return (1);
// 	if (ft_is_separator(str, 0) != 0)
// 		return (1);
// 	return (0);
// }

// void	ft_copie_dest_src(t_token *tok, char *src)
// {
// 	int	i;
// 	int	u;

// 	i = 0;
// 	u = 0;
// 	while (tok->arg[i] != '\0')
// 		i++;
// 	while (src[u] != '\0')
// 	{
// 		tok->arg[i + u] = src[u];
// 		u++;
// 	}
// }

// char	*ft_src_in_dest(t_data *data, char *dest, char *src, char sep)
// {
// 	int		sd;
// 	int		ss;
// 	char	*ret;

// 	sd = ft_str_size(dest);
// 	ss = ft_str_size(src);
// 	if (sep != 0)
// 		ret = ft_malloc_str(data, sd + ss + 1);
// 	else
// 		ret = ft_malloc_str(data, sd + ss);
// 	sd = 0;
// 	ss = 0;
// 	while (dest && dest[sd] && dest[sd] != '\0')
// 	{
// 		ret[sd] = dest[sd];
// 		sd++;
// 	}
// 	if (sd > 0 && sep != 0)
// 	{
// 		ret[sd] = sep;
// 		sd++;
// 	}
// 	while (src[ss] != '\0')
// 	{
// 		ret[sd + ss] = src[ss];
// 		ss++;
// 	}
// 	ret[sd + ss] = '\0';
// 	ft_strdel(&src);
// 	return (ret);
// }

// char	*ft_str_cpy(char *stra, char *strb)
// {
// 	int	i;
// 	int	u;

// 	i = 0;
// 	u = 0;
// 	while (stra[i] && stra[i] != '\0')
// 		i++;
// 	while (strb[u] && strb[u] != '\0')
// 	{
// 		stra[i + u] = strb[u];
// 		u++;
// 	}
// 	return (stra);
// }

// int	ft_is_number(char c)
// {
// 	if (c <= '9' && c >= '0')
// 		return (1);
// 	else
// 		return (0);
// }
