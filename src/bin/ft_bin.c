/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:42:26 by guderram          #+#    #+#             */
/*   Updated: 2022/02/25 04:03:14 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int		ft_bin_access(t_data *data, int i, int u, char *path) // ret 0 si rien trouver, sinon 1
// {
// 	char	*str;

// 	str = ft_malloc_str(data, (u - i));
// 	if (str != NULL)
// 	{
// 		str = ft_strncpy(str, &(path[i]), (u - i));
		
// 	}

	
// }

char	*ft_malloc_one_var(t_data *data, t_var *var) // malloc une ligne dans data->env
{
	int		i;
	int		u;
	char	*str;

	i = ft_str_size(var->name);
	u = ft_str_size(var->value);
	i = i + u + 1; // le '+ 1' correspond au signe '='
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
	while (var->value[u])
	{
		str[i + u] = var->value[u];
		u++;
	}
	str[i + u] = '\0';
	return (str);
}

void	ft_malloc_var(t_data *data) // malloc et renvoie var dans un char **
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
	data->env = malloc(sizeof(char *) * (i + 1));
	// data->env = ft_malloc_str(data, i);
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


// int		ft_bin_access(t_data *data, char *str) // renvoie la valeur de access
// {
// 	return (access(str, F_OK));
// }

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
	// printf("tok bin : ;%s'");
	tok->arg[u + y] = '\0';
	return (u);
}

void	ft_free_tab_char(char **str) // free un tableau de char
{
	int	i;

	i = 0;
	while (str != NULL && str[i])
	{
		ft_strdel(&str[i]);
		i++;
	}
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}


void	ft_is_bin(t_data *data, t_token *token) // 
{
	int		i;
	t_var	*var;

	i = 0;
	var = ft_found_var_name(data, "PATH");
	token->arg = NULL;
	if (data->env != NULL)
		ft_free_tab_char(data->env);
	ft_malloc_var(data);
	while (var->value != NULL && var->value[i] && access(token->arg, F_OK) == -1)
	{
		i = i + ft_bin_path(data, var, token, i);
	}
	if (access(token->arg, F_OK) == -1)
	{
		ft_arg_path_bin(data, token);
		
		
	}
	else
		ft_bin_execve(data, token);
}

void	ft_arg_path_bin(t_data *data, t_token *token) // cherche si la string est un binaire
{
	int	i;
	pid_t	pid;
	int		status;

	i = access(token->bin[0], F_OK);
	if (i == 0)
	{
		pid = fork();
		if (pid == -1)
			data->err = 5000;
		else if (pid == 0)
			i = execve(token->bin[0], token->bin, data->env);
		else
			waitpid(pid, &status, 0);
	}
	else
	{
		data->err = 4000; // ERREUR : COMMANDE NON TROUVEE !
		printf("ft_bin > ft_is_bin : COMMANDE INCONNUE\n");
	}
}

void	ft_bin_execve(t_data *data, t_token *token) // 
{
	int		i;
	pid_t	pid;
	int		status;
	// int u = 0;

	pid = fork();
	i = 0;
	if (pid == -1)
		printf("ERREUR TEST FORK\n");
	else if (pid == 0)
		i = execve(token->arg, token->bin, data->env);
	else
		waitpid(pid, &status, 0);
	
	// printf("EXECVE i : %d\n", i); // A SUPP
	// printf("PATH : '%s'\n", token->arg);
	// while (data->env[u])
	// {
	// 	printf("'%s'\n", data->env[u]);
	// 	u++;
	// }
}

void	ft_test(t_data *data) // TEST
{
	char	*str;
	char	*cmd;
	char	*path;
	char	*env;
	char	**argv;
	int	i;

	i = 0;
	argv = malloc(sizeof(char *) * 3);
	argv[0] = "ls";
	argv[1] = "-la";
	argv[2] = NULL;
	// env = getenv(NULL);
	env = NULL;
	path = "/bin/ls";
	cmd = "ls";
	str = "/usr/local/bin";
	i = access(path, F_OK);
	printf("access : '%d'\nerror : '%d'\n", i, data->err);
	i = 0;

	i = execve(path, data->token->bin, NULL);
	printf("execve : '%d'\nerror : '%d'\n", i, data->err);

}
