/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include "environ.h"
#include "prompt.h"
#include "get_next_line.h"
#include "line_editing.h"

void	put_prompt(t_line *line)
{
	t_coor coord;

	ft_putstr_fd(line->prompt, 2);
	coord = get_prompt_visual_offset(line);
	if (coord.x == 0)
		ft_putchar_fd('\n', 2);
}

void	load_prompt(t_env *env, t_line *line, char *var, char *defaut)
{
	char	*prompt;
	size_t	len;

	len = 0;
	prompt = NULL;
	if (var && ft_strequ(var, "PS1"))
		prompt = get_ps1(env, &len);
	else if (var)
		prompt = env_getenv((const char**)env->environ, var, NULL);
	if (!prompt)
		prompt = defaut;
	if (var && ft_strequ(var, "PS1"))
		line->prompt_len = len;
	else
		line->prompt_len = ft_strlen(prompt);
	if (line->prompt)
		free(line->prompt);
	if (var && ft_strequ(var, "PS1"))
		line->prompt = prompt;
	else
		line->prompt = ft_strdup(prompt);
}
