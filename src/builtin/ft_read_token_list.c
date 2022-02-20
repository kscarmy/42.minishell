/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:17 by guderram          #+#    #+#             */
/*   Updated: 2022/02/20 17:45:16 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_while_token(t_data *data) // lecture des tokens
{
	int	i;

	i = 0;

	while (i < 5 && data->exit == 0 && data->token != NULL) // A SUPP : i garde fou
		i++;

	/*	faire des tests unitaires :		*/
	if (data->token->cmd == 1) // pour echo
		ft_echo(data, data->token);
	if (data->token->cmd == 2) // pour pwd
		ft_pwd(data, data->token);
	if (data->token->cmd == 3) // pour export
		printf("\n'%s'\n", data->token->str);

	if (data->token->cmd == 4) // pour env
	{
		i = 0;
		while(data->env[i])
			printf("%s\n", data->env[i++]);
	}
	if (data->token->cmd == 5) // pour history
		add_history(NULL, 2);	// shows history with param == 2; adds to history with param == 1;
	if (data->token->cmd == 6)
		change_dir("src/parsing");	// fill inside with path of directory to enter.
	if (data->token->cmd == 7) // pour exit
		data->exit = 1; // enclanche la sortie
	return (0);
}
