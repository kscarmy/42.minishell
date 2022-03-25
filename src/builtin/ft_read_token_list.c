/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:17 by guderram          #+#    #+#             */
/*   Updated: 2022/03/24 07:32:53 by guderram         ###   ########.fr       */
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
	// printf("launch cmd\n");
	if (token->cmd == 1) // pour echo
		ft_echo(data, token);
	if (token->cmd == 2) // pour pwd
		ft_pwd(data);
	if (token->cmd == 3) // pour export
		ft_export(data, token);
	if (token->cmd == 4) // pour env
		ft_env(data, token);
	if (token->cmd == 5) // pour history
		add_history(NULL, 2);	// shows history with param == 2; adds to history with param == 1;
	if (token->cmd == 6)
		ft_cd(data, token);	// fill inside with path of directory to enter.
	if (token->cmd == 7) // pour exit
		data->exit = 1; // enclanche la sortie
	if (token->cmd == 8) // pour unset
		ft_unset(data, token);
	if (token->cmd == 9) // pour bin
		ft_is_bin(data, token);
}


void	ft_read_token_list(t_data *data) // lecture des tokens
{
	t_token *token;

	// printf("pre Token\n");
	ft_print_token_list(data);
	token = ft_ret_last_token(data);
	// printf("Token  : %d, '%s'\n", token->cmd, token->arg);
	while (data->exit == 0 && token != NULL)
	{
		// printf("in while Token\n");
		if (token->prev != NULL && token->prev->sep != -1)
			printf("un sep est detecter\n");
		if (token->cmd != -1)
		{
			// printf("go cmd\n");
			ft_launch_cmd(data, token);
		}
		if (token->prev != NULL)
			token = token->prev;
		else
			token = NULL;
		// printf("end tok\n");
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
