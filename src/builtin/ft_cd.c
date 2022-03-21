/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:47:58 by guderram          #+#    #+#             */
/*   Updated: 2022/03/21 21:41:23 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cd(t_data *data, t_token *token)                 // changes directory
{
	if (data->token->arg == NULL || !ft_strncmp(data->token->arg, "~\0", 2))
	{
		chdir(getenv("HOME"));
		if (data->pwd)
		{
			free(data->pwd);
			data->pwd = NULL;
		}
		data->pwd = getcwd(NULL, 0);
		return (1);
	}
	if (chdir(data->token->arg) < 0)
		perror(data->token->arg);        // printf error message
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	data->pwd = getcwd(NULL, 0);
	return (1); //ok
}
