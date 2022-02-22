/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:42:26 by guderram          #+#    #+#             */
/*   Updated: 2022/02/22 10:55:57 by guderram         ###   ########.fr       */
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
