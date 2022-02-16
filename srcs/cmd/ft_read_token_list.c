/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:17 by guderram          #+#    #+#             */
/*   Updated: 2022/02/16 12:05:22 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_while_token(t_data *data) // lecture des tokens
{
	int	i;
	
	i = 0;
	while (i < 5 && data->exit == 0 && data->first != NULL) // A SUPP : i garde fou
	{
		i++;
	}
	printf("\ncmd : %d\noption : %d\nstr :'%s'\n", data->first->cmd, data->first->option, data->first->str);
	return (0);
}
