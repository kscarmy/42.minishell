/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:54:31 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 14:10:43 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_clear_token_list(t_data *data)
{
	while (data->token != NULL)
		ft_delete_token(data, data->token);
}

void	ft_clear_for_new_input(t_data *data)
{
	ft_clear_token_list(data);
	ft_pipe_close_data_fd(data, 3);
	data->i = 0;
	ft_strdel(&data->input);
}
