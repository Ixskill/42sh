/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:09 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "builtin.h"
#include "job_control.h"
#include "hash_table.h"
#include "expand.h"
#include "exec.h"

/*
**	pipeline         :      pipe_sequence
**	                 | Bang pipe_sequence
*/

/*
**	pipe_sequence    :                             command
**	                 | pipe_sequence '|' linebreak command
*/

int		pipe_sequence_has_to_fork(t_ast *pipe_sequence)
{
	t_ast	*simple_command;
	char	**cmd_name_expanded;

	if (pipe_sequence->child[3] != NULL)
		return (1);
	simple_command = pipe_sequence->child[0]->child[0];
	if (!(is_symb(simple_command, SIMPLE_COMMAND)))
		return (0);
	cmd_name_expanded = get_cmd_name(simple_command, NO_SHOW_ERROR);
	if (cmd_name_expanded && cmd_name_expanded[0] &&
			!get_exec_builtin(cmd_name_expanded[0])
		&& !get_function(singleton_env(), cmd_name_expanded[0]))
	{
		ft_arraydel(&cmd_name_expanded);
		return (1);
	}
	ft_arraydel(&cmd_name_expanded);
	return (0);
}

void	fill_job(t_ast *pipe_sequence, t_process **first_process)
{
	if (pipe_sequence->child[0] && !pipe_sequence->child[3])
	{
		return (ft_genlst_add(first_process, \
				fill_process_av(pipe_sequence->child[0], \
						process_new(pipe_sequence->child[0]))));
	}
	if (pipe_sequence->child[0] && pipe_sequence->child[3])
	{
		ft_genlst_add(first_process, \
				fill_process_av(pipe_sequence->child[3], \
					process_new(pipe_sequence->child[3])));
		fill_job(pipe_sequence->child[0], first_process);
	}
}

void	debug_process(t_process *first_process)
{
	while (first_process)
	{
		debug_symbol(first_process->command);
		first_process = first_process->next;
	}
}

int		exec_pipeline(t_ast *ast)
{
	int			exit_status;
	t_process	*first_process;
	t_job		*new_job;
	t_ast		*pipe_sequence;
	int			ret;

	first_process = NULL;
	pipe_sequence = ast->child[is_token(ast->child[0], TK_BANG) ? 1 : 0];
	if (pipe_sequence_has_to_fork(pipe_sequence))
	{
		ret = singleton_jc()->warn_exit;
		singleton_jc()->warn_exit = 0;
		new_job = job_new();
		fill_job(pipe_sequence, &first_process);
		new_job->first_process = first_process;
		ft_genlst_pushback((void **)&singleton_jc()->first_job, new_job);
		exit_status = launch_job(singleton_jc(), new_job, 1);
		singleton_jc()->warn_exit = ret;
	}
	else
		exit_status = exec(pipe_sequence);
	if (is_token(ast->child[0], TK_BANG))
		return (exit_status > 0 ? EXIT_SUCCESS : EXIT_FAILURE);
	return (exit_status);
}
