/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:53 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include <signal.h>
#include "completion.h"

void	comple_handle_sigwinch(int signum)
{
	t_comple	*c;

	c = singleton_comple();
	edit_handle_sigwinch(0);
	put_termcap("cd");
	comple_clear(*c);
	put_termcap("up");
	comple_init_winch(c);
	comple_refresh(singleton_line(), *c);
	(void)signum;
}

void	comple_handle_sigint(int signum)
{
	t_comple	*c;

	c = singleton_comple();
	comple_clear(*c);
	put_termcap("up");
	comple_free(*c);
	singleton_line()->completion = 0;
	edit_set_signals_open();
	edit_refresh(singleton_line());
	(void)signum;
}

void	comple_set_comple_signum(int num)
{
	singleton_comple()->signum = num;
}

void	comple_set_signals(void)
{
	struct sigaction	sa;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sa.sa_handler = comple_handle_sigwinch;
	sa.sa_flags = SA_RESTART;
	sa.sa_mask = block_mask;
	sigaction(SIGWINCH, &sa, NULL);
	signal(SIGINT, comple_handle_sigint);
}
