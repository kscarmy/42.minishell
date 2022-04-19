/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:02:35 by guderram          #+#    #+#             */
/*   Updated: 2022/04/19 18:19:18 by guderram         ###   ########.fr       */
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
	if (data->var != NULL)
		var = data->var;
	else
		return (NULL);
	if (i == 0)
		return (NULL);
	while (var != NULL)
	{

		if (ft_strncmp(var->name, str, i) == 0)
		{
			if(var->name[i] == '\0')
			{
				// printf("found var name str '%s' str[i] '%c' var '%s'\n", str, str[i], var->name);
				return (var);
			}
		}
		var = var->next;
	}
	return (var);
}

void	ft_disp_all_var(t_data *data, char sep, int export) // permet d'afficher toutes les variables stockees avec en option un separateur entre nom et value, si export vaut 1 alors considere que la commande export a ete lancee sans arguments
{
	t_var	*var;
	
	var = data->var;
	while (var != NULL)
	{
		if (export == 1)
			ft_putstr("declare -x ");
		ft_putstr(var->name);
		ft_putchar(sep);
		if (export == 1)
			ft_putchar('"');
		ft_putstr(var->value);
		if (export == 1)
			ft_putchar('"');
		if (var->next != NULL)
			ft_putchar('\n');
		var = var->next;
	}
}
