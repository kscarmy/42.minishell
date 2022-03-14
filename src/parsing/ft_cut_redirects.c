/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:58:24 by guderram          #+#    #+#             */
/*   Updated: 2022/03/12 04:03:48 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cut_redirects(t_data *data) // ret 1 si une redirection est trouvee, sinon ret 0
{
	int i;

	i = 0;
//	printf("is redir\n");
	while (ft_is_whitespace(data->input[i]))
		i++;
	if (ft_is_separator(data->input, i) != 0)
	{
		ft_create_redirects_token(data, ft_is_separator(data->input, i));
		if (ft_is_separator(data->input, i) > 4)
			data->i = data->i + i + 2;
		else
			data->i = data->i + i + 1;
		printf("redir ok\n");
		return (1);
	}	
	return (0);
}

void	cut_cmd_redir(t_data *data, int i)
{
	char **cmd;

	(void)i;
		cmd = ft_split(data->input, '>');
		data->token->bin[0] = cmd[0];
		data->token->bin[1] = cmd[1];
}

void	ft_create_redirects_token(t_data *data, int i) // cree le token de la commande redirect
{
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->sep = i; // valeur de la commande de sortie
	cut_cmd_redir(data, i);		
	printf("data->token->bin[0] = %s\n", data->token->bin[0]);
	printf("data->token->bin[1] = %s\n", data->token->bin[1]);
}
