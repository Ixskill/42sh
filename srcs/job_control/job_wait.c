#include "job_control.h"
#include <errno.h>
#include "color.h"

void	update_status(t_job_control *jc)
{
	int status;
	pid_t pid;

	while (42)
	{
		errno = 0;
		pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
		if (!(!mark_process_status(jc, pid, status)))
			break ;
	}
}

void	get_job_exit_status(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p && p->next)
		p = p->next;
	if (WIFEXITED(p->status))
		j->exit_status = WEXITSTATUS(p->status);
	else if (p->stopped)
		j->exit_status = EXIT_FAILURE;
	else if (WIFSIGNALED(p->status))
		j->exit_status = EXIT_FAILURE;
}

void	wait_for_job(t_job_control *jc, t_job *j)
{
	int status;
	pid_t pid;

	while (42)
	{
		errno = 0;
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (!(!mark_process_status(jc, pid, status)
					&& !job_is_stopped(j)
					&& !job_is_completed(j)))
			break ;
	}
	get_job_exit_status(j);
}