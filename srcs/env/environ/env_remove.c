/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:54 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "hash_table.h"
#include "libft.h"
#include "local.h"

void	env_remove_var_index(t_env *env, size_t key_index)
{
	size_t	environ_size;
	char	**environ;
	char	**new_environ;

	environ = env->environ;
	environ_size = env->environ_size;
	new_environ = palloc(sizeof(char*) * (environ_size - 1 + 1));
	free(environ[key_index]);
	ft_memcpy(new_environ, environ, key_index * sizeof(*new_environ));
	ft_memcpy(new_environ + key_index, environ + key_index + 1, \
			(environ_size - key_index) * sizeof(*new_environ));
	new_environ[environ_size - 1] = NULL;
	free(env->environ);
	env->environ = new_environ;
	env->environ_size--;
}

void	env_remove_var(t_env *env, const char *key)
{
	size_t	index;

	if (env_getenv((const char**)env->environ, key, &index))
	{
		env_remove_var_index(env, index);
		local_remove(env, key);
	}
}
