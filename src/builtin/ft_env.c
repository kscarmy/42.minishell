/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:11:48 by guderram          #+#    #+#             */
/*   Updated: 2022/02/24 07:36:10 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_data *data, t_token *token) // commande env
{
	
	// token->str = getenv(NULL);
	// if (token->str == NULL)
	// 	data->err = 106;
	/*	sortie sur l'entree standard	*/
	// ft_putstr(token->str);
	// ft_putstr("\n");
	// data->i = data->i;
	token->cmd = token->cmd;
	ft_disp_all_var(data, '=');
	ft_putstr("\n");
	data->i = data->i;
}
