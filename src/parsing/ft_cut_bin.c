/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:45:12 by guderram          #+#    #+#             */
/*   Updated: 2022/07/09 01:52:39 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_str_size_space(char *str, int i)
{
	while (str && str[i] && str[i] != ' ')
		i++;
	return (i);
}

void	ft_cut_inter_malloc(t_data *data, t_token *t, char *str, int ret)
{
	int	i;
	int	max;
	int	u;

	i = 0;
	u = 0;
	max = ft_bin_size(str);
	while (str && str[i] && u < max)
	{
		i = i + ft_space(str, i);
		t->bin[ret + u] = ft_malloc_str(data, ft_str_size_space(str, i));
		t->bin[ret + u] = ft_strncpy(t->bin[ret + u], &str[i],
				ft_str_size_space(str, i) - i);
		i = ft_str_size_space(str, i);
		i = i + ft_space(str, i);
		u++;
	}
}

int	ft_cut_bin_incre_one_arg(char *str, int u)
{
	u = u + ft_space(str, u);
	while (str[u] && str[u] != ' '
		&& ft_is_separator(str, u) == 0)
	{
		if (str[u] == '\'')
		{
			u++;
			while (str[u]
				&& str[u] != '\'')
				u++;
			u++;
		}
		else if (str[u] == '\"')
		{
			u++;
			while (str[u]
				&& str[u] != '\"')
				u++;
			u++;
		}
		else
			u++;
	}
	u = u + ft_space(str, u);
	return (u);
}

void	ft_cut_bin_inter_malloc(t_data *data, t_token *t, char *str, int ret)
{
	int		i;
	char	*tmp;

	i = ft_space(str, 0);
	tmp = NULL;
	while (str && str[i] && ft_is_separator(str, i) == 0
		&& i < ft_str_size(str))
	{
		data->dol = 0;
		tmp = ft_one_arg(data, i);
		ft_parse_input_interpret(data, i);
		if (data->dol == 1)
		{
			ft_cut_inter_malloc(data, t, tmp, ret);
			ret = ret + ft_cut_bin_inter_sub(tmp);
		}
		else
		{
			t->bin[ret] = ft_str_malloc_cpy(data, tmp);
			ret++;
		}
		i = ft_cut_bin_incre_one_arg(str, i);
		ft_strdel(&tmp);
	}
	data->i = data->i + i;
}

int	ft_cut_bin_inter_size(t_data *data, char *str, char *stra)
{
	int		ret;
	int		i;
	char	*tmp;

	if (data->dol == 1)
		ret = ft_cut_bin_inter_sub(stra);
	else
		ret = 1;
	i = ft_space(str, 0);
	tmp = NULL;
	while (str && str[i] && ft_is_separator(str, i) == 0
		&& i < ft_str_size(str))
	{
		i = i + ft_space(str, i);
		tmp = ft_one_arg(data, i);
		ft_parse_input_interpret(data, i);
		if (data->dol == 1)
			ret = ret + ft_cut_bin_inter_sub(tmp);
		else
			ret++;
		i = i + ft_cut_bin_incre_one_arg(str, i);
		ft_strdel(&tmp);
		data->dol = 0;
	}
	return (ret);
}
