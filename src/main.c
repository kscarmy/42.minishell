/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:35:54 by guderram          #+#    #+#             */
/*   Updated: 2022/05/31 19:15:30 by guderram         ###   ########.fr       */
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
	int	i = 0;
	// char *line;
	// write(0, "~$ ", 3);
	
	/*	TEST	*/
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGSEGV, handler);

	printf("1 %d 2 %d 3 %d 4 %d\n", SIGINT, SIGQUIT, SIGSEGV, EOF);
	/*	TEST	*/
	g_return = 0;
	while (data->exit == 0)
	{
		/*	readline	*/
		i = 0;
		data->input = readline("~$ ");
		if (g_return >= 0 && ft_str_size(data->input) > 0)
		{
			add_history(data->input);
			if (ft_is_input_safe(data->input) == 0)
				data->err = 1;
			else
				ft_parse_input(data);
			if (data->err == 0 && data->exit == 0 && data->token != NULL)
				ft_read_token_list(data);
		}
		else if (g_return == -13)
			g_return = 2;
		else if (data->input == NULL)
		{
			// printf("DATA INPUT NULL !\n");
			ft_putchar_fd('\n', 1);
			g_return = -113;
		}


		// while (data->input[i]) { i++; }
		// printf("sizeof input %d\n", i);
		/*	commande de parsing a inserer ici */
		// if (ft_is_input_safe(data->input) == 0)
		// 	data->err = 1;
		// else
		// 	ft_parse_input(data);

		// printf("err : %d\n", data->err);
		/* commande d'execusion des tokens a inserer ici */
		
		// if (data->err == 0 && data->exit == 0 && data->token != NULL)
		// 	ft_read_token_list(data);



			// ft_while_token(data);
		// printf("AFTER READ TOKEN\n");

			/*	test avec echo	*/
		// printf("pre delete tok\n");
		// ft_delete_token(data, data->token);

			/*	commande de reset de data	*/
		// printf("pre clear input\n");
		// printf("sizeof data->i %d\n", data->i);
		ft_clear_for_new_input(data);
		if (g_return == -113)
			data->exit = 1;
		// printf("fin du clear pour input\n");
		if (data->exit != 0)
			ft_putstr("exit\n");
	}
	// write(0, "ex\n", 3);


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

	// init_signals();
	// signal(SIGTSTP, handler);

	printf("Bienvenue dans ce minishell realisé par guderram et mourdani\n");
	data = malloc(sizeof(t_data));
	// printf("OK 1\n");
	if (ft_init_data(data, env) == 0)
		return (0); // erreur
	// while (data->exit == 0 && ft_verif_pipe(data->pipe) == 1)
	// printf("OK 2\n");
	prompt(data);
	// printf("OK 3\n");
	/*	fonction qui clear tout a faire	*/
	
	/*	tests free : 	*/
	unlink(TMP_OUT);
	unlink(TMP_IN);
	return (g_return);
}
