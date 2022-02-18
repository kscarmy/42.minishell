/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 03:42:50 by guderram          #+#    #+#             */
/*   Updated: 2022/02/18 07:32:02 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_check_quote(t_data *data) // verif des quotes
{
	int	i;
	int squote;
	int	dquote;

	i = data->i;
	dquote = 0;
	squote = 0;
	
	while (data->input[i] && ft_is_separator(data->input, i))
	{
		if (data->input[i] == 34) // 34 = "
			dquote++;
		if (data->input[i] == 39) // 39 == '
			squote++;
		i++;
	}
	// if (dquote )
}
