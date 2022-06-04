/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:45:12 by guderram          #+#    #+#             */
/*   Updated: 2022/06/04 20:22:54 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	ft_cut_bin(t_data *data) // ret 1 si echo trouver, sinon ret 0. i est la tete de lecture ou demarre la lecture
// {
// 	int	i;

// 	i = data->i;
// 	// printf("\ncut bin : '%s'\n", &data->input[i]);
// 	while (data->input[i] && data->input[i] != ' ' && ft_is_separator(data->input, i) == 0)
// 		i++;
// 	if (i > 0)
// 	{
// 		// printf ("cut bin i %d\n", i);
// 		if (data->token == NULL)
// 			ft_init_token(data);
// 		else
// 			ft_add_new_token(data);
// 		ft_create_bin_token(data);
// 		return (1);
// 	}
// 	return (0);
// }

// int		ft_bin_count(t_data *data, int i) // revoie le nombre de cases a malloc
// {
// 	int u;

// 	u = 1;
// 	while (data->input[i] && ft_is_separator(data->input, i) == 0)
// 	{
// 		if (ft_space(data->input, i) > 0)
// 		{
// 			i = i + ft_space(data->input, i);
// 			u++;
// 		}
// 		i++;
// 	}
// 	return (u);
// }

// int		ft_bin_arg_size(t_data *data, int i) // renvoie la taille d'un argument
// {
// 	int	u;

// 	u = 0;
// 	while (data->input[i + u] && data->input[i + u] != ' ' && ft_is_separator(data->input, (i + u)) == 0)
// 		u++;
// 	return (u);
// }

// void	ft_malloc_bin(t_data *data) // malloc le **bin
// {
// 	int	cases;
// 	int	i;
// 	int	u;

// 	i = data->i;
// 	u = 0;
// 	cases = ft_bin_count(data, data->i);
// 	data->token->bin = malloc(sizeof(char *) * (cases + 1));
// 	// printf("malloc bin : data[i] <%s>\n", &data->input[i]);
// 	if (data->token->bin == NULL)
// 		data->err = 2010;
// 	else
// 	{
// 		while (data->input[i] && ft_is_separator(data->input, (i)) == 0 && data->input[i] != ' ')
// 		{
// 			// printf("malloc bin : i 1 %d <%s>\n", i, &data->input[i]);
// 			i = i + ft_space(data->input, i);
// 			// printf("malloc bin : i 2 %d <%s>\n", i, &data->input[i]);
// 			data->token->bin[u] = malloc(sizeof(char *) * (ft_bin_arg_size(data, i)));
// 			if (data->token->bin[u] != NULL)
// 				data->token->bin[u] = ft_strncpy(data->token->bin[u], &(data->input[i]), ft_bin_arg_size(data, i));
// 			else
// 				data->err = 2020;
// 			// printf("malloc bin : i 3 %d <%s>\n", i, &data->input[i]);
// 			i = i + ft_bin_arg_size(data, i);
// 			// printf("malloc bin : i 4 %d <%s>\n", i, &data->input[i]);
// 			// printf("malloc bin : <%s>\n", data->token->bin[u]);
// 			u++;
// 		}
// 		// printf("malloc bin : <%s>\n", data->token->bin[u]);
// 		data->token->bin[u] = NULL;
// 		// data->i = data->i + i;
// 	}
// }

// void	ft_create_bin_token(t_data *data) // fonction qui cree le token bin
// {
// 	int	u;

// 	u = 0;
// 	data->token->cmd = 9;
// 	ft_malloc_bin(data);
// 	while (data->input[data->i + u] && ft_is_separator(data->input, (data->i + u)) == 0)
// 		u++;
// 	data->i = data->i + u;

	// int i = 0;
	// printf("create bin tok :\n");
	// printf("create bin tok : tok <%p>\n", data->token);
	// printf("create bin tok : bin <%p>\n", data->token->bin);
	// while (data->token->bin != NULL && data->token->bin[i])
	// {
	// 	printf("%d '%s'\n",i ,data->token->bin[i]);
	// 	i++;
	// }
	// printf("create bin tok : <%s>\n", data->token->bin[0]);
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
// }

/*	Nouveau cut bin	*/

int	ft_cut_bin(t_data *data) // ret 1 si echo trouver, sinon ret 0. i est la tete de lecture ou demarre la lecture
{
	int	u;
	int i;
	// char	*tmp;

	i = 0;
	// ft_putstr("CUT BIN :\n");
	u = ft_bin_size(data);
	// ft_putnbr(u);
	// ft_putstr("CUT BIN : 1\n");
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 9;
	// ft_putstr("CUT BIN : 2\n");
	data->token->bin = (char **)malloc(sizeof(char*) * (u + 1));
	// ft_putstr("CUT BIN : 3\n");
	// if (data->token->bin == NULL)
	// 	ft_putstr("CUT BIN : NULL\n");

	data->token->bin[u] = NULL;
	
	u = 0;
	// ft_putnbr(u);
	u = u + ft_space(data->input, data->i + u);
	// ft_putstr("CUT BIN : 4\n");
	// ft_putnbr(u);
	ft_strdel(&data->token->arg);
	// data->token->arg = ft_src_in_dest(data, data->token->arg, ft_one_arg(data, u), 0);
	// ft_putstr("CUT BIN : 5\n");
	u = u + ft_space(data->input, data->i + u);
	// ft_putstr("CUT BIN : 6\n");
	// printf("BIN : data->token->arg : <%s>\n", data->token->arg);
	while (data->input[data->i + u] && ft_is_separator(data->input, data->i + u) == 0)
	{
		// printf("malloc builtin : debut while\n");
		u = u + ft_space(data->input, data->i + u);
		// printf("malloc builtin : one arg\n");
		data->token->bin[i] = ft_one_arg(data, u);
		// data->token->bin[i] = ft_src_in_dest(data, NULL, ft_one_arg(data, u), 0);
		// printf("malloc builtin : incre one arg : u %d <%s>\n", u, &data->input[data->i + u]);
		u = ft_incre_one_arg(data, u);
		
		u = u + ft_space(data->input, data->i + u);
		// printf("malloc builtin : fin while : u %d <%s>\n", u, &data->input[data->i + u]);
		i++;
	}
	// ft_putstr("CUT BIN : 7\n");
	data->i = data->i + u;
	return (1);
}

int	ft_bin_size(t_data *data) // permet de malloc la strucure de bin
{
	int		u;
	int max = 0;
	int nbr = 0;

	u = 0;
	while (data->input[data->i + u] && ft_is_separator(data->input, data->i + u) == 0 && max < 20)
	{
		// printf("malloc builtin : debut while\n");
		u = u + ft_space(data->input, data->i + u);
		// printf("malloc builtin : one arg\n");
		// tok->arg = ft_src_in_dest(data, tok->arg, ft_one_arg(data, u), ' ');
		// printf("malloc builtin : incre one arg : u %d <%s>\n", u, &data->input[data->i + u]);
		u = ft_incre_one_arg(data, u);
		
		u = u + ft_space(data->input, data->i + u);
		// printf("malloc builtin : fin while : u %d <%s>\n", u, &data->input[data->i + u]);
		max ++;
		nbr++;
	}
	return (nbr);
	// printf("bin : nbr arg : %d\n", nbr);
	// data->i = data->i + u;
}
