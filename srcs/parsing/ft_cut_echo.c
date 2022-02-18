/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:16:44 by guderram          #+#    #+#             */
/*   Updated: 2022/02/18 07:44:46 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cut_echo(t_data *data, int i) // ret 1 si echo trouver, sinon ret 0. i est la tete de lecture ou demarre la lecture
{
	char	*str;
	int		u;

	u = 0;
	str = "echo";
	while (data->input[i] && data->input[i] != ' ')
	{
		if (ft_is_a_b(data->input[i], str[u]) == 1)
			u++;
		i++;
	}
	// printf("\ncut echo :\ni : %d\nu : %d\n", i , u); // A SUPP
	if (u == 4)
	{
		ft_cut_echo_option(data, i);
		return (1);
	}
	return (0);
}

void	ft_cut_echo_option(t_data *data, int i)
{
	char	*str;
	int		u;

	str = "-n";
	u = 0;
	// printf("\necho op 1 :\ni : %d\nstr[i] : '%c'\nu : %d\n", i,data->input[i], u); // A SUPP
	i = i + ft_space(data->input, i);
	// printf("\necho op 2 :\ni : %d\nstr[i] : '%c'\nu : %d\n", i,data->input[i], u); // A SUPP
	// printf("\necho option i %d\n", i);
	// printf("echo option str '%c'\n", data->input[i]);
	// printf("\necho op 2 :\ni : %d\nu : %d\n", i , u); // A SUPP
	if (ft_is_a_b(data->input[i], str[0]) == 1)
		u++;
	while (ft_is_a_b(data->input[i + u], str[1]) == 1)
		u++;
	// printf("\necho op 3 :\ni : %d\nstr[i] : '%c'\nu : %d\n", i,data->input[i], u); // A SUPP
	// printf("\necho op 3 :\ni : %d\nu : %d\n", i , u); // A SUPP
	if (u >= 2)
		i = i + u;
	i = i + ft_space(data->input, i);
	data->i = data->i + i;
	// printf("\necho op 4 :\ni : %d\ndata i : %d\nstr[i] : '%c'\nu : %d\n", i, data->i, data->input[i], u); // A SUPP
	// printf("\necho op 4 :\ni : %d\nu : %d\n", i , u); // A SUPP
	ft_create_echo_token(data, u);
}


void	ft_create_echo_token(t_data *data, int option) // fonction qui cree le token echo avec ou sans option : si u >= 2 alors option
{
	int	u;

	u = 0;
	if (data->first == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->first->cmd = 1;
	if (option >= 2)
		data->first->option = 1;
	// printf("\nTok 1 :\ni : %d\nstr[i] : '%c'\nu : %d\n", data->i, data->input[data->i], u); // A SUPP
	while (ft_is_separator(data->input, (data->i + u)) == 0 && data->input[data->i + u])
		u++;
	// printf("\nTok 2 :\ni : %d\nstr[i] : '%c'\nu : %d\n", data->i, data->input[data->i], u); // A SUPP
	data->first->str = ft_malloc_str(data, u);
	if (data->first->str != NULL)
	{
		data->first->str = ft_strncpy(data->first->str, &(data->input[data->i]), u);
	}
	else
		data->err = 200; // erreur malloc
}
