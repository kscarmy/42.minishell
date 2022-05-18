/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 23:58:29 by mourdani          #+#    #+#             */
/*   Updated: 2022/05/18 16:55:15 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	handler_c()
{
	printf("\n");
	write(0, "~$ ", 3);
}

void	handler_q()
{
	
}

void init_signals(void)
{
//	struct termios old_termios, new_termios;

//	tcgetattr(0,&old_termios);
//	new_termios             = old_termios;
//	new_termios.c_cc[VINTR] = 4; // ^D 
//	new_termios.c_cc[VSUSP] = 3; // ^C
//	new_termios.c_cc[VEOL] = 21; // ^'\' 
//	tcsetattr(0,TCSANOW,&new_termios);
	signal(SIGINT, handler_c);
	signal(SIGQUIT, handler_q);
}
