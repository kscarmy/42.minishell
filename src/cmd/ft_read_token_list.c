/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:17 by guderram          #+#    #+#             */
/*   Updated: 2022/02/19 10:10:29 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_while_token(t_data *data) // lecture des tokens
{
	int	i;

	i = 0;

	while (i < 5 && data->exit == 0 && data->first != NULL) // A SUPP : i garde fou
		i++;

	/*	faire des tests unitaires :		*/
	if (data->first->cmd == 1) // pour echo
		ft_echo(data, data->first);
	else if (data->first->cmd == 2) // pour pwd
		ft_pwd(data, data->first);
	else if (data->first->cmd == 3) // pour export
		printf("\n'%s'\n", data->first->str);
	else if (data->first->cmd == 4) // pour env
	{
		i = 0;
		while(data->env[i])
			printf("%s\n", data->env[i++]);
	}
	else if (data->first->cmd == 5) // pour history
		add_history(NULL, 2);	// shows history with param == 2; adds to history with param == 1;
	else if (data->first->cmd == 6)
		change_dir("src/parsing");	// fill inside with path of directory to enter. 
	return (0);
}
