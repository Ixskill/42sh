/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_mark_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:23 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "job_control.h"

static int		mark_process_status_process(int status, t_process *p)
{
	p->status = status;
	if (WIFSTOPPED(status))
		p->stopped = 1;
	else
	{
		p->completed = 1;
		if (WIFSIGNALED(status))
			p->signaled = 1;
	}
	return (0);
}

int				mark_process_status(t_job_control *jc, pid_t pid, int status)
{
	t_job		*j;
	t_process	*p;

	if (pid == 0 || errno == ECHILD)
		return (-1);
	j = jc->first_job;
	while (j)
	{
		p = j->first_process;
		while (p)
		{
			if (p->pid == pid)
				return (mark_process_status_process(status, p));
			p = p->next;
		}
		j = j->next;
	}
	ft_dprintf(2, "No child process %d.\n", pid);
	return (-1);
}
