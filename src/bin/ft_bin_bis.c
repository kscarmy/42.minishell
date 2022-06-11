/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:00:06 by guderram          #+#    #+#             */
/*   Updated: 2022/06/11 14:53:18 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_is_bin_bis(t_data *data, t_token *token, t_var *var, int *i)
{
	token->arg = NULL;
	while (var != NULL && var->value != NULL
		&& *i < ft_str_size(var->value) && access(token->arg, F_OK) == -1)
		*i = *i + ft_bin_path(data, var, token, *i);
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
	ft_is_bin_bis(data, token, var, &i);
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
