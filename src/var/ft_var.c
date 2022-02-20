/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:02:35 by guderram          #+#    #+#             */
/*   Updated: 2022/02/20 22:16:01 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_var	*ft_found_var_name(t_data *data, char *str) // permet de trouver et de renvoyer l'adresse de la var qui contient la string "str" dans name. si rien n'est trouver renvoie "NULL"
{
	t_var	*var;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (data->var != 0)
		var = data->var;
	else
		return (NULL);
	while (var != NULL)
	{
		if (ft_strncmp(var->name, str, i) == 0)
			return (var);
		else
			var = var->next;
	}
	return (var);
}

