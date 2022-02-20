/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 07:26:19 by guderram          #+#    #+#             */
/*   Updated: 2022/02/20 23:54:09 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(t_data *data, t_token *token) // commande pwd
{
		// token->str = getenv("PWD");
	// if (token->str == NULL)
	// 	data->err = 106;
	/*	sortie sur l'entree standard	*/
	// ft_putstr(token->str);
	// ft_putstr("\n");
	token->cmd = token->cmd;
	ft_disp_all_var(data, '=');
	ft_putstr("\n");
	data->i = data->i;
}
