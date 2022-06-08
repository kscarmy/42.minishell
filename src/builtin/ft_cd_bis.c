/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:23:19 by guderram          #+#    #+#             */
/*   Updated: 2022/06/08 11:28:51 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cd_from_data_to_var_opwd(t_data *data)
{
	t_var	*opwd;

	opwd = ft_found_var_name(data, "OLDPWD");
	if (opwd == NULL)
	{
		ft_add_new_var(data);
		data->var->name = ft_malloc_str(data, 6);
		data->var->name = ft_strncpy(data->var->name, "OLDPWD", 6);
		data->var->value = ft_malloc_str(data, ft_strlen(data->opwd));
		data->var->value = ft_strncpy(data->var->value,
				data->opwd, ft_strlen(data->opwd));
	}
	else
	{
		ft_strdel(&opwd->value);
		opwd->value = ft_malloc_str(data, ft_strlen(data->opwd));
		opwd->value = ft_strncpy(opwd->value,
				data->opwd, ft_strlen(data->opwd));
	}
}

void	ft_cd_from_data_to_var_pwd(t_data *data)
{
	t_var	*pwd;

	pwd = ft_found_var_name(data, "PWD");
	if (pwd == NULL)
	{
		ft_add_new_var(data);
		data->var->name = ft_malloc_str(data, 3);
		data->var->name = ft_strncpy(data->var->name, "PWD", 3);
		data->var->value = ft_malloc_str(data, ft_strlen(data->pwd));
		data->var->value = ft_strncpy(data->var->value,
				data->pwd, ft_strlen(data->pwd));
	}
	else
	{
		ft_strdel(&pwd->value);
		pwd->value = ft_malloc_str(data, ft_strlen(data->pwd));
		pwd->value = ft_strncpy(pwd->value, data->pwd, ft_strlen(data->pwd));
	}
}
