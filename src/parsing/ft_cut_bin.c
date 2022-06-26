/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:45:12 by guderram          #+#    #+#             */
/*   Updated: 2022/06/26 18:35:22 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_str_size_space(char *str, int i)
{
	//("--- ft_str_size_space : str[i] <%s>\n", &str[i]);
	while (str && str[i] && str[i] != ' ')
		i++;
	//("--- ft_str_size_space : str[i] <%s>\n", &str[i]);
	return (i);
}

void	ft_cut_inter_malloc(t_data *data, t_token *t, char *str, int ret)
{
	int	i;
	int	max;
	int u;

	i = 0;
	u = 0;
	//("----- ft_cut_inter_malloc : entree\n");
	max = ft_bin_size(str);
	// //("ft_cut_inter_malloc : entree\n");
	while (str && str[i] && u < max)
	{
		i = i + ft_space(str, i);
		// while (str && str[i] && str[i] != ' ')
		// 	i++;
		
		t->bin[ret + u] = ft_malloc_str(data, ft_str_size_space(str, i));
		t->bin[ret + u] = ft_strncpy(t->bin[ret + u], &str[i], ft_str_size_space(str, i) - i);
		// //("----- ft_cut_inter_malloc : 1 str[i] <%s> %d\n", &str[i], i);
		// //("----- ft_cut_inter_malloc : bin : <%s>\n", t->bin[ret + u]);
		i = ft_str_size_space(str, i);
		// //("----- ft_cut_inter_malloc : 2 str[i] <%s> %d\n", &str[i], i);
		i = i + ft_space(str, i);
		// //("----- ft_cut_inter_malloc : 3 str[i] <%s> %d\n", &str[i], i);
		u++;
	}
}

int	ft_cut_bin_incre_one_arg(char *str, int u)
{
	// ////printf("ft_incre_one_arg : entree : data i : %d u %d <%s>\n", data->i, u, &data->input[data->i + u]);
	while (str[u]
		&& str[u] != ' '
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
	// ////printf("ft_incre_one_arg : sortie : data i : %d u %d <%s>\n", data->i, u, &data->input[data->i + u]);
	return (u);
}

void	ft_cut_bin_inter_malloc(t_data *data, t_token *t ,char *str, int ret) // str = &data->input[data->i], stra = premiere string
{
	// int	ret;
	int	i;
	char	*tmp;

	////printf("\n\n");
	////printf("ft_cut_bin_inter_malloc : entree\n");
	//("ft_cut_bin_inter_malloc : str <%s> \n", str);
	// if (data->dol == 1)
	// 	ret = ft_cut_bin_inter_sub(stra);
	// else
	// 	ret = 1;
	i = ft_space(str, 0);
	tmp = NULL;
	while (str && str[i] && ft_is_separator(str, i) == 0 && i < ft_str_size(str))
	{
		//("ft_cut_bin_inter_malloc : while\n");
		data->dol = 0;
		tmp = ft_one_arg(data, i);
		////printf("ft_cut_bin_inter_malloc : tmp <%s>\n", tmp);
		ft_parse_input_interpret(data, i);
		if (data->dol == 1)
		{
			////printf("ft_cut_bin_inter_malloc : if\n");
			ft_cut_inter_malloc(data, t, tmp, ret);
			ret = ret + ft_cut_bin_inter_sub(tmp);
		}
		else
		{
			//printf("ft_cut_bin_inter_malloc : else\n");
			t->bin[ret] = ft_str_malloc_cpy(data, tmp);
			ret++;
		}
		//printf("--- ft_cut_bin_inter_malloc : 1 : str[i] <%s>\n", &str[i]);
		i = i + ft_space(str, i);
		//printf("--- ft_cut_bin_inter_malloc : 2 : str[i] <%s>\n", &str[i]);
		i = ft_cut_bin_incre_one_arg(str, i);
		//printf("--- ft_cut_bin_inter_malloc : 3 : str[i] <%s>\n", &str[i]);
		i = i + ft_space(str, i);
		ft_strdel(&tmp);
	}
	//printf("ft_cut_bin_inter_malloc : sortie\n");
	data->i = data->i + i;
	data->dol = 0;
}

int	ft_cut_bin_inter_size(t_data *data, char *str, char *stra) // str = &data->input[data->i], stra = premiere string
{
	int	ret;
	int	i;
	char	*tmp;

	if (data->dol == 1)
		ret = ft_cut_bin_inter_sub(stra);
	else
		ret = 1;
	i = ft_space(str, 0);
	tmp = NULL;
	//printf("ft_cut_bin_inter_size : entree : ret %d\n", ret);
	while (str && str[i] && ft_is_separator(str, i) == 0 && i < ft_str_size(str))
	{
		//printf("ft_cut_bin_inter_size : while 1 : i %d str <%s>\n", i, &str[i]);
		i = i + ft_space(str, i);
		//printf("ft_cut_bin_inter_size : while 2 : i %d str <%s>\n", i, &str[i]);
		tmp = ft_one_arg(data, i);
		ft_parse_input_interpret(data, i);
		//printf("ft_cut_bin_inter_size : while : i %d str <%s>\n", i, &str[i]);
		if (data->dol == 1)
		{
			//printf("ft_cut_bin_inter_size : while : ret 1 %d\n", ret);
			ret = ret + ft_cut_bin_inter_sub(tmp);
			//printf("ft_cut_bin_inter_size : while : ret 1 %d\n", ret);
		}
		else
		{
			//printf("ft_cut_bin_inter_size : while : ret 2 %d\n", ret);
			ret++;
			//printf("ft_cut_bin_inter_size : while : ret 2 %d\n", ret);
		}
		i = i + ft_cut_bin_incre_one_arg(str, i);
		//printf("ft_cut_bin_inter_size : while 3 : i %d str <%s>\n", i, &str[i]);
		i = i + ft_space(str, i);
		//printf("ft_cut_bin_inter_size : while 4 : i %d str <%s>\n", i, &str[i]);
		ft_strdel(&tmp);
		data->dol = 0;
	}
	//printf("ft_cut_bin_inter_size : ret %d\n", ret);
	data->dol = 0;
	return (ret);
}

int	ft_cut_bin_inter_sub(char *str) // retourne le nombre d'arguments dans une string
{
	int	i;
	int	ret;

	i = 0;
	// i = ft_space(str, i);
	ret = 0;
	//printf("ft_cut_bin_inter_sub : entree : str <%s>\n", str);
	// while (str && str[i] == ' ')
	// 	i++;
	if (str && str[i] != ' ')
		ret++;
	// i = i + ft_space(str, i);
	while (str && str[i])
	{
		//printf("ft_cut_bin_inter_sub : while 1 : str[i] <%s>\n", &str[i]);
		i = i + ft_space(str, i);
		//printf("ft_cut_bin_inter_sub : while 2 : str[i] <%s>\n", &str[i]);
		if (str[i] != ' ')
			ret++;
		while (str && str[i] && str[i] != ' ')
			i++;
		//printf("ft_cut_bin_inter_sub : while 3 : str[i] <%s>\n", &str[i]);
		i = i + ft_space(str, i);
		//printf("ft_cut_bin_inter_sub : while 4 : str[i] <%s>\n", &str[i]);
	}
	return (ret);
}

int	ft_cut_bin(t_data *data, char *str)
{
	int	u;
	int	i;
	int	dol;

	i = 0;
	u = 0;
	dol = data->dol;
	//("ft_cut_bin : dol %d\n", data->dol);
	//("ft_cut_bin : bin size %d\n", ft_cut_bin_inter_size(data, &data->input[data->i], str));
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	u = ft_cut_bin_inter_size(data, &data->input[data->i], str);
	printf("ft_cut_bin : u %d\n", u);
	data->token->bin = (char **)malloc(sizeof(char *) * (u + 1));
	data->token->bin[u] = NULL;
	data->dol = dol;
	if (data->dol == 1)
	{
		//("ft_cut_bin : if : str <%s> i %d\n", str, i);
		ft_cut_inter_malloc(data, data->token, str, i);
		//printf("ft_cut_bin : if 2\n");
		i = i + ft_cut_bin_inter_sub(str);
	}
	else
	{
		//printf("ft_cut_bin : else\n");
		data->token->bin[i] = ft_str_malloc_cpy(data, str);
		// ft_putstr("ft_cut_bin : else : ok\n");
		i++;
	}
	data->dol = 0;
	//printf("ft_cut_bin : u %d\n\n", u);
	
	ft_cut_bin_inter_malloc(data, data->token, &data->input[data->i], i);

	// data->token->bin = (char **)malloc(sizeof(char *) * (u + 1));
	// u = ft_space(data->input, data->i);
	// // //("ft_cut_bin : u %d\n", u);
	// data->token->bin[0] = ft_str_malloc_cpy(data, str);
	// u = u + ft_space(data->input, data->i + u);
	// while (data->input[data->i + u]
	// 	&& ft_is_separator(data->input, data->i + u) == 0)
	// {
	// 	u = u + ft_space(data->input, data->i + u);
	// 	data->token->bin[i] = ft_one_arg(data, u);
	// 	u = ft_incre_one_arg(data, u);
	// 	u = u + ft_space(data->input, data->i + u);
	// 	i++;
	// }
	// // //("ft_cut_bin : str <%s>\n", data->token->bin[0]);
	// data->token->bin[i] = NULL;
	// data->i = data->i + u;

	
	data->dol = 0;
	data->token->cmd = 9;
	//printf("ft_cut_bin : SORTIE\n");
	return (1);
}

char	*ft_str_malloc_cpy(t_data *data, char	*str)
{
	int		i;
	int		size;
	char	*ret;

	i = 0;
	size = ft_str_size(str);
	//("ft_str_malloc_cpy : entree : str <%s> size %d\n", str, size);
	ret = ft_malloc_str(data, size);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	//("ft_str_malloc_cpy : sortie : ret <%s>\n", ret);
	return (ret);
}

int	ft_bin_size(char *str)
{
	int		nbr;
	int		u;

	u = 0;
	nbr = 1;
	//("ft_bin_size : str <%s>\n", str);
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
