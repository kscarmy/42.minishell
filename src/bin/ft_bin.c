/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:42:26 by guderram          #+#    #+#             */
/*   Updated: 2022/06/04 20:17:54 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_malloc_one_var(t_data *data, t_var *var) // malloc une ligne dans data->env
{
	int		i;
	int		u;
	char	*str;

	// printf("ft_malloc_one_var : entree\n");
	i = ft_str_size(var->name);
	u = ft_str_size(var->value);
	i = i + u + 2; // le '+ 1' correspond au signe '='
	str = ft_malloc_str(data, i);
	i = 0;
	u = 0;
	// printf("ft_malloc_one_var : init : ok\n");
	while (var->name[i])
	{
		str[i] = var->name[i];
		i++;
	}
	str[i] = '=';
	i++;
	// printf("ft_malloc_one_var : while 1 : OK\n");
	// printf("ft_malloc_one_var : value : <%s>\n", var->value);
	while (var->value != NULL && var->value[u])
	{
		str[i + u] = var->value[u];
		u++;
	}
	str[i + u] = '\0';
	// printf("ft_malloc_one_var : sortie\n");
	return (str);
}

void	ft_malloc_var(t_data *data) // malloc et renvoie var dans un char **
{
	int		i;
	t_var	*var;

	i = 0;
	var = data->var;
	// ft_putstr("ft_malloc_var : entree\n");
	while (var != NULL)
	{
		var = var->next;
		i++;
	}
	// ft_putstr("ft_malloc_var : while 1 : ok\n");
	data->env = (char **)malloc(sizeof(char *) * (i + 1));
	// data->env = ft_malloc_str(data, i);
	// ft_putstr("ft_malloc_var : malloc : ok\n");
	i = 0;
	var = data->var;
	while (data->err == 0 && var != NULL)
	{
		data->env[i] = ft_malloc_one_var(data, var);
		var = var->next;
		i++;
	}
	// printf("ft_malloc_var : while 2 : ok\n");
	data->env[i] = NULL;
	// printf("ft_malloc_var : sortie\n");
}

int		ft_bin_path(t_data *data, t_var *var, t_token *tok, int i) // stocke et malloc un path dans token->arg
{
	int	u;
	int	y;

	u = 0;
	y = ft_str_size(tok->bin[0]);
	if (tok->arg != NULL)
		ft_strdel(&tok->arg);
	while (var->value[i + u] && var->value[i + u] != ':')
		u++;
	tok->arg = ft_malloc_str(data, (u + y + 2)); // '+ 1' pour ajouter le '/'
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

void	ft_free_data_env(t_data *data) // free un tableau de char
{
	int	i;

	i = 0;
	// char	*tmp;
	// data->env
	// ft_putstr("free tab char :\n");
	// while (data->env[i])
	// {
	// 	ft_putstr(data->env[i]);
	// 	ft_putstr("\n");
	// 	i++;
	// }
	// i = 0;
	// ft_putstr("free tab char : 0\n");
	while (data->env && data->env[i])
	{
		// ft_putstr(data->env[i]);
		// ft_putstr("\n");
		// tmp = &
		// ft_strdel(&data->env[i]);
		free(data->env[i]);
		data->env[i] = NULL;
		i++;
	}
	// ft_putstr("free tab char : 1\n");
	if (data->env != NULL)
	{
		free(data->env);
		data->env = NULL;
	}
	// ft_putstr("free tab char : 2\n");
}


void	ft_is_bin(t_data *data, t_token *token) //
{
	int		i;
	t_var	*var;

	i = 0;
	// ft_putstr("ft_is_bin :\n");
	var = ft_found_var_name(data, "PATH");
	if (var == NULL)
	{
		ft_putstr("bash: ");
		ft_putstr(token->bin[0]);
		ft_putstr(" : No such file or directory\n");
		g_return = 127;
		// printf("PATH UNSTET :\n");
		return ;
	}
	// printf("ft_is_bin : var OK\n");
	// printf("ft_is_bin : tok list\n");
	// ft_print_token_list(data);
	// printf("ft_is_bin : suite\n");
	// printf("tok <%s> bin <%s>\n", token->arg, token->bin[0]);
	
	// ft_print_token_list(data);
	// ft_putstr("ft_is_bin : suite\n");
	if (data->env != NULL)
		ft_free_data_env(data);
	// ft_putstr("ft_is_bin : free var : OK\n");
	ft_malloc_var(data);
	// ft_putstr("ft_is_bin : malloc var : OK\n");

	/*	fin zone test	*/
	// printf("tok <%s> bin <%s>\n", token->arg, token->bin[0]);
	if (access(token->arg, F_OK) == 0)
	{
		// printf("acces OK !\n");
		ft_bin_execve(data, token);
		return ;
	}

	/*	fin zone test	*/
	
	token->arg = NULL;

	// ft_putstr("ft_is_bin : fin zone test : OK\n");
	while (var != NULL && var->value != NULL && i < ft_str_size(var->value) && access(token->arg, F_OK) == -1)
	{
		i = i + ft_bin_path(data, var, token, i);
	}
	// ft_putstr("token arg :\n");
	if (access(token->arg, F_OK) == 0)
		ft_bin_execve(data, token);
	else
	{
		ft_putstr("bash: ");
		ft_putstr(token->bin[0]);
		ft_putstr(" : commande introuvable\n");
		g_return = 127;
		// printf("ft_bin > ft_is_bin : COMMANDE INCONNUE\n");
	}
	// ft_putstr("token arg :\n");
	// if (access(token->arg, F_OK) == -1)
	// {
	// 	ft_arg_path_bin(data, token);
	// }
	// else
	// 	ft_bin_execve(data, token);
}

