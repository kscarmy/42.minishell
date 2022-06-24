/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:16:44 by guderram          #+#    #+#             */
/*   Updated: 2022/06/24 12:46:43 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	ft_cut_echo(t_data *data, int i)
// {
// 	if (ft_strncmp(&data->input[i], "echo", 4) != 0)
// 		return (0);
// 	i = i + 4;
// 	if (ft_str_after_cut(&data->input[i]) != 1)
// 		return (0);
// 	ft_cut_echo_option(data, i);
// 	return (1);
// }

int	ft_cut_echo(t_data *data, char *str)
{
	char	*arg;

	arg = "echo";
	if (ft_str_size(str) != ft_str_size(arg))
		return (0);
	if (ft_strncmp(str, arg, ft_str_size(arg)) != 0)
		return (0);
	ft_create_echo_token(data);
	return (1);
}

// void	ft_cut_echo_option(t_data *data, int i)
// {
// 	char	*str;
// 	int		u;

// 	str = "-n";
// 	u = 0;
// 	i = i + ft_space(data->input, i);
// 	if (ft_is_a_b(data->input[i], str[0]) == 1)
// 		u++;
// 	while (ft_is_a_b(data->input[i + u], str[1]) == 1)
// 		u++;
// 	if (u >= 2 && (data->input[i + u] == '\0'
// 			|| data->input[i + u] == '\'' || data->input[i + u] == '\"'
// 			|| data->input[i + u] == ' '))
// 		i = i + u;
// 	else
// 		u = 0;
// 	i = i + ft_space(data->input, i);
// 	data->i = i;
// 	ft_create_echo_token(data, u);
// }

void	ft_create_echo_token(t_data *data)
{
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 1;
	// if (option >= 2)
	// 	data->token->option = 1;
	ft_malloc_builtin_arg(data, data->token);
}
