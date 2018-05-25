/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:04 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "environ.h"
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "exec.h"
#include "local.h"
#include <pwd.h>
#include "modes.h"
#include "get_next_line.h"
#include "lexer.h"
#include "bang.h"

char	*line_editing_get_line(t_line *line, t_hist *hist,
		void (*sig_handler)(void))
{
	put_prompt(line);
	history_init(hist);
	edit_line_init(line, sig_handler);
	return (edit_get_input());
}

char	*stream_get_line(int stream)
{
	char	*buff;

	buff = NULL;
	get_next_line(stream, &buff);
	return (buff);
}

/*
**	i point after the last \n or to the \0
*/

char	*string_get_line(t_modes *modes)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (modes->string[i])
	{
		if (modes->string[i] == '\n')
		{
			while (modes->string[i] == '\n')
				i++;
			break ;
		}
		i++;
	}
	if (i > 0)
	{
		res = ft_strndup(modes->string, i);
		modes->string += i;
	}
	return (res);
}

int		get_input(t_modes *modes, char **buff)
{
	char	*tmp;

	if (modes->mode == INTERACTIVE_MODE)
	{
		*buff = ft_strdup(line_editing_get_line(singleton_line(), \
					singleton_hist(), &edit_set_signals_open));
		if ((tmp = bang_expand((const char*)*buff, singleton_hist())))
		{
			if (!ft_strequ(tmp, *buff))
				ft_dprintf(2, "%s\n", tmp);
			*buff = ft_strchange(*buff, tmp);
		}
	}
	else if (modes->mode == STRING_MODE)
		*buff = string_get_line(modes);
	else
	{
		*buff = stream_get_line(modes->stream);
	}
	if (!*buff)
		return (0);
	return (1);
}

int		reopen(t_lexer *lex, t_parser *parser, t_modes *modes)
{
	char	*new_command;

	if (((struct s_info*)lex->state->data)->state == BS)
	{
		ft_simple_lst_del_one(&lex->state_list, lex->state, free_info);
		lex->line = ft_strchange(lex->line, ft_strndup(lex->line,
					ft_strlen(lex->line) - 2));
		lex->state = ft_last_simple_lst(lex->state_list);
		lex->pos -= 2;
	}
	if (modes->mode == INTERACTIVE_MODE)
		reopen_line_editing(lex, parser, &new_command);
	else if (!get_input(modes, &new_command))
		return (0);
	lex->line = ft_strjoin_free(lex->line, new_command, 0b10);
	return (1);
}
