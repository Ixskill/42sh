/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:35 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include <stdio.h>
#include "failure.h"
#include "color.h"
#include "line_editing.h"

/*
**	When using a putstr to write the line to the terminal, the behavior is not
**	consistent when it reaches the last column and the char is a newline.  This
**	function makes sure every character is printed where it should (jumps lines
**	twice when it reaches last col with char newline).
*/

static void	term_write_char(t_line *line, size_t i)
{
	if (line->visu_mode)
	{
		if (line->pos < line->visu_start)
			if (i >= line->pos && i < line->visu_start)
				ft_putstr("\e[39;42m");
		if (line->pos >= line->visu_start)
			if (i >= line->visu_start && i < line->pos)
				ft_putstr("\e[39;42m");
	}
	write(2, line->buff + i, 1);
	if (line->visu_mode)
	{
		if (line->pos < line->visu_start)
			if (i >= line->pos && i < line->visu_start)
				ft_putstr("\e[0m");
		if (line->pos >= line->visu_start)
			if (i >= line->visu_start && i < line->pos)
				ft_putstr("\e[0m");
	}
}

static void	write_tab(t_line *line, size_t i)
{
	t_coor	tab_pos;
	size_t	offset;

	tab_pos = get_char_visual_coor(line, i);
	offset = (tab_pos.x % 8) ? (8 - (tab_pos.x % 8)) : 8;
	if (tab_pos.x == 0)
	{
		ft_putchar_fd(' ', 2);
		ft_putchar_fd('\t', 2);
	}
	else if (tab_pos.x + offset >= line->ws_col)
	{
		ft_putchar_fd('\t', 2);
		ft_putchar_fd('\n', 2);
	}
	else
		ft_putchar_fd('\t', 2);
}

void		write_term(t_line *line, size_t i)
{
	t_coor	pos;
	t_coor	l_pos;
	size_t	nb_newl;

	if (line->buff[i] == '\t')
		write_tab(line, i);
	else if (line->buff[i] == '\n')
	{
		pos = get_char_visual_coor(line, i);
		l_pos = get_char_visual_coor(line, i - 1);
		nb_newl = 1;
		if (pos.x == 0 && line->buff[i - 1] != '\n' &&
				l_pos.x != (int)line->ws_col)
			nb_newl = 2;
		write(2, "\n\n", nb_newl);
	}
	else
		term_write_char(line, i);
}

void		term_putstr(t_line *line)
{
	size_t	i;

	i = 0;
	while (line->buff[i])
	{
		write_term(line, i);
		++i;
	}
}
