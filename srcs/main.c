/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:35:54 by guderram          #+#    #+#             */
/*   Updated: 2022/02/17 20:30:17 by guderram         ###   ########.fr       */
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
	while (data->exit == 0 && get_next_line(0, &data->input) > 0)
	{
		
		/* commande de parsing a inserer ici */
		ft_parse_input(data);
		
		/* commande d'execusion des tokens a inserer ici */
		if (data->exit == 0)
			ft_while_token(data);
		
		/*	commande de reset de data	*/
		ft_clear_for_new_input(data);
		write(0, "~$ ", 3);
	}
	
	/*	fonction qui clear tout a faire	*/

	return (0);
}
