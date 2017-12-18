/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "exec.h"
#include "libft.h"
#include "hash_table.h"
#include "failure.h"
#include "builtin.h"

static const char	**handle_i(t_env *env, const char **argv)
{
	env_free_env(env);
	env->environ = env_create_environ(NULL, &(env->environ_size));
	return (argv + 1);
}

static const char	**apply_opt(t_env *env, const char **argv, int *error)
{
	while (*argv)
	{
		if (ft_strequ(*argv, "-i"))
			argv = handle_i(env, argv);
		else if (ft_strequ(*argv, "-u"))
		{
			if (!(*(argv + 1)))
			{
				investigate_error(1, NULL,
						"env: option requires an argument -- u", 0);
				*error = 1;
				return (argv);
			}
			env_remove_var(env, *(argv + 1));
			argv += 2;
		}
		else if (ft_strequ(*argv, "-"))
			argv++;
		else if (ft_strequ(*argv, "--"))
			return (argv + 1);
		else
			return (argv);
	}
	return (argv);
}

static const char	**build_new_env(t_env *env, const char **argv, int *error)
{
	int	eq_index;

	argv = apply_opt(env, argv, error);
	if (*error)
		return (argv);
	while (*argv)
	{
		eq_index = ft_strichr(*argv, '=');
		if (eq_index == 0)
		{
			*error = 1;
			investigate_error(1, NULL, "env: invalid argument", 0);
			return (argv);
		}
		else if (eq_index > 0)
			env_add_var_from_string(env, (char *)*argv, eq_index);
		else
			return (argv);
		argv++;
	}
	return (argv);
}

static int			exec_env(t_env *new_env, const char **argv)
{
	pid_t	child;
	int		ret;

	create_hash_table(&new_env->hash_table, new_env->environ);
	child = fork();
	if (child == 0)
		exit(layer_exec(new_env, (char **)argv));
	else if (child > 0)
		wait(&ret);
	return (1);
}

int					builtin_env(t_env *old_env, const char **argv)
{
	t_env	new_env;
	int		error;

	error = 0;
	if (!env_copy_env(&new_env, old_env))
		return (EXIT_FAILURE);
	argv = build_new_env(&new_env, argv + 1, &error);
	if (error)
	{
		env_free_env(&new_env);
		return (EXIT_FAILURE);
	}
	if (!(*argv))
		env_print_environ((const char**)new_env.environ);
	else
		exec_env(&new_env, argv);
	env_free_env(&new_env);
	return (EXIT_SUCCESS);
}
