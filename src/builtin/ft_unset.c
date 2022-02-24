/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:12:33 by guderram          #+#    #+#             */
/*   Updated: 2022/02/24 02:38:31 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_unset(t_data *data, t_token *token) // fonction principale de unset
{
	t_var	*var;

	var = ft_found_var_name(data, token->arg);
	// printf("var name '%s' : var value '%s'\n", var->name, var->value);
	if (var != NULL)
		ft_delete_var(data, var);
}
