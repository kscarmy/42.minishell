/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 06:59:21 by mourdani          #+#    #+#             */
/*   Updated: 2022/06/24 12:32:56 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	ft_cut_exit(t_data *data)
// {
// 	int	i;

// 	i = data->i;
// 	while (ft_is_whitespace(data->input[i]))
// 		i++;
// 	if (ft_strncmp(&data->input[i], "exit", 4) != 0)
// 		return (0);
// 	i = i + 4;
// 	if (ft_str_after_cut(&data->input[i]) != 1)
// 		return (0);
// 	data->i = i;
// 	ft_create_exit_token(data);
// 	return (1);
// }


int	ft_cut_exit(t_data *data, char *str)
{
	char	*arg;

	arg = "exit";
	if (ft_str_size(str) != ft_str_size(arg))
		return (0);
	if (ft_strncmp(str, arg, ft_str_size(arg)) != 0)
		return (0);
	ft_create_exit_token(data);
	return (1);
}

void	ft_create_exit_token(t_data *data)
{
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 7;
	ft_malloc_builtin_arg(data, data->token);
}
