/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:16:44 by guderram          #+#    #+#             */
/*   Updated: 2022/02/17 19:11:42 by guderram         ###   ########.fr       */
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
		while (ft_is_a_b(data->input[i], str[u]) == 1)
			u++;
		i++;
	}
	printf("\ncut echo :\ni : %d\nu : %d\n", i , u); // A SUPP
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
	printf("\necho op 1 :\ni : %d\nu : %d\n", i , u); // A SUPP
	i = ft_space(data->input, i);
	printf("\necho op 2 :\ni : %d\nu : %d\n", i , u); // A SUPP
	while (data->input[i] && data->input[i] != ' ') //  verifier que si "-n" a plusieurs n, ceux ci sont comptes
	{
		while (ft_is_a_b(data->input[i], str[u]) == 1)
			u++;
		i++;
	}
	printf("\necho op 3 :\ni : %d\nu : %d\n", i , u); // A SUPP
	if (u >= 2)
		i = i + u;
	data->i = data->i + i;
	printf("\necho op 4 :\ni : %d\nu : %d\n", i , u); // A SUPP
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
	while (ft_is_separator(data->input, data->i) == 0 && data->input[data->i + u])
		u++;
	data->first->str = malloc(sizeof(char) * (u + 1));
	if (data->first->str != NULL)
	{
		data->first->str = ft_strncpy(data->first->str, &data->input[data->i], u);
	}
	else
		data->err = 200; // erreur malloc
}
