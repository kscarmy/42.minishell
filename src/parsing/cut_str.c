/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:51:35 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/14 13:57:45 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cut_backslash(char **ret, char *str, int *i)		// 
{
	*ret = ft_straddc(*ret, str[*i+1]);			// add second char after \.
	*i += 2;						// increment i and data->i with 2.
}

void	cut_quotes(t_data *data, char **ret, char *str, int *i)
{
   	*ret = ft_strjoin(*ret, ft_quote(data, str, *i));
			if (data->i == 0)
				return;
			*i = data->i;
}

void	cut_errno(t_data *data, char **ret, int *i)
{
	*ret = ft_strjoin(*ret, ft_itoa(errno));
					if (data->i == 0)
						return;
					*i += 2;
}

void	cut_env_var(t_data *data, char **ret, char *str, int *i)
{
					*ret = ft_strjoin(*ret, put_env(data, str, *i));
					if (data->i == 0)
						return;
					*i = data->i;

}

char	*cut_str(t_data *data, char *str)
{
	char *ret;
	char *quote;
	int	i;

	i = 0;
	ret = malloc(sizeof(char *));
	quote = malloc(sizeof(char *));
	if (!ret || !quote)
		return(NULL);
	ret = NULL;
	quote = NULL;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		while (str[i] == ' ' && str[i + 1] == ' ')
			i++;
		if (str[i-1] != '\\' && (str[i] == '"' || str[i] == '\''))
			cut_backslash(&ret, str, &i);
		if (str[i-1] != '\\' && (str[i] == '"' || str[i] == '\''))
			cut_quotes(data, &ret, str, &i);
		else 
		{
			if (str[i] == '$')
			{
				if (str[i + 1] == '?')
					cut_errno(data, &ret, &i);
				else 
					cut_env_var(data, &ret, str, &i);
			}
			else
				ret = ft_straddc(ret, str[i++]);
		}
	}
	return (ret);
}
