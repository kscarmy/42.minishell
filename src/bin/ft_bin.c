/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:42:26 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 22:58:34 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_malloc_one_var(t_data *data, t_var *var)
{
	int		i;
	int		u;
	char	*str;

	i = ft_str_size(var->name);
	u = ft_str_size(var->value);
	i = i + u + 2;
	str = ft_malloc_str(data, i);
	i = 0;
	u = 0;
	while (var->name[i])
	{
		str[i] = var->name[i];
		i++;
	}
	str[i] = '=';
	i++;
	while (var->value != NULL && var->value[u])
	{
		str[i + u] = var->value[u];
		u++;
	}
	str[i + u] = '\0';
	return (str);
}

void	ft_malloc_var(t_data *data)
{
	int		i;
	t_var	*var;

	i = 0;
	var = data->var;
	while (var != NULL)
	{
		var = var->next;
		i++;
	}
	data->env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	var = data->var;
	while (data->err == 0 && var != NULL)
	{
		data->env[i] = ft_malloc_one_var(data, var);
		var = var->next;
		i++;
	}
	data->env[i] = NULL;
}

int	ft_bin_path(t_data *data, t_var *var, t_token *tok, int i)
{
	int	u;
	int	y;

	u = 0;
	y = ft_str_size(tok->bin[0]);
	if (tok->arg != NULL)
		ft_strdel(&tok->arg);
	while (var->value[i + u] && var->value[i + u] != ':')
		u++;
	tok->arg = ft_malloc_str(data, (u + y + 2));
	u = 0;
	y = 0;
	while (var->value[i + u] && var->value[i + u] != ':')
	{
		tok->arg[u] = var->value[i + u];
		u++;
	}
	tok->arg[u] = '/';
	u++;
	while (tok->bin[0][y])
	{
		tok->arg[u + y] = tok->bin[0][y];
		y++;
	}
	tok->arg[u + y] = '\0';
	return (u);
}

void	ft_free_data_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env && data->env[i])
	{
		free(data->env[i]);
		data->env[i] = NULL;
		i++;
	}
	if (data->env != NULL)
	{
		free(data->env);
		data->env = NULL;
	}
}

void	ft_is_bin(t_data *data, t_token *token)
{
	int		i;
	t_var	*var;

	i = 0;
	if (data->env != NULL)
		ft_free_data_env(data);
	ft_malloc_var(data);
	if (access(token->bin[0], F_OK) == 0)
	{
		ft_arg_path_bin(data, token);
		return ;
	}
	var = ft_found_var_name(data, "PATH");
	if (var == NULL)
	{
		ft_putstr("bash: ");
		ft_putstr(token->bin[0]);
		ft_putstr(" : No such file or directory\n");
		g_return = 127;
		return ;
	}
	token->arg = NULL;
	while (var != NULL && var->value != NULL
		&& i < ft_str_size(var->value) && access(token->arg, F_OK) == -1)
		i = i + ft_bin_path(data, var, token, i);
	if (access(token->arg, F_OK) == 0)
		ft_bin_execve(data, token);
	else
	{
		ft_putstr("bash: ");
		ft_putstr(token->bin[0]);
		ft_putstr(" : commande introuvable\n");
		g_return = 127;
	}
}

void	ft_arg_path_bin(t_data *data, t_token *token)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		data->err = 5000;
	else if (pid == 0)
		execve(token->bin[0], token->bin, data->env);
	signal(SIGINT, ft_handler_pid);
	signal(SIGQUIT, ft_handler_pid);
	waitpid(pid, &g_return, 0);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
}

void	ft_bin_execve(t_data *data, t_token *token)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		data->err = 5050;
	else if (pid == 0)
		execve(token->arg, token->bin, data->env);
	signal(SIGINT, ft_handler_pid);
	signal(SIGQUIT, ft_handler_pid);
	waitpid(pid, &g_return, 0);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
}
