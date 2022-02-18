/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:35:31 by guderram          #+#    #+#             */
/*   Updated: 2022/02/18 07:51:18 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_data *data, t_token *token) // commande echo
{
	/*	sortie sur l'entree standard	*/
	ft_putstr(token->str);
	if (token->option != 1)
		ft_putstr("\n");
	data->i = data->i;
	// ft_delete_token(data, token); // SEG FAULT
}
