/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 23:58:29 by mourdani          #+#    #+#             */
/*   Updated: 2022/05/30 16:30:24 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		g_return = 2;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		g_return = 0;
	}

	// rl_on_new_line();
	// printf("JEAN MICH\n");
	// ft_putchar('\n');
	// write(0, "~$ ", 3);
	// rl_on_new_line();
}

void	jean()
{
	rl_redisplay();
	return ;
}

void init_signals(void)
{
	signal(SIGINT, jean);
	signal(SIGQUIT, handler);
	// struct termios old_termios, new_termios;

	// tcgetattr(0,&old_termios);
	// new_termios             = old_termios;
	// new_termios.c_cc[VINTR] = 4; // ^D 
	// new_termios.c_cc[VSUSP] = 3; // ^C
	// new_termios.c_cc[VEOL] = 21; // ^'\' 
	// tcsetattr(0,TCSANOW,&new_termios);
}
