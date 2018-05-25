/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "local.h"

static int	valid_param_expansion(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '(' && str[i + 1] != '{')
		{
			if (str[i + 1] == 0)
				return (-1);
			return (i);
		}
		i++;
	}
	return (-1);
}

static char	*expand_from_env(t_env *env, char *key, int offset)
{
	char	*param;
	char	*ret;

	param = local_get_var(env->local, key + offset + 1);
	if (param)
		ret = ft_strdup(param);
	else
		ret = ft_strnew(0);
	return (ret);
}

void		parameter_expansion(t_env *env, t_token *token)
{
	char	**split;
	int		offset;
	char	*result;
	size_t	i;

	i = 0;
	if ((offset = valid_param_expansion(token->value)) != -1)
	{
		result = ft_strnew(0);
		split = ft_strsplit_keep(token->value, WHITESPACES"/");
		while (split[i])
		{
			if ((offset = valid_param_expansion(split[i])) != -1)
				split[i] = ft_strchange(split[i], \
						expand_from_env(env, split[i], offset));
			result = ft_strchange(result, ft_strjoin(result, split[i]));
			free(split[i]);
			i++;
		}
		free(split);
		token->value = ft_strchange(token->value, result);
	}
}
