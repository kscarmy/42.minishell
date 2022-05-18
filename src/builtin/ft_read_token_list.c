/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:17 by guderram          #+#    #+#             */
/*   Updated: 2022/05/18 22:15:15 by mourdani         ###   ########.fr       */
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
	// if (token->prev != NULL && token->prev->sep == 2) // si le prochain token a un sep
	// 	{
	// 		printf("in pipe out\n");
	// 		ft_pipe_out(data);
	// 	}
	// if (token->next != NULL && token->next->sep == 2) // si le precedent token a un sep
	// 	ft_pipe_in(data);
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
	while (t != NULL && (t->sep == 2 || (t->prev != NULL && t->prev->sep == 2) || (t->next != NULL && t->next->sep == 2)))
	{
		
		if(t->cmd != -1)
			ft_launch_cmd(data, t);
		if (t->prev != NULL)
			t = t->prev;
		else
			t = NULL;
		
	}
	return (t);
}

void	ft_read_token_list(t_data *data) // lecture des tokens
{
	t_token *last_token;

//	ft_print_token_list(data);
	last_token = ft_ret_last_token(data);
	while (data->exit == 0 && last_token != NULL)
	{
		if (last_token->prev != NULL && last_token->prev->sep == 2)
		{
			// printf("PREMIER\n");
			last_token = ft_read_token_list_while_pipe(data, last_token);
		}
		else
		{
			// printf("SECOND\n");
			if (last_token != NULL && last_token->cmd != -1)
			{
				ft_launch_cmd(data, last_token);
				// printf("statu de exit : %d\n", data->exit);
			}
		}
		if (last_token != NULL && last_token->prev != NULL)
			last_token = last_token->prev;
		else
			last_token = NULL;
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
		if (token->arg != NULL)
		while (token->bin != NULL && token->bin[i])
		{
			printf(" '%s'", token->bin[i]);
			i++;
		}
		token = token->next;
	}
}
