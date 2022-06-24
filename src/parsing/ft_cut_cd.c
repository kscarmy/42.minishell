/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:59:30 by mourdani          #+#    #+#             */
/*   Updated: 2022/06/24 12:31:14 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_dir(t_data *data)
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
		perror(data->token->arg);
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	data->pwd = getcwd(NULL, 0);
	return (1);
}

// int	ft_cut_cd(t_data *data, int i)
// {
// 	if (ft_strncmp(&data->input[i], "cd", 2) != 0)
// 		return (0);
// 	i = i + 2;
// 	if (ft_str_after_cut(&data->input[i]) != 1)
// 		return (0);
// 	i = i + ft_space(data->input, i);
// 	data->i = i;
// 	ft_create_cd_token(data);
// 	return (1);
// }

int	ft_cut_cd(t_data *data, char *str)
{
	char	*arg;

	arg = "cd";
	if (ft_str_size(str) != ft_str_size(arg))
		return (0);
	if (ft_strncmp(str, arg, ft_str_size(arg)) != 0)
		return (0);
	ft_create_cd_token(data);
	return (1);
}

void	ft_create_cd_token(t_data *data)
{
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 6;
	ft_malloc_builtin_arg(data, data->token);
}
