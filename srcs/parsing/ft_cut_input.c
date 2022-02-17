/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:50 by guderram          #+#    #+#             */
/*   Updated: 2022/02/17 19:13:37 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parse_input(t_data *data) // return 0 si ok, sinon 1 ou numero specifique a l'erreur
{
	int	found;
	
	found = 0;
	while (data->input[data->i])
	{
		ft_space(data->input, data->i);
		if (ft_cut_echo(data, data->i) == 1)
			found++;
		data->i = data->i + 1;
	}
	if (found == 0)
	{
		data->exit = 1;
		ft_putstr("ERREUR\n");
		return (1); // pas de commande trouvee
	}
	return (0);
}
