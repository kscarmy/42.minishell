/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 23:58:29 by mourdani          #+#    #+#             */
/*   Updated: 2022/06/06 15:08:01 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	ft_handler(int	sig)
{
	// printf("int %d quit %d segv %d\n", SIGINT, SIGQUIT,  SIGSEGV);
	// printf("sig %d\n", sig);
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		// rl_replace_line("", 0);
		// ft_putstr_fd("\b\b\b\b", 1);
		rl_redisplay();
		g_return = 2;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		g_return = 0;
		return ;
		// printf("sigquit ctr back\n");
	}	
}


void	ft_handler_pid(int	sig)
{
	
	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 1);
}

void init_signals(void)
{

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	// signal(SIGSEGV, handler);
	
// struct termios old_termios, new_termios;

	// tcgetattr(0,&old_termios);
	// new_termios             = old_termios;
	// new_termios.c_cc[VINTR] = 4; // ^D 
	// new_termios.c_cc[VSUSP] = 3; // ^C
	// new_termios.c_cc[VEOL] = 21; // ^'\' 
	// tcsetattr(0,TCSANOW,&new_termios);
}
