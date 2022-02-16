/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:35:54 by guderram          #+#    #+#             */
/*   Updated: 2022/02/16 12:09:00 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


int	main(int argc, char **argv, char **env)
{
	argc = 0;
	argv = NULL;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (ft_init_env(data, env) == 0)
		return (0); // erreur
	
	/*		Tests		*/
	write(0, "~$ ", 3);
	while (get_next_line(0, &data->input) > 0)
	{

		// write(0, "\n", 3);
		// ft_putstr(data->input);
		
		/* commande de parsing a inserer ici */
		ft_parse_input(data);
		

		/* commande d'execusion des tokens a inserer ici */
		
		ft_while_token(data);
		// write(0, "\n", 3);
		write(0, "~$ ", 3);
	}
	// printf("\n");
	// while (data->env[i])
	// {
	// 	printf("%s\n", data->env[i]);
	// 	i++;
	// }
	/*		Tests		*/

	return (0);
}
