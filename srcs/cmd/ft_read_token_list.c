/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:17 by guderram          #+#    #+#             */
/*   Updated: 2022/02/18 11:10:56 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_while_token(t_data *data) // lecture des tokens
{
	int	i;
	
	i = 0;
	while (i < 5 && data->exit == 0 && data->first != NULL) // A SUPP : i garde fou
	{
		i++;
	}

	/*	faire des tests unitaires :		*/
	if (data->first->cmd == 1) // pour echo
	{
		ft_echo(data, data->first);
	}
	if (data->first->cmd == 2) // pour pwd
	{
		ft_pwd(data, data->first);
	}
	if (data->first->cmd == 3) // pour export
	{
		printf("\n'%s'\n", data->first->str);
	}
	
	return (0);
}
