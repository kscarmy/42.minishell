/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_bin_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:39:29 by guderram          #+#    #+#             */
/*   Updated: 2022/07/09 01:52:31 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_bin_inter_sub(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str && str[i])
	{
		i = i + ft_space(str, i);
		if (str[i] != ' ')
			ret++;
		while (str && str[i] && str[i] != ' ')
			i++;
		i = i + ft_space(str, i);
	}
	return (ret);
}

void	ft_cut_bin_bis(t_data *data, char *str)
{
	int	dol;
	int	u;

	dol = data->dol;
	u = 0;
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	u = ft_cut_bin_inter_size(data, &data->input[data->i], str);
	data->dol = 0;
	printf("ft_cut_bin : u %d\n", u);
	data->token->bin = (char **)malloc(sizeof(char *) * (u + 1));
	data->token->bin[u] = NULL;
	data->dol = dol;
}

int	ft_cut_bin(t_data *data, char *str)
{
	int	i;

	i = 0;
	ft_cut_bin_bis(data, str);
	if (data->dol == 1)
	{
		ft_cut_inter_malloc(data, data->token, str, i);
		i = i + ft_cut_bin_inter_sub(str);
	}
	else
	{
		data->token->bin[i] = ft_str_malloc_cpy(data, str);
		i++;
	}
	data->dol = 0;
	ft_cut_bin_inter_malloc(data, data->token, &data->input[data->i], i);
	data->dol = 0;
	data->token->cmd = 9;
	return (1);
}

char	*ft_str_malloc_cpy(t_data *data, char	*str)
{
	int		i;
	int		size;
	char	*ret;

	i = 0;
	size = ft_str_size(str);
	ret = ft_malloc_str(data, size);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_bin_size(char *str)
{
	int		nbr;
	int		u;

	u = 0;
	nbr = 1;
	while (str[u] && ft_is_separator(str, u) == 0)
	{
		u = u + ft_space(str, u);
		while (str && str[u] && str[u] != ' ' && ft_is_separator(str, u) == 0)
			u++;
		u = u + ft_space(str, u);
		nbr++;
	}
	return (nbr);
}
