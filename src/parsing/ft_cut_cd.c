/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:59:30 by mourdani          #+#    #+#             */
/*   Updated: 2022/02/24 16:29:10 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_dir(t_data *data)                 // changes directory
{
	if (chdir(data->token->arg) < 0)
		perror(data->token->arg);        // printf error message
	return (1); //ok
}

int	ft_cut_cd(t_data *data) // ret 1 si cd est trouvé, sinon ret 0
{
	char *command;
	int i;

	i = 0;
	command = "cd";
	while (ft_is_whitespace(data->input[i]))
		i++;
	if (ft_strncmp((data->input + i), command, 2) == 0)
	{
		data->i = i + 3;
		if (data->input[data->i - 1] != ' ')
			return (0);
		ft_create_cd_token(data);
		return(1);
	}
	return (0);
}

void	ft_create_cd_token(t_data *data) // cree le token de la commande cd.
{
	int	u;

	u = 0;
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 6;
	while (ft_is_separator(data->input, (data->i + u)) == 0 && data->input[data->i + u])
		u++;
	data->token->arg = ft_malloc_str(data, u);
	if (data->token->arg != NULL)
	{
		data->token->arg = ft_strncpy(data->token->arg, &(data->input[data->i]), u);
		data->token->arg = cut_str(data, data->token->arg);
	}
	else
		data->err = 200; // erreur malloc
}
