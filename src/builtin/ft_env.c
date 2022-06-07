/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:11:48 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 22:43:46 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_data *data, t_token *token)
{
	token->cmd = token->cmd;
	ft_disp_all_var(data, '=', 0);
	ft_putstr("\n");
	data->i = data->i;
}
