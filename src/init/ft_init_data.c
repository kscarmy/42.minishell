/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 05:03:09 by guderram          #+#    #+#             */
/*   Updated: 2022/05/30 15:19:21 by guderram         ###   ########.fr       */
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
	// printf("OK 1B1\n");
	while (var != NULL && ft_strncmp(var->name, str, 3) != 0)
		var = var->next;
	// printf("OK 1B2\n");
	while (var->value[i])
		i++;
	// printf("OK 1B3\n");
	data->pwd = ft_malloc_str(data, i);
	data->pwd = ft_strncpy(data->pwd, var->value, i);
	// printf("OK 1B4\n");
	i = 0;
	str = "OLDPWD";
	var = data->var;
	while (var != NULL && ft_strncmp(var->name, str, 6) != 0)
		var = var->next;
	// printf("OK 1B5\n");
	while (var != NULL && var->value[i])
		i++;
	// printf("OK 1B6\n");
	data->opwd = ft_malloc_str(data, i);
	// printf("OK 1B7\n");
	data->opwd = ft_strncpy(data->opwd, var->value, i);	
	// printf("OK 1B8\n");
}

void	ft_init_pipe(t_data *data) // prepare la structure des pipes
{
	t_pipe	*pip;

	pip = malloc(sizeof(t_pipe));
	data->pipe = pip;
	data->pipe->fd_o = -10;
	data->pipe->fd_i = -10;
	data->pipe->ofd_o = -10;
	data->pipe->ofd_i = -10;
	// printf("PIPE INIT : %d\n", data->pipe->fd_o);
}

int		ft_init_data(t_data *data, char **env) // malloc env dans data
{
	int	i;

	i = 0;
	data->var = NULL;
	// printf("OK 1A\n");
	t_var	*t;
	while (env[i] && data->err == 0)
	{
		ft_create_var_var(data, env[i]);
		i++;
	}
	ft_add_new_var(data);
	data->var->name = malloc(sizeof(char) * 2);
	data->var->name[0] = '$';
	data->var->name[1] = '\0';
	// printf("OK 1B\n");
	ft_init_data_pwd(data);
	// printf("OK 1BB\n");
	data->i = 0;
	data->exit = 0;
	data->err = 0;
	data->token = NULL;
	// printf("OK 1C\n");
	ft_init_pipe(data);
	t = ft_found_var_name(data, "SHLVL");
	if (t != NULL)
	{
		i = ft_atoi(t->value);
		i++;
		ft_strdel(&t->value);
		t->value = ft_itoa(i);
	}
	else
	{
		
	}
	// printf("OK 1D\n");
	// data->fd_in = -10;
	// data->fd_out = -10;
	return (1); // 1 = OK
}
