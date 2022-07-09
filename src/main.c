/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:35:54 by guderram          #+#    #+#             */
/*   Updated: 2022/07/06 09:45:27 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_return;

int	ft_verif_pipe(t_pipe *p)
{
	if (p->fd_i == -10 && p->fd_o == -10 && p->ofd_i == -10 && p->ofd_o == -10)
		return (1);
	else
		return (0);
}

void	prompt(t_data *data)
{
	while (g_return != -1234 && data->exit == 0)
	{
		data->err = 0;
		data->i = 0;
		if (g_return >= 0)
			data->input = readline("~$ ");
		if (data->input == NULL)
			return ;
		if (g_return >= 0 && data->input != NULL
			&& ft_str_size(data->input) > 0)
			add_history(data->input);
		if (ft_is_input_safe(data->input) == 0)
			data->err = 1;
		else if (g_return >= 0)
			ft_parse_input(data);
		if (g_return >= 0 && data->err == 0
			&& data->exit == 0 && data->token != NULL)
			ft_read_token_list(data);
		ft_clear_for_new_input(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	argc = 0;
	argv = NULL;
	(void)argc;
	(void)argv;
	g_return = 0;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	ft_putstr("Bienvenue dans ce minishell realisé par guderram et mourdani\n");
	data = malloc(sizeof(t_data));
	if (ft_init_data(data, env) == 0)
		return (0);
	prompt(data);
	ft_putstr("exit\n");
	unlink(TMP_OUT);
	unlink(TMP_IN);
	ft_free_minishell(data);
	free(data);
	data = NULL;
	rl_clear_history();
	return (ft_resize_g_return(g_return));
}
