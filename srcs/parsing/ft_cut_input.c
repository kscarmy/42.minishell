/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:50 by guderram          #+#    #+#             */
/*   Updated: 2022/02/16 10:37:14 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parse_input(t_data *data) // return 0 si ok, sinon 1 ou numero specifique a l'erreur
{
	int	i;
	int	found;
	
	i = 0;
	found = 0;
	while (data->input[i])
	{
		ft_space(data->input, i);
		if (ft_cut_echo(data, i) == 1)
			found++;
		i++;
	}
	if (found == 0)
	{
		ft_putstr("ERREUR\n");
		return (1); // pas de commande trouvee
	}
	return (0);
}