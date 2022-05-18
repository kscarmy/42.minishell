/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:45:12 by guderram          #+#    #+#             */
/*   Updated: 2022/05/18 23:03:23 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_bin(t_data *data) // ret 1 si echo trouver, sinon ret 0. i est la tete de lecture ou demarre la lecture
{
	int	i;

	i = data->i;
	while (data->input[i] && data->input[i] != ' ' && ft_is_separator(data->input, i) == 0)
		i++;
	if (i > 0)
	{
//		printf ("cut bin i %d\n", i);
		if (data->token == NULL)
			ft_init_token(data);
		else
			ft_add_new_token(data);
		ft_create_bin_token(data);
		return (1);
	}
	return (0);
}

int		ft_bin_count(t_data *data, int i) // revoie le nombre de cases a malloc
{
	int u;

	u = 1;
	while (data->input[i] && ft_is_separator(data->input, i) == 0)
	{
		if (ft_space(data->input, i) > 0)
		{
			i = i + ft_space(data->input, i);
			u++;
		}
		i++;
	}
	return (u);
}

int		ft_bin_arg_size(t_data *data, int i) // renvoie la taille d'un argument
{
	int	u;

	u = 0;
	while (data->input[i + u] && data->input[i + u] != ' ' && ft_is_separator(data->input, (i + u)) == 0)
		u++;
	return (u);
}

void	ft_malloc_bin(t_data *data) // malloc le **bin
{
	int	cases;
	int	i;
	int	u;

	i = data->i;
	u = 0;
	cases = ft_bin_count(data, data->i);
	data->token->bin = malloc(sizeof(char *) * (cases + 1));
	if (data->token->bin == NULL)
		data->err = 2010;
	else
	{
		while (data->input[i] && ft_is_separator(data->input, (i)) == 0)
		{
			i = i + ft_space(data->input, i);
			data->token->bin[u] = malloc(sizeof(char *) * (ft_bin_arg_size(data, i)));
			if (data->token->bin[u] != NULL)
			{
				data->token->bin[u] = ft_strncpy(data->token->bin[u], &(data->input[i]), ft_bin_arg_size(data, i));
				data->token->bin[0][ft_bin_arg_size(data, i)] = '\0';
			}
			else
				data->err = 2020;
			i = i + ft_bin_arg_size(data, i);
			u++;
		}
		data->token->bin[u] = NULL;
		// data->i = data->i + i;
	}
}

void	ft_create_bin_token(t_data *data) // fonction qui cree le token bin
{
	int	u;

	u = 0;
	data->token->cmd = 9;
	ft_malloc_bin(data);
	while (data->input[data->i + u] && ft_is_separator(data->input, (data->i + u)) == 0)
		u++;
	data->i = data->i + u;
	// while (data->input[data->i + u] != ' ' && ft_is_separator(data->input, (data->i + u)) == 0 && data->input[data->i + u])
	// 	u++;
	// data->token->bin = ft_malloc_str(data, u);
	// if (data->token->bin != NULL)
	// 	data->token->bin = ft_strncpy(data->token->bin, &(data->input[data->i]), u);
	// else
	// 	data->err = 2001; // erreur malloc
	// data->i = data->i + u;
	// u = 0;
	// data->i = data->i + ft_space(data->input, data->i);
	// while (ft_is_separator(data->input, (data->i + u)) == 0 && data->input[data->i + u])
	// 	u++;
	// if (u > 0)
	// 	data->token->arg = ft_malloc_str(data, u);
	// if (u > 0 && data->token->arg != NULL)
	// 	data->token->arg = ft_strncpy(data->token->arg, &(data->input[data->i]), u);
	// if (u > 0 && data->token->arg == NULL)
	// 	data->err = 2002; // erreur malloc
}
