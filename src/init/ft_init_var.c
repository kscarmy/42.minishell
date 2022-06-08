/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:41:03 by guderram          #+#    #+#             */
/*   Updated: 2022/06/08 11:09:20 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_init_var(t_data *data)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (var == NULL)
		data->err = 1001;
	else
	{
		var->name = NULL;
		var->value = NULL;
		var->next = NULL;
		var->prev = NULL;
	}
	data->var = var;
}

void	ft_add_new_var(t_data *data)
{
	t_var	*new;

	new = (t_var *)malloc(sizeof(t_var));
	if (new == NULL)
		data->err = 101;
	else
	{
		new->name = NULL;
		new->value = NULL;
		new->next = data->var;
		data->var = new;
		new->prev = NULL;
		new->next->prev = new;
	}
}

void	ft_free_var(t_data *data, t_var *var)
{
	if (var->name != NULL)
	{
		free (var->name);
		var->name = NULL;
		if (var->name != NULL)
			data->err = 1003;
	}
	if (var->value != NULL)
	{
		free (var->value);
		var->value = NULL;
		if (var->name != NULL)
			data->err = 1004;
	}
}

void	ft_delete_var(t_data *data, t_var *delete)
{
	if (delete == NULL)
		data->err = 102;
	if (data->var != NULL && delete != NULL)
	{
		ft_free_var(data, delete);
		if (delete->next == NULL && delete->prev != NULL)
			delete->prev->next = NULL;
		if (delete->prev == NULL && delete->next != NULL)
		{
			data->var = delete->next;
			delete->next->prev = NULL;
		}
		if (delete->prev == NULL && delete->next == NULL)
			data->var = NULL;
		if (delete->next != NULL && delete->prev != NULL)
		{
			delete->prev->next = delete->next;
			delete->next->prev = delete->prev;
		}
		if (delete && delete != NULL)
		{
			free (delete);
			delete = NULL;
		}
	}
}
