/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_arg_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:28:19 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 13:36:55 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_malloc_arg_bbbb(t_data *data, t_token *tok, int *u, int *i)
{
	*i = 0;
	while (tok->arg[*i] && tok->arg[*i] != '\0')
		*i = *i + 1;
	tok->arg[*i] = data->input[data->i + *u];
	if (data->input[data->i + *u] == ' ')
		*u = *u + ft_space(data->input, data->i + *u);
	else
		*u = *u + 1;
}

void	ft_malloc_arg_end(t_data *data, int *u, int *size)
{
	if (*size == 0 && data->input[data->i + *u] == '\"')
	{
		*u = *u + 1;
		while (data->input[data->i + *u]
			&& data->input[data->i + *u] != '\"')
			*u = *u + 1;
		if (data->input[data->i + *u] == '\"')
			*u = *u + 1;
		data->i = data->i + *u;
	}
	else if (*size == 0)
		data->err = 200;
}

char	*ft_one_simple_arg(t_data *data, int i)
{
	char	*ret;
	int		j;

	j = 0;
	while (data->input[i + j] && data->input[i + j] != ' '
		&& ft_is_separator(data->input, i + j) == 0
		&& data->input[i + j] != '\'' && data->input[i + j] != '\"'
		&& data->input[i + j] != '$')
		j++;
	ret = ft_malloc_str(data, j);
	j = 0;
	while (data->input[i + j] && data->input[i + j] != ' '
		&& ft_is_separator(data->input, i + j) == 0
		&& data->input[i + j] != '\'' && data->input[i + j] != '\"'
		&& data->input[i + j] != '$')
	{
		ret [j] = data->input[i + j];
		j++;
	}
	ret [j] = '\0';
	return (ret);
}
