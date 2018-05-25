/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_line_refresh.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:20 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

/*
**	Injects the history line WITHOUT ITS RETURN AT THE END
**	in line->buff
**	line->len = ft_strlen((const char *)new_line);
**	line->pos = line->len;
**	edit_refresh(line);
*/

void	history_line_refresh(t_line *line, char *new_line)
{
	size_t	i;

	edit_refresh_clear(line);
	ft_strclr(line->buff);
	i = ft_strlen(new_line);
	if (i >= 1 && new_line[i - 1] == '\n')
		new_line[i - 1] = 0;
	edit_insert_str(line, line->buff, new_line);
	put_prompt(line);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
}
