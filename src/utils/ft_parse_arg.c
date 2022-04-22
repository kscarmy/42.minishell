/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:28:56 by guderram          #+#    #+#             */
/*   Updated: 2022/04/22 05:45:19 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_size_of_arg(t_data *data) // renvoie la taille d'un arg, pratique pour malloc tok->arg
{
	int	u;
	// int i = 0;

	u = 0;
	while (ft_is_separator(data->input, (data->i + u)) == 0 && data->input[data->i + u])
	{
		// printf ("u 1 %d\n", u);
		if (data->input[data->i + u] == '\"' && data->input[data->i + u + 1] != '\"' && data->input[data->i + u + 1] != '\0')
			u = u + ft_str_size(ft_ret_double_quote(data, &data->input[data->i + u], 0));
		else if (data->input[data->i + u] == '\'' && data->input[data->i + u + 1] != '\'' && data->input[data->i + u + 1] != '\0')
			u = u + ft_str_size(ft_ret_simple_quote(data, &data->input[data->i + u], 0));
		else if ((data->input[data->i + u] == '\"' && data->input[data->i + u + 1] == '\"') || (data->input[data->i + u] == '\'' && data->input[data->i + u + 1] == '\''))
			{
				// printf ("q null\n");
				u = u + 2;
			}
		else
			u++;
		// printf ("u 4 %d\n", u);
		// i++;
		// printf("<%c>\n", data->input[data->i + u]);
	}
	// printf ("size arg %d\n", u);
	if (u == 0)
		u++;
	return (u);
}

void	ft_malloc_arg(t_data *data, t_token *tok) // malloc dans tok->arg l'argument
{
	int		i;
	int		u;
	int		size;
	char	*tmp;
	
	int bordel = 0;

	i = 0;
	u = 0;
	size = ft_size_of_arg(data);
	printf ("size tok arg <%d>\n", size);
	tok->arg = ft_malloc_str(data, size);
	if (size > 0 && tok->arg != NULL)
	{
		while (data->input[data->i + u] && ft_is_separator(data->input, (data->i + u)) == 0)
		{
			printf ("in while : <%s>\n", &(data->input[data->i + u]));
			if (data->input[data->i + u] == '\"' && data->input[data->i + u + 1] != '\"')
			{
				printf ("in dq\n");
				tmp = ft_ret_double_quote(data, &data->input[data->i + u], 0);
				u = u + 2 + ft_str_size(tmp);
				ft_copie_dest_src(tok, tmp);
				ft_strdel(&tmp);
			}
			else if (data->input[data->i + u] == '\'' && data->input[data->i + u + 1] != '\'')
			{
				printf ("in sq\n");
				// printf("malloc arg sgl quote :\n");
				// printf ("u 1 %d\n", u);
				// printf("sgl pre tmp <%s> u %d c <%c>\n", tmp, u, data->input[data->i + u]);
				tmp = ft_ret_simple_quote(data, &data->input[data->i + u], 0);
				u = u + 2 + ft_str_size(tmp);
				// i = i + 2 + ft_str_size(tmp);
				// printf("sgl apr tmp <%s> u %d c <%c>\n", tmp, u, data->input[data->i + u]);
				// if (data->input[data->i + u] == '\'')
				// 	u++;
				// printf("tmp <%s> u %d c <%c>\n", tmp, u, data->input[data->i + u]);
				// u = u + ft_str_size(ft_ret_simple_quote(data, &data->input[data->i + u], 0));
				// printf ("u 2 %d <%s> <%s>\n", u, tok->arg, tmp);
				ft_copie_dest_src(tok, tmp);
				ft_strdel(&tmp);
				// printf ("u 3 %d <%s>\n", u, tok->arg);
			}
			else if ((data->input[data->i + u] == '\"' && data->input[data->i + u + 1] == '\"') || (data->input[data->i + u] == '\'' && data->input[data->i + u + 1] == '\''))
			{
				printf ("Q null <%s>\n", &(data->input[data->i + u]));
				u = u + 2;
				printf ("Q null <%s>\n", &(data->input[data->i + u]));
			}
			else
			{
				i = 0;
				while (tok->arg[i] && tok->arg[i] != '\0')
					i++;
				// printf("els pre tok <%s> u %d i %d c <%c>\n", tok->arg, u, i, data->input[data->i + u]);
				tok->arg[i] = data->input[data->i + u];
				// i++;
				// printf("els apr tok <%s> u %d i %d c <%c>\n", tok->arg, u, i, data->input[data->i + u]);
				if (data->input[data->i + u] == ' ')
				{
					// printf("while space\n");
					u = u + ft_space(data->input, data->i + u);
				}
				else
					u++;
			}
			printf("fin bcl tmp <%s> u %d c <%c>\n", tmp, u, data->input[data->i + u]);
			bordel++;
		}
		while (tok->arg[i] && tok->arg[i] != '\0')
			i++;
		tok->arg[i] = '\0';
		data->i = data->i + u;
	}
	else
		data->err = 200; // erreur malloc
}
