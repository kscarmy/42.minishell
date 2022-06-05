/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 06:59:21 by mourdani          #+#    #+#             */
/*   Updated: 2022/06/05 16:29:25 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_exit(t_data *data) // ret 1 si exti trouver, sinon ret 0
{
	char *command;
	int i;

	i = data->i;
	command = "exit";
	while (ft_is_whitespace(data->input[i]))
		i++;
	if (ft_strncmp((data->input + i), command, 4) == 0)
	{
		data->i = data->i + 4;
		ft_create_exit_token(data);
		// data->exit = 1;
		// data->i = data->i + 4;
		return(1);
	}
	return (0);
}

void	ft_create_exit_token(t_data *data) // cree le token de la commande pwd
{
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 7; // valeur de la commande de sortie
	ft_malloc_builtin_arg(data, data->token);
	// printf("cut exit : tok arg <%s>\n", data->token->arg);
}
