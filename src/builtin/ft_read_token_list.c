/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:17 by guderram          #+#    #+#             */
/*   Updated: 2022/04/16 20:29:54 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_ret_last_token(t_data *data) // renvoie l'adresse du dernier token.
{
	t_token	*token;

	token = data->token;
	while (token->next != NULL)
		token = token->next;
	return (token);
}


void	ft_launch_cmd(t_data *data, t_token *token) // lance une cmd
{
	// printf("pipe : %d %d\n", data->pipe->fd_i, data->pipe->fd_o);
	if (token->prev != NULL && token->prev->sep == 2) // si le prochain token a un sep
		{
			printf("in pipe out\n");
			ft_pipe_out(data);
		}
	if (token->next != NULL && token->next->sep == 2) // si le precedent token a un sep
		ft_pipe_in(data);
	// printf("launch cmd\n");
	if (token->cmd == 1) // pour echo
		ft_echo(data, token);
	if (token->cmd == 2) // pour pwd
		ft_pwd(data);
	if (token->cmd == 3) // pour export
		ft_export(data, token);
	if (token->cmd == 4) // pour env
		ft_env(data, token);
	// if (token->cmd == 5) // pour history
	// 	add_history(NULL, 2);	// shows history with param == 2; adds to history with param == 1;
	if (token->cmd == 6)
		ft_cd(data, token);	// fill inside with path of directory to enter.
	if (token->cmd == 7) // pour exit
		data->exit = 1; // enclanche la sortie
	if (token->cmd == 8) // pour unset
		ft_unset(data, token);
	if (token->cmd == 9) // pour bin
		ft_is_bin(data, token);
	ft_pipe_close_data_fd(data, 3);
}

t_token		*ft_read_token_list_while_pipe(t_data *data, t_token *t) // lecture des tokens dans les pipes
{
	pid_t		pid;
	// int			status;

	pid = fork();
	while (t != NULL && (t->sep == 2 || (t->prev != NULL && t->prev->sep == 2) || (t->next != NULL && t->next->sep == 2)))
	{
		
		if(t->cmd != -1)
			ft_launch_cmd(data, t);
		if (t->prev != NULL)
			t = t->prev;
		else
			t = NULL;
		
	}
	printf("PTN DE PID 2 : %d, %d\n", getpid(), pid);
	waitpid(pid, 0, 0);
	// kill(pid, SIGKILL);
	printf("sortie du fork?\n");
	return (t);
}

void	ft_read_token_list(t_data *data) // lecture des tokens
{
	t_token *t;

	ft_print_token_list(data);
	t = ft_ret_last_token(data);
	printf("PTN DE PID: %d\n", getpid());
	while (data->exit == 0 && t != NULL)
	{
		if (t->prev != NULL && t->prev->sep == 2)
		{
			printf("PREMIER\n");
			t = ft_read_token_list_while_pipe(data, t);
		}
		else
		{
			printf("SECOND\n");
			if (t != NULL && t->cmd != -1)
			{
				ft_launch_cmd(data, t);
				printf("statu de exit : %d\n", data->exit);
			}
		}
		if (t != NULL && t->prev != NULL)
			t = t->prev;
		else
			t = NULL;
	}
}



void	ft_print_token_list(t_data *data) // affiche tout les token
{
	t_token *token;
	int		i;

	token = data->token;
	i = 0;
	while (token != NULL)
	{
		printf("-------------------------------\n");
		printf("cmd %d sep %d", token->cmd, token->sep);
		if (token->arg != NULL)
			printf(" arg '%s'", token->arg);
		while (token->bin != NULL && token->bin[i])
		{
			printf(" '%s'", token->bin[i]);
			i++;
		}
		printf("\n");
		token = token->next;
	}
	printf("-------------------------------\n");
}



// int		ft_while_token(t_data *data) // lecture des tokens
// {
// 	int	i;

// 	i = 0;

// 	while (i < 5 && data->exit == 0 && data->token != NULL) // A SUPP : i garde fou
// 		i++;

// 	// printf("TEST 1\n");
// 	/*	faire des tests unitaires :		*/
// 	if (data->token->cmd == 1) // pour echo
// 		ft_echo(data, data->token);
// 	if (data->token->cmd == 2) // pour pwd
// 		ft_pwd(data, data->token);
// 	if (data->token->cmd == 3) // pour export
// 	{
// 		printf("\n'%s'\n", data->token->arg);
// 		ft_export(data, data->token);
// 	}
// 	// printf("TEST 2\n");

// 	// printf("TEST 3\n");
// 	if (data->token->cmd == 4) // pour env
// 		ft_env(data, data->token);
// 	// printf("TEST 4\n");
// 	if (data->token->cmd == 5) // pour history
// 		add_history(NULL, 2);	// shows history with param == 2; adds to history with param == 1;
// 	// printf("TEST 5\n");
// 	if (data->token->cmd == 6)
// 		change_dir(data);	// fill inside with path of directory to enter.

// 	if (data->token->cmd == 7) // pour exit
// 		data->exit = 1; // enclanche la sortie
// 	// printf("TEST 6\n");
// 	if (data->token->cmd == 8) // pour unset
// 	{
// 		// printf("\n'%s'\n", data->token->arg);
// 		ft_unset(data, data->token);
// 	}
// 	if (data->token->cmd == 9) // pour bin
// 	{
// 		// printf("bin : '%s'\narg : '%s'\n", data->token->bin[0], data->token->bin[1]);
// 		ft_is_bin(data, data->token);
// 		// ft_test(data);
// 	}
// 	if (data->token->sep > 0)
// 		printf("token sep : %d\n", data->token->sep);
// 	return (0);
// }
