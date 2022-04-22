/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 03:50:34 by guderram          #+#    #+#             */
/*   Updated: 2022/04/22 05:21:20 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_ret_simple_quote(t_data *data, char *str, int incr) // renvoie la chaine entre simple quote. Applique PAS les $UN_TRUC si besoin
{
	int		i;
	char	*ret;

	i = 1;
	while (str[i] && str[i] != '\'')
		i++;
	if (incr == 1) // choisi ou pas d'incrementer data->i
		data->i = data->i + i;
	ret = ft_malloc_str(data, i);
	i = 1;
	while (str[i] && str[i] != '\'')
	{
		ret[i - 1] = str[i];
		i++;
	}
	ret[i - 1] = '\0';
	// printf ("ret smp quote <%s>\n", ret);
	return (ret);
}

char	*ft_ret_double_quote(t_data *data, char *str, int incr) // renvoie la chaine entre double quote. Applique les $UN_TRUC si besoin
{
	int		i;
	int 	u; // pour le malloc
	char	*ret;

	printf("entree dbl q\n");
	u = 0; // car ne prend pas le premier < " > dans le malloc
	i = 1; // pour skip le premier < " >
	while (str[i] && str[i] != '\"')
		i++;
	if (incr == 1) // choisi ou pas d'incrementer data->i
		data->i = data->i + i; // incre data avant tout pour pas bugger 
	i = 1;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			u = u + ft_str_size(ft_ret_dollar(data, &str[i]));
			while (str[i] && str[i] != ' ' && str[i] != '$' && ft_is_separator(str, i) == 0 && str[i] != '\"')
				i++;
		}
		else
		{
			u++;
			i++;
		}
	}
	printf("dbl q size <%d>\n", u);
	ret = ft_malloc_str(data, u);
	i = 1;
	u = 0;
	printf("malloc ret ok\n");
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			ft_copie_dest_src(data->token, ft_ret_dollar(data, &str[i]));
			u = u + ft_str_size(ft_ret_dollar(data, &str[i]));
			while (str[i] && str[i] != ' ' && str[i] != '$' && ft_is_separator(str, i) == 0 && str[i] != '\"')
				i++;
		}
		else
		{
			ret[u] = str[i];
			u++;
			i++;
		}
	}
	ret[u] = '\0';
	printf("exit bdl q\n");
	return (ret);
}

char	*ft_ret_dollar(t_data *data, char *str) // renvoie la valeur directe de var name, si str n'existe pas renvoie un null
{
	int		i;
	char	*ret;
	t_var	*var;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '$' && ft_is_separator(str, i) == 0 && str[i] != '\'' && str[i] != '\"')
		i++;
	ret = ft_malloc_str(data, i);
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '$' && ft_is_separator(str, i) == 0 && str[i] != '\'' && str[i] != '\"')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	var = ft_found_var_name(data, ret);
	if (var == NULL)
		return (NULL);
	ft_strdel(&ret);
	ret = ft_malloc_str(data, ft_str_size(var->value));
	i = 0;
	while (var->value[i])
	{
		ret[i] = var->value[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
