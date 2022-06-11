/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_token_list_bis_bis.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:00:49 by guderram          #+#    #+#             */
/*   Updated: 2022/06/11 15:03:50 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_read_token_list_cat_while(t_token *t)
{
	if (t->bin != NULL && t->bin[0] != NULL
		&& ft_strncmp(t->bin[0], "cat", 3) == 0 && t->bin[1] == NULL)
	{
		if (t->prev != NULL && t->prev->sep == 2 && t->prev->prev != NULL)
			return (1);
	}
	return (0);
}

t_token	*ft_read_token_list_cat(t_data *data, t_token *tok)
{
	t_token	*t;
	char	*tmp;

	t = tok;
	data->cat = 0;
	while (ft_read_token_list_cat_while(t) == 1)
	{
		data->cat = data->cat + 1;
		t = t->prev->prev;
	}
	if (t->prev == NULL && data->cat > 0)
	{
		ft_launch_cmd(data, t);
		while (data->cat > 0)
		{
			tmp = readline("");
			ft_strdel(&tmp);
			data->cat = data->cat - 1;
		}
		return (NULL);
	}
	return (tok);
}
