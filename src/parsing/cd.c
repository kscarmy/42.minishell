/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:59:30 by mourdani          #+#    #+#             */
/*   Updated: 2022/02/19 10:10:13 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_dir(char *path)
{
	if (chdir(path) < 0)
		perror("chdir() error");
//	if (closedir(dir) == -1)
//		perror("closedir");
	return (1); //ok
}

int	cut_cd(t_data *data)
{
	char *command;
	int i;

	i = 0;
	command = "cd";
	while (ft_is_whitespace(data->input[i]))
		i++;
	if (ft_strncmp((data->input + i), command, 2) == 0)
	{
		ft_create_cd_token(data);
		return(1);
	}
	return (0);
}

void	ft_create_cd_token(t_data *data) // cree le token de la commande cd.
{
	if (data->first == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->first->cmd = 6;
}
