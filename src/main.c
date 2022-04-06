/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:35:54 by guderram          #+#    #+#             */
/*   Updated: 2022/04/03 10:21:59 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		ft_verif_pipe(t_pipe *p) // renvoie 1 si les pipe sont libres (== -10) sinon 0
{
	if(p->fd_i == -10 && p->fd_o == -10 && p->ofd_i == -10 && p->ofd_o == -10)
		return (1);
	else
		return (0);
}



void	prompt(t_data *data)
{
	write(0, "~$ ", 3);
	while (data->exit == 0 && get_next_line(0, &data->input) > 0)
	{
		/* commande de parsing a inserer ici */
		ft_parse_input(data);
		printf("AFTER PARSING\n");
		/* commande d'execusion des tokens a inserer ici */
		if ((data->exit == 0) && (data->token != NULL))
			ft_read_token_list(data);
			// ft_while_token(data);
		printf("AFTER READ TOKEN\n");

			/*	test avec echo	*/
		// printf("pre delete tok\n");
		// ft_delete_token(data, data->token);

			/*	commande de reset de data	*/
		// printf("pre clear input\n");
		ft_clear_for_new_input(data);
		// printf("pre new line\n");
		if (data->exit == 0)
			write(0, "~$ ", 3);
		else
			ft_putstr("exit\n");
	}
	write(0, "ex\n", 3);


}

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

	init_signals();
	signal(SIGTSTP, handler);

	printf("Bienvenue dans ce minishell realisé par guderram et mourdani\n");
	data = malloc(sizeof(t_data));
	if (ft_init_data(data, env) == 0)
		return (0); // erreur
	// while (data->exit == 0 && ft_verif_pipe(data->pipe) == 1)
	prompt(data);
	/*	fonction qui clear tout a faire	*/
	
	/*	tests free : 	*/
	unlink(TMP_OUT);
	unlink(TMP_IN);
	return (0);
}
