/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 23:58:29 by mourdani          #+#    #+#             */
/*   Updated: 2022/07/06 09:45:35 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_return = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		g_return = 0;
	}
}

void	ft_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_return = sig;
		ft_putstr_fd("\b\b  \b\b", 1);
		rl_replace_line("", 0);
		ft_putstr_fd("\b\b  \b\b", 1);
		g_return = 130;
		exit(130);
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
	g_return = sig;
}

void	ft_handler_pid(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	g_return = sig;
}

void	init_signals(void)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
}
