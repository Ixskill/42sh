/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shopt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOPT_H
# define SHOPT_H
# include "t_env.h"

/*
**	Defining flags for options
*/

/*
**	If you edit OPTNB, recompile the program.
*/

# define OPTNB 2U
# define ALLEXPORT 0b1L
# define SYNCOLOR 0b10L

struct						s_shopt_mask
{
	long	mask;
	char	*string;
};

extern struct s_shopt_mask	g_shopt_mask[OPTNB + 1];

int							set_shell_opt(t_env *env, int sign, \
		const char *option_value);
#endif
