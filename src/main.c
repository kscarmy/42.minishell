/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:35:54 by guderram          #+#    #+#             */
/*   Updated: 2022/02/24 08:10:01 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	argc = 0;
	argv = NULL;
	// char *line;
	t_data	*data;
//	t_var *var;

	(void)argc;
	(void)argv;
//	int i = 0; // A SUPP


	(void)env;   // void temporaire pour compiler.
	data = malloc(sizeof(t_data));
	if (ft_init_data(data, env) == 0)
		return (0); // erreur
	// printf("pwd : '%s'\nopwd : '%s'\n", data->pwd, data->opwd);

	/*		Tests		*/
//	var = ft_found_var_name(data, "USER");
//	printf("var = %s\n", var->value);
	write(0, "~$ ", 3);
	while (data->exit == 0 && get_next_line(0, &data->input) > 0)
	{

		/* commande de parsing a inserer ici */
		ft_parse_input(data);

		/* commande d'execusion des tokens a inserer ici */
		if ((data->exit == 0) && (data->token != NULL))
			ft_while_token(data);

			/*	test avec echo	*/
		ft_delete_token(data, data->token);

			/*	commande de reset de data	*/
		ft_clear_for_new_input(data);
		if (data->exit == 0)
			write(0, "~$ ", 3);
		else
			ft_putstr("exit\n");
	}
	// ft_test(data);

	/*	fonction qui clear tout a faire	*/

	return (0);
}
