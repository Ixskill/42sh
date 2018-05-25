/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:42 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "t_env.h"
# include "history.h"
# include "fcntl.h"

/*
** In unsetenv.c
*/

int				builtin_unsetenv(t_env *env, const char **argv);

/*
** In setenv.c
*/

int				builtin_setenv(t_env *env, const char **argv);

/*
** In env.c
*/

int				builtin_env(t_env *env, const char **argv);

/*
** In env.c
*/

int				builtin_exit(t_env *env, const char **argv);

/*
** In cd.c
*/

int				builtin_cd(t_env *env, const char **argv);

/*
** In exec_builtin.c
*/

int				exec_builtin(t_env *env, const char **argv);

/*
** In echo.c
*/

int				builtin_echo(t_env *env, const char **argv);

/*
** In alias.c
*/

int				builtin_alias(t_env *env, const char **argv);
int				builtin_unalias(t_env *env, const char **argv);
t_list			*find_alias(t_list *alias, const char *argv, size_t len);

/*
** In unset.c
*/

int				builtin_unset(t_env *env, const char **argv);

/*
** In fg.c
*/

int				builtin_fg(t_env *env, const char **argv);

/*
** In fg.c
*/

int				builtin_bg(t_env *env, const char **argv);

/*
** In jobs.c
*/

int				builtin_jobs(t_env *env, const char **argv);

/*
** In set.c
*/

int				builtin_set(t_env *env, const char **argv);

int				builtin_shopt(t_env *env, const char **argv);

int				builtin_shift(t_env *env, const char **argv);
int				builtin_export(t_env *env, const char **argv);
/*
** In file history.c
*/

int				builtin_history(t_env *env, const char **argv);
int				builtin_history_c(t_hist *hist);
int				builtin_history_w(t_hist *hist, const char *argv);
int				builtin_history_r(t_hist *hist, const char *argv);
int				builtin_history_p(t_hist *hist, const char *argv);

/*
** 	In file history_handle_options.c
*/

const char		**handle_r(t_hist *h, const char **argv, int *error);

/*
**	The builtin struct, holding a key (name of the builtin)
**	and the corresponding function
*/

typedef struct	s_builtin
{
	const char	*key;
	int			(*f)(t_env*, const char**);
}				t_builtin;

void			*get_exec_builtin(const char *argv);
void			backslash(char **line, char **word, char quote);
#endif
