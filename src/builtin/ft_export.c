/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 07:04:57 by guderram          #+#    #+#             */
/*   Updated: 2022/06/23 16:00:37 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_export_in_var(t_data *data, t_token *token, int i)
{
	t_var	*var;
	int		u;
	int		y;

	u = 0;
	y = 0;
	while (token->arg[y])
		y++;
	var = ft_found_var_name(data, token->arg);
	if (var != NULL)
		ft_delete_var(data, var);
	ft_add_new_var(data);
	data->var->name = ft_malloc_str(data, y);
	data->var->name = ft_strncpy(data->var->name, token->arg, y);
	y++;
	while (token->bin[i][y + u])
		u++;
	data->var->value = ft_malloc_str(data, u);
	data->var->value = ft_strncpy(data->var->value, &(token->bin[i][y]), u);
	data->var->value[u] = '\0';
}

void	ft_parse_export_name(t_data *data, t_token *token, int i)
{
	int	u;

	u = 0;
	if (token->arg != NULL)
		ft_strdel(&token->arg);
	while (token->bin[i][u] != '=')
		u++;
	token->arg = ft_malloc_str(data, u);
	if (token->arg != NULL)
		token->arg = ft_strncpy(token->arg, token->bin[i], u);
}

int	ft_export_bin_equal(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '_' && str[1] == '=')
		return (0);
	while (str && str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_export(t_data *data, t_token *token)
{
	int	i;

	i = 0;
	if (token->bin && token->bin[0] == NULL)
	{
		ft_disp_all_var(data, '=', 1);
		ft_putchar('\n');
	}
	while (token->bin && token->bin[i] != NULL)
	{
		if (ft_export_bin_equal(token->bin[i]) == 1)
		{
			ft_parse_export_name(data, token, i);
			ft_export_in_var(data, token, i);
		}
		i++;
	}
}
