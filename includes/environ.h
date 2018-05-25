/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2018/05/25 20:40:13 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H
# ifdef __linux__
#  include <sys/wait.h>
# endif
# include "t_env.h"

char		**env_create_environ(const char **original, size_t *new_size);
void		env_print_environ(const char **environ);
char		*env_getenv(const char **environ, const char *key, size_t *index);

void		env_load_shlvl_pwd(t_env *env);
void		env_load_base_env(t_env *env, const char **environ);
void		env_change_value(t_env *env, const char *key,
		size_t key_index, const char *new_value);
void		env_add_var(t_env *env, const char *key, const char *value);
void		env_add_change(t_env *env, const char *key, const char *value);
void		env_add_var_from_string(t_env *env, char *key_value, \
		ssize_t eq_index);
void		env_remove_var(t_env *env, const char *key);
int			is_key(const char *key);

#endif
