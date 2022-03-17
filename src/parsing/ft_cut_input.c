/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:50 by guderram          #+#    #+#             */
/*   Updated: 2022/03/17 18:15:19 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_parse_cmd_not_found(t_data *data) // commande non trouvee
{
	ft_putstr("minishell : command not found : ");
	ft_putstr(&(data->input[data->i]));
	ft_putchar('\n');
	return (-1);
}

int	ft_parse_input(t_data *data) // return 0 si ok, sinon 1 ou numero specifique a l'erreur
{
	int	found;

	data->i = 0;
	found = 0;
	while (data->exit == 0 && found >= 0 && data->input[data->i])
	{
		// printf("prefonc data i : '%s'\n", &(data->input[data->i]));
		found = 0;
		data->i = data->i + ft_space(data->input, data->i);
		if (cut_history(data) == 1)		// checks if command is "history" and creates its token
			found++;
		else 
			add_history(data->input, 1);	// adds line to history if it is not "history"
		if (found == 0 && ft_cut_exit(data))		// sets data->exit = 1 if command is "exit"
			found++;
		printf("i : %d", data->i);
		if (found == 0 && ft_cut_env(data, data->i) == 1)			// checks if command is "env" and creates its token
		{
			printf("incre env found\n");
			found++;
		}
		printf(" %d", data->i);
		if (found == 0 && ft_cut_cd(data))
			found++;
		printf(" %d", data->i);
		if (found == 0 && ft_cut_echo(data, data->i) == 1)
		{
			found++;
		}
		printf(" %d PWD", data->i);
		if (found == 0 && ft_cut_pwd(data) == 1)
			found++;
		printf(" %d", data->i);
		if (found == 0 && ft_cut_export(data) == 1)
			found++;
		printf(" %d", data->i);
		if (found == 0 && ft_cut_unset(data, data->i) == 1)
			found++;
		printf(" %d RE", data->i);
		if (found == 0 && ft_cut_redirects(data) == 1)
			found++;
		printf(" %d\n", data->i);
		// if (found == 0 && ft_cut_bin(data) == 1)
		// 	found++;
		// printf("aftfonc data i : '%s'\n", &(data->input[data->i]));
		if (found == 0)
			found = ft_parse_cmd_not_found(data);
		printf("PARSE INPUT end while i %d, '%s'", data->i, &(data->input[data->i]));
	}
	if (found == -1)
		return (1); // pas de commande trouvee
	return (0);
}




// int	ft_parse_input(t_data *data) // return 0 si ok, sinon 1 ou numero specifique a l'erreur
// {
// 	int	found;

// 	data->i = 0;
// 	found = 0;

// 	if (ft_cut_exit(data))			// sets data->exit = 1 if command is "exit"
// 		return (0);

// 	if (cut_history(data) == 1)		// checks if command is "history" and creates its token
// 		found++;
// 	else 
// 		add_history(data->input, 1);	// adds line to history if it is not "history"
	
// 	if (ft_cut_env(data))			// checks if command is "env" and creates its token
// 		found++;
	
// 	if (ft_cut_cd(data))
// 		found++;
// 	while (data->input[data->i])
// 	{
// 		found = 0;
// 		ft_space(data->input, data->i);
// 		if (found == 0 && ft_cut_echo(data, data->i) == 1)
// 			found++;
// 		if (found == 0 && ft_cut_pwd(data) == 1)
// 			found++;
// 		if (found == 0 && ft_cut_export(data) == 1)
// 			found++;
// 		if (found == 0 && ft_cut_unset(data, data->i) == 1)
// 			found++;
// 		if (found == 0 && ft_cut_redirects(data) == 1)
// 			found++;
// 		if (found == 0 && ft_cut_bin(data) == 1)
// 			found++;
// 		data->i = data->i + 1;
// 	}
// 	if (found == 0)
// 	{
// 		if (!'\n')
// 			printf("minishell : command not found : %s\n", data->input);
// 		return (1); // pas de commande trouvee
// 	}
// 	return (0);
// }


