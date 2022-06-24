/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:04:56 by guderram          #+#    #+#             */
/*   Updated: 2022/06/24 12:22:38 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	ft_cut_unset(t_data *data, int i)
// {
// 	char	*str;
// 	int		u;

// 	u = 0;
// 	str = "unset";
// 	i = i + ft_space(data->input, i);
// 	while (data->input[i] && data->input[i] != ' '
// 		&& ft_is_separator(data->input, i) == 0)
// 	{
// 		if (ft_is_a_b(data->input[i], str[u]) == 1)
// 			u++;
// 		i++;
// 	}
// 	if (u == 5)
// 	{
// 		data->i = data->i + 5;
// 		ft_create_unset_token(data);
// 		return (1);
// 	}
// 	return (0);
// }

int	ft_cut_unset(t_data *data, char *str)
{
	char	*arg;

	arg = "unset";
	// printf("ft_cut_unset : str %d arg %d\n", ft_str_size(str), ft_str_size(arg));
	if (ft_str_size(str) != ft_str_size(arg))
		return (0);
	if (ft_strncmp(str, arg, ft_str_size(arg)) != 0)
		return (0);
	// printf("ft_cut_unset : ok\n");
	ft_create_unset_token(data);
	return (1);
}

void	ft_create_unset_token(t_data *data)
{
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 8;
	// printf("ft_create_unset_token : data i %d\n", data->i);
	ft_malloc_builtin_arg(data, data->token);
}
