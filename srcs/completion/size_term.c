/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:53 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line_editing.h"
#include "failure.h"
#include <sys/ioctl.h>

size_t				get_ws_col(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

size_t				get_ws_row(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_row);
}

size_t				get_reserved_line(size_t ws_row, t_line *line)
{
	size_t	used_by_prompt;
	size_t	used_by_buff;

	used_by_prompt = (size_t)get_prompt_visual_offset(line).y;
	used_by_buff = (size_t)get_char_visual_coor(line, line->len).y;
	return (ws_row - used_by_prompt - used_by_buff);
}
