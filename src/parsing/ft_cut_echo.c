/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:16:44 by guderram          #+#    #+#             */
/*   Updated: 2022/05/18 15:08:46 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_echo(t_data *data, int i) // ret 1 si echo trouver, sinon ret 0. i est la tete de lecture ou demarre la lecture
{
	// char	*str;
	// int		u;

	// u = 0;
	// str = "echo";
	// while (data->input[i] && data->input[i] != ' ')
	// {
	// 	if (ft_is_a_b(data->input[i], str[u]) == 1)
	// 		u++;
	// 	i++;
	// }
	// if (u == 4)
	// {
	// 	ft_cut_echo_option(data, i);
	// 	return (1);
	// }

	if (ft_strncmp(&data->input[i], "echo", 4) != 0)
		return (0);
	i = i + 4;
	// printf("\necho pre ok\n");
	if (ft_str_after_cut(&data->input[i]) != 1)
		return (0);
	// printf("\necho ok\n");
	ft_cut_echo_option(data, i);
	// printf("\necho sortie data->i : %d\n", data->i);
	return (1);
}

void	ft_cut_echo_option(t_data *data, int i)
{
	char	*str;
	int		u;

	str = "-n";
	u = 0;
	i = i + ft_space(data->input, i);
	if (ft_is_a_b(data->input[i], str[0]) == 1)
		u++;
	while (ft_is_a_b(data->input[i + u], str[1]) == 1)
		u++;
	if (u >= 2)
		i = i + u;
	i = i + ft_space(data->input, i);
	// printf("cut echo option i %d\n", i);
	data->i = i;
	ft_create_echo_token(data, u);
}


void	ft_create_echo_token(t_data *data, int option) // fonction qui cree le token echo avec ou sans option : si u >= 2 alors option
{
	// int	u;

	// u = 0;
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 1;
	if (option >= 2)
		data->token->option = 1;
	printf("CREATE ECHO TOKEN :\n");


	// ft_malloc_arg(data, data->token); // OLD


	ft_malloc_builtin_arg(data, data->token);

	printf("END CREATE ECHO TOKEN :\n");
	// printf("echo u %d\n", u);
	// data->token->arg = ft_malloc_str(data, u);
	// if (u > 0 && data->token->arg != NULL)
	// {
	// 	data->token->arg = ft_strncpy(data->token->arg, &(data->input[data->i]), u);
	// 	data->token->arg = cut_str(data, data->token->arg);
	// 	data->i = data->i + u;
	// }
	// else
	// 	data->err = 200; // erreur malloc
	
}
