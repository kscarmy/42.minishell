/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:11:40 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 13:46:14 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_src_in_dest_bis(char *dest, char *src, char *ret, char sep)
{
	int	sd;
	int	ss;

	sd = 0;
	ss = 0;
	while (dest && dest[sd] && dest[sd] != '\0')
	{
		ret[sd] = dest[sd];
		sd++;
	}
	if (sd > 0 && sep != 0)
	{
		ret[sd] = sep;
		sd++;
	}
	while (src[ss] != '\0')
	{
		ret[sd + ss] = src[ss];
		ss++;
	}
	ret[sd + ss] = '\0';
	ft_strdel(&src);
	return (ret);
}

char	*ft_src_in_dest(t_data *data, char *dest, char *src, char sep)
{
	int		sd;
	int		ss;
	char	*ret;

	sd = ft_str_size(dest);
	ss = ft_str_size(src);
	if (sep != 0)
		ret = ft_malloc_str(data, sd + ss + 1);
	else
		ret = ft_malloc_str(data, sd + ss);
	return (ft_src_in_dest_bis(dest, src, ret, sep));
}

char	*ft_str_cpy(char *stra, char *strb)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (stra[i] && stra[i] != '\0')
		i++;
	while (strb[u] && strb[u] != '\0')
	{
		stra[i + u] = strb[u];
		u++;
	}
	return (stra);
}

int	ft_str_after_cut(char *str)
{
	if (str[0] == '\0')
		return (1);
	if (str[0] == ' ')
		return (1);
	if (ft_is_separator(str, 0) != 0)
		return (1);
	return (0);
}

void	ft_copie_dest_src(t_token *tok, char *src)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (tok->arg[i] != '\0')
		i++;
	while (src[u] != '\0')
	{
		tok->arg[i + u] = src[u];
		u++;
	}
}
