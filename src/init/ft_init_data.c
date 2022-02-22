/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 05:03:09 by guderram          #+#    #+#             */
/*   Updated: 2022/02/21 02:27:25 by guderram         ###   ########.fr       */
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
	data->var->name = ft_malloc_str(data, i);
	data->var->name = ft_strncpy(data->var->name, str, i);
	i++;
	while(str[i + u])
		u++;
	data->var->value = ft_malloc_str(data, u);
	data->var->value = ft_strncpy(data->var->value, &(str[i]), u);
}

void	ft_init_data_pwd(t_data *data) // initialise les deux pwd dans la structure data
{
	int	i;
	t_var *var;
	char *str;

	i = 0;
	str = "PWD";
	var = data->var;
	while (var != NULL && ft_strncmp(var->name, str, 3) != 0)
		var = var->next;
	while (var->value[i])
		i++;
	data->pwd = ft_malloc_str(data, i);
	data->pwd = ft_strncpy(data->pwd, var->value, i);
	
	i = 0;
	str = "OLDPWD";
	var = data->var;
	while (var != NULL && ft_strncmp(var->name, str, 6) != 0)
		var = var->next;
	while (var->value[i])
		i++;
	data->opwd = ft_malloc_str(data, i);
	data->opwd = ft_strncpy(data->opwd, var->value, i);	
}

int	ft_init_data(t_data *data, char **env) // malloc env dans data
{
	int	i;

	i = 0;
	data->var = NULL;
	while (env[i] && data->err == 0)
	{
		ft_create_var_var(data, env[i]);
		i++;
	}
	ft_init_data_pwd(data);
	data->i = 0;
	data->exit = 0;
	data->err = 0;
	data->token = NULL;
	return (1); // 1 = OK
}
