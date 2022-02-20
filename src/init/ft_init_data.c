/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 05:03:09 by guderram          #+#    #+#             */
/*   Updated: 2022/02/20 23:43:28 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_create_var_var(t_data *data, char *str) // cree un maillon de chane dans la structure var
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	if (data->var == NULL)
		ft_init_var(data);
	else
		ft_add_new_var(data);
	while(str[i] && str[i] != '=')
		i++;
	// i++;
	// printf("env '%s'", str);

	data->var->name = ft_malloc_str(data, i);
	data->var->name = ft_strncpy(data->var->name, str, i);
	// printf(" : var name '%s'", data->var->name);
	i++;
	while(str[i + u])
		u++;
	data->var->value = ft_malloc_str(data, u);
	data->var->value = ft_strncpy(data->var->value, &(str[i]), u);
	// printf(" : var value '%s'", data->var->value);
	// ft_putstr(data->var->value);
	// printf("\n");
}

int	ft_init_data_bis(t_data *data, char **env, int i)
{
	int	u;

	u = 0;
	while (env[i][u] && env[i][u] != '\n' )
		u++;
	data->env[i] = ft_malloc_str(data, i);
	// data->env[i] = malloc(sizeof(char) * (u + 1));
	if (data->env[i] == NULL)
		return (0); // erreur malloc
	u = 0;
	while (env[i][u] && env[i][u] != '\n' )
	{
		data->env[i][u] = env[i][u];
		u++;
	}
	data->env[i][u] = '\0';
	return (1); // OK
}

int	ft_init_data(t_data *data, char **env) // malloc env dans data
{
	int	i;
//	int	u;

	i = 0;
//	u = 0;
	while (env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	if (data->env == NULL)
		return (0); // erreur malloc
	i = 0;
	data->var = NULL;
	while (env[i] && data->err == 0)
	{
		// printf("env[%d] '%s'\n", i, env[i]); // A SUPP
		ft_create_var_var(data, env[i]);
		// ft_putstr(data->var->value);
		// printf("\n");
		if (ft_init_data_bis(data, env, i) == 0)
			return (0); // erreur malloc
		i++;
		// ft_putstr(data->var->value);
		// printf("\n");
	}
	data->i = 0;
	data->exit = 0;
	data->err = 0;
	data->token = NULL;
	data->env[i] = NULL;
	return (1); // 1 = OK
}
