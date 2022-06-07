/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:38:29 by guderram          #+#    #+#             */
/*   Updated: 2022/06/07 13:10:55 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    ft_free_minishell(t_data *data) // free les mallocs avant de sortir du programme.
{
    t_var   *var;
    t_token *tok;

    var = data->var;
    tok = data->token;
    // ft_putstr("free minishell :\n");
    while (var != NULL)
    {
        ft_delete_var(data, var);
        var = data->var;
    }
    // ft_putstr("free minishell :\n");
    // free()
    while (tok != NULL)
    {
        tok = data->token;
        ft_delete_token(data, tok);
    }
    if (data->input != NULL)
        ft_strdel(&data->input);
    if (data->pwd != NULL)
		ft_strdel(&data->pwd);
    if (data->opwd != NULL)
		ft_strdel(&data->opwd);	
	if (data->tmp != NULL)
		ft_strdel(&data->tmp);

        
    // if (data->token != NULL)
    //     ft_strdel(&data->token);
    // if (data->var != NULL)
    //     ft_strdel(&data->var);
    if (data->pipe != NULL)
    {
        free(data->pipe);
        data->pipe = NULL;
        // ft_strdel(&data->pipe);
    }
    ft_free_data_env(data);
    data->env = NULL;

    
    // free(data->pipe);
    // data->pipe = NULL;
    // free(data->input);
    // data->input = NULL;
}
