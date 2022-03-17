/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:25:07 by guderram          #+#    #+#             */
/*   Updated: 2022/03/17 18:04:09 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_cut_export(t_data *data) // cut la commande export
{
	char	*str;
	int		u;
	int		i;

	i = data->i;
	u = 0;
	str = "export";
	while (data->input[i] && data->input[i] != ' ')
	{
		if (ft_is_a_b(data->input[i], str[u]) == 1)
			u++;
		i++;
	}
	if (u == 6)
	{

		data->i = data->i + u;
		ft_create_export_token(data);
		return (1);
	}
	return (0);
}

void	ft_parse_export(t_data *data) // parse les arguments de export
{
	int	i;
	int	m;

	i = data->i;
	m = 0;
	while (data->input[i] && ft_is_separator(data->input, i) == 0)
	{
		if (ft_is_export(data->input, i) != 0)
		{
			m = ft_is_export(data->input, i);
			ft_str_join_input(data, i, m);
			i = i + m;
		}
		m = 0;
		i++;
	}
	// data->i = data->i + i;
}

int		ft_is_export(char *str, int i) // verifie si l'argument d'export est valable
{
	int	equal; // compte le nombre de "=" present
	// int	pos; // retien la position de "="

	equal = 0;
	// pos = 0;
	while (str[i] && str[i] != ' ' && ft_is_separator(str, i) != 1)
	{
		if (str[i] == '=' && str[i + 1] != ';' && str[i + 1] != ' ' && str[i - 1] != ';' && str[i - 1] != ' ')
		{
			// pos = i;
			equal++;
		}
		i++;
	}
	if (equal == 1)
		return (i);
	return (0);
}

int		ft_export_count_equal(t_data *data) // compte le nombre valide d'arguments pour export
{
	int	i;
	int	equal;

	i = data->i;
	equal = 0;
	// printf("'");
	while (data->input[i] && ft_is_separator(data->input, i) == 0)
	{
		// printf("%c", data->input[i]);
		if (data->input[i] == '=' && ft_is_separator(data->input, (i - 1)) == 0 && data->input[i - 1] != ' ')
		{
			equal++;
			while (data->input[i] && ft_is_separator(data->input, i) == 0 && data->input[i] != ' ') // incre i jusqua retomber sur un autre arg
			{
				
				// printf("incre\n");
				i++;
				// printf("%c", data->input[i]);
			}
		}
		else
			i++;
	}
	// printf("'\n");
	// printf("i %d c '%c'\n", i, data->input[i]);
	return (equal);
}

int		ft_export_sizeof_arg(char	*str, int i) // renvoie la taille d'un arg de export en partant de i dans str
{
	int	u;
	u = 0;
	while (str[i + u] && ft_is_separator(str, (i + u)) == 0 && str[i + u] != ' ')
		u++;
	if (ft_check_char(&(str[i]), '=', u) == 1)
		return (u);
	return (0);
}

void	ft_export_in_bin(t_data *data, int nb) // malloc chaques arguments VALIDES de export
{
	int	i;
	int	u;
	int	s; // size of arg

	i = data->i;
	u = 0;
	// printf("in bin 1 : i %d\n", i);
	while (data->input[i] && ft_is_separator(data->input, i) == 0 && u < nb)
	{
		i = i + ft_space(data->input, i);
		s = ft_export_sizeof_arg(data->input, i);
		if (s > 0)
		{
			// printf("in bin 2 : i %d u %d s %d\n", i, u, s);
			data->token->bin[u] = ft_malloc_str(data, s);
			data->token->bin[u] = ft_strncpy(data->token->bin[u], &(data->input[i]), s);
			// printf("str '%s' : bin%d '%s'\n", &(data->input[i]), u, data->token->bin[u]);
			u++;
			
			i = i + s;
		}
		else
			i++;
	}
	// printf("EXPORT IN BIN :\n");
	// printf("data i %d, i : %d\n", data->i, i);
	data->i = i;
	// data->i = data->i + i;
	// printf("data i %d, inp i '%s'\n", data->i, &(data->input[data->i]));
	// printf("data i %d", data->i);
	// printf("in bin 3 : i %d\n", i);
	data->token->bin[u] = NULL;
}


void	ft_create_export_token(t_data *data) // cree le token de la commande export
{
	int	i;

	i = 0;
	if (data->token == NULL)
		ft_init_token(data);
	else
		ft_add_new_token(data);
	data->token->cmd = 3;
	data->token->arg = ft_malloc_str(data, 0);
	i = ft_export_count_equal(data);
	data->token->bin = malloc(sizeof(char *) * (i + 1));
	if (data->token->bin == NULL)
		data->err = 8010;
	else
		ft_export_in_bin(data, i);
	// printf("export : %d\n", i);

	/*	affichage token bin	*/
	// int	u = 0;
	// while (data->token->bin[u])
	// {
	// 	printf("bin%d : '%s'\n", u, data->token->bin[u]);
	// 	u++;
	// }

	/*	affichage token bin	*/

	
	ft_parse_export(data);
}
