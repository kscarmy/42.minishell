/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:17 by guderram          #+#    #+#             */
/*   Updated: 2022/02/24 07:37:04 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_while_token(t_data *data) // lecture des tokens
{
	int	i;

	i = 0;

	while (i < 5 && data->exit == 0 && data->token != NULL) // A SUPP : i garde fou
		i++;

	// printf("TEST 1\n");
	/*	faire des tests unitaires :		*/
	if (data->token->cmd == 1) // pour echo
		ft_echo(data, data->token);
	if (data->token->cmd == 2) // pour pwd
		ft_pwd(data, data->token);
	if (data->token->cmd == 3) // pour export
		printf("\n'%s'\n", data->token->arg);
	// printf("TEST 2\n");

	// printf("TEST 3\n");
	if (data->token->cmd == 4) // pour env
		ft_env(data, data->token);
	// printf("TEST 4\n");
	if (data->token->cmd == 5) // pour history
		add_history(NULL, 2);	// shows history with param == 2; adds to history with param == 1;
	// printf("TEST 5\n");
	if (data->token->cmd == 6)
		change_dir("src/parsing");	// fill inside with path of directory to enter.

	if (data->token->cmd == 7) // pour exit
		data->exit = 1; // enclanche la sortie
	// printf("TEST 6\n");
	if (data->token->cmd == 8) // pour unset
	{
		printf("\n'%s'\n", data->token->arg);
		ft_unset(data, data->token);
	}
	if (data->token->cmd == 9) // pour bin
	{
		// printf("bin : '%s'\narg : '%s'\n", data->token->bin[0], data->token->bin[1]);
		ft_is_bin(data, data->token);
		// ft_test(data);
	}
	return (0);
}