void	ft_arg_path_bin(t_data *data, t_token *token) // cherche si la string est un binaire
{
	int	i;
	pid_t	pid;
	// int		status;

	i = access(token->bin[0], F_OK);
	printf("NON MICHEL !\n");
	if (i == 0)
	{
		pid = fork();
		if (pid == -1)
			data->err = 5000;
		else if (pid == 0)
			i = execve(token->bin[0], token->bin, data->env);
		else
			waitpid(pid, &g_return, 0);
	}
	else
	{
		// data->err = 4000; // ERREUR : COMMANDE NON TROUVEE !
		printf("ft_bin > ft_is_bin : COMMANDE INCONNUE\n");
	}
}

void	ft_bin_execve(t_data *data, t_token *token) //
{
	pid_t	pid;
	// int		status;

	// printf("------ Entree Fork : <%s>\n", token->arg);
	// ft_putstr_fd("SORTIE SUR 1 :", 1);
	// printf("fd_in : %d\n", data->pipe->fd_i);
	// printf("fd_out : %d\n", data->pipe->fd_o);
	// dup2(data->pipe->fd_i, 0);
	pid = fork();
	if (pid == -1)
		printf("ERREUR TEST FORK\n");
	else if (pid == 0)
		execve(token->arg, token->bin, data->env);
	// else
	waitpid(pid, &g_return, 0);
	// printf("------ Sortie Fork <%s> !\n", token->arg);
}

// void	ft_test(t_data *data) // TEST
// {
// 	char	*path;
// 	char	**argv;
// 	int	i;

// 	i = 0;
// 	argv = malloc(sizeof(char *) * 3);
// 	argv[0] = "ls";
// 	argv[1] = "-la";
// 	argv[2] = NULL;

// 	path = "/bin/ls";
// 	i = access(path, F_OK);
// 	printf("access : '%d'\nerror : '%d'\n", i, data->err);
// 	i = 0;

// 	i = execve(path, data->token->bin, NULL);
// 	printf("execve : '%d'\nerror : '%d'\n", i, data->err);

// }
