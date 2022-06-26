/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:45:12 by guderram          #+#    #+#             */
/*   Updated: 2022/06/26 12:15:42 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	ft_cut_bin_inter_size(t_data *data, char *str)

int	ft_cut_bin_inter_size(t_data *data, char *str, char *stra) // str = &data->input[data->i], stra = premiere string
{
	int	ret; // size on **bin
	int	i;
	// char	*str;
	char	*tmp;

	int	stop = 0; // A SUPP
	
	printf("ft_cut_bin_inter_size : entree : \n");
	if (data->dol == 1)
		ret = ft_cut_bin_inter_sub(stra);
	else
		ret = 1;
	i = 0;
	tmp = NULL;
	// str = &data->input[data->i];
	while (str && str[i] == ' ')
		i++;
	while (str && str[i] && ft_is_separator(str, i) == 0 && i < ft_str_size(str) && stop < 5)
	{
		printf("ft_cut_bin_inter_size : while : i %d, stra <%s> str <%s>\n", i, stra, str);
		data->dol = 0;
		tmp = ft_one_arg(data, i);
		ft_parse_input_interpret(data, i);
		if (data->dol == 1)
			ret = ret + ft_cut_bin_inter_sub(tmp);
		else
			ret++;
		i = i + ft_incre_one_arg(data, i);
		// i++;
		ft_strdel(&tmp);
		stop++;
	}
	printf("ft_cut_bin_inter_size : sortie : \n");
	return (ret);
}

int	ft_cut_bin_inter_sub(char *str) // retourne le nombre d'arguments dans une string
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	printf("ft_cut_bin_inter_sub : entree\n");
	while (str && str[i] == ' ')
		i++;
	if (str && str[i] != ' ')
		ret++;
	while (str && str[i])
	{
		if (str[i] == ' ')
			ret++;
		while (str[i] == ' ')
			i++;
		i++;
	}
	return (ret);
}

int	ft_cut_bin(t_data *data, char *str)
{
	int	u;
	int	i;

	i = 1;
	printf("ft_cut_bin : dol %d\n", data->dol);
	printf("ft_cut_bin : bin size %d\n", ft_cut_bin_inter_size(data, &data->input[data->i], str));
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	u = ft_bin_size(data);
	data->token->bin = (char **)malloc(sizeof(char *) * (u + 1));
	u = ft_space(data->input, data->i);
	data->token->bin[0] = ft_str_malloc_cpy(data, str);
	u = u + ft_space(data->input, data->i + u);
	while (data->input[data->i + u]
		&& ft_is_separator(data->input, data->i + u) == 0)
	{
		u = u + ft_space(data->input, data->i + u);
		data->token->bin[i] = ft_one_arg(data, u);
		u = ft_incre_one_arg(data, u);
		u = u + ft_space(data->input, data->i + u);
		i++;
	}
	data->token->bin[i] = NULL;
	data->i = data->i + u;
	data->dol = 0;
	return (1);
}

char	*ft_str_malloc_cpy(t_data *data, char	*str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_malloc_str(data, ft_str_size(str));
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_bin_size(t_data *data)
{
	int		nbr;
	int		u;

	u = 0;
	nbr = 1;
	while (data->input[data->i + u]
		&& ft_is_separator(data->input, data->i + u) == 0)
	{
		u = u + ft_space(data->input, data->i + u);
		u = ft_incre_one_arg(data, u);
		u = u + ft_space(data->input, data->i + u);
		nbr++;
	}
	data->token->cmd = 9;
	return (nbr);
}
