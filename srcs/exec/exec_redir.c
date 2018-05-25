/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:00 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "exec.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"

#include <stdio.h>

static t_redir	g_redir[] =
{
	{TK_GREAT, &file_redir},
	{TK_DGREAT, &file_redir},
	{TK_LESS, &file_redir},
	{TK_LESSGREAT, &file_redir},
	{TK_LESSAND, &merge_fd},
	{TK_GREATAND, &merge_fd},
	{-1, NULL}
};

void	*get_exec_redir_func(int id)
{
	size_t		i;

	i = 0;
	while (g_redir[i].f && g_redir[i].id != id)
		i++;
	return (g_redir[i].f);
}

/*
**	This function is used to open the file with the right options depending on
**	the operator's id. FD of the opened file will be returned.
*/

/*
**	Fd merging with op >& and <&
*/

/*
**	If target is '-' file descriptor "io_number" should be closed, and restored
**	after command is up.
*/

int		merge_fd(int io_number, char *target, t_list **redir_stack, \
		int id)
{
	int	target_fd;
	int	natural_fd;

	natural_fd = TRUE;
	if (io_number == -1)
		io_number = (id == TK_LESSAND) ? STDIN_FILENO : STDOUT_FILENO;
	if (ft_strequ(target, "-"))
		target_fd = -2;
	else
		target_fd = ft_atoi(target);
	if (target_fd == -2 || (target_fd >= STDIN_FILENO &&
				(fcntl(target_fd, F_GETFD) != -1)))
		push_dup(io_number, target_fd, natural_fd, redir_stack);
	return (1);
}

int		file_redir(int io_number, char *target, t_list **redir_stack, \
		int id)
{
	int	target_fd;

	if (io_number == -1)
		io_number = (id == TK_LESS || id == TK_LESSGREAT) ? \
					STDIN_FILENO : STDOUT_FILENO;
	if ((target_fd = redir_open_file(target, id)) == -1)
		return (0);
	if (target_fd >= STDIN_FILENO)
		push_dup(io_number, target_fd, FALSE, redir_stack);
	return (1);
}
