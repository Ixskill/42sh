/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_complete_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:07 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_asynchronous_list(t_ast *and_or)
{
	t_process	*first_process;
	t_job		*new_job;

	new_job = job_new();
	first_process = process_new(and_or);
	fill_process_av(and_or, first_process);
	new_job->first_process = first_process;
	ft_genlst_pushback((void **)&singleton_jc()->first_job, new_job);
	launch_job(singleton_jc(), new_job, 0);
}

/*
**	list             : list separator_op and_or
**	                 |                   and_or
*/

t_ast	*get_and_or(t_ast *list)
{
	if (is_symb(list->child[2], AND_OR))
		return (list->child[2]);
	return (list->child[0]);
}

/*
**	complete_command : list separator_op
**	                 | list
*/

int		exec_complete_command(t_ast *ast)
{
	int			exit_status;
	t_ast		*and_or;

	and_or = get_and_or(ast->child[0]);
	exit_status = exec_list(ast->child[0]);
	if (ast->child[1] && is_token(ast->child[1]->child[0], TK_AND))
	{
		exec_asynchronous_list(and_or);
		return (exit_status);
	}
	return (exec(and_or));
}

/*
**	list             : list separator_op and_or
**	                 |                   and_or
*/

int		exec_list(t_ast *ast)
{
	int			exit_status;
	t_ast		*and_or;

	if (!ast->child[2])
		return (EXIT_SUCCESS);
	and_or = get_and_or(ast->child[0]);
	exit_status = exec_list(ast->child[0]);
	if (ast->child[1] && is_token(ast->child[1]->child[0], TK_AND))
	{
		exec_asynchronous_list(and_or);
		return (exit_status);
	}
	return (exec(and_or));
}
