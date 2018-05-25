/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_token.h"
#include "lexer.h"

/*
**	Creates a token, allocating memory for it and the string it contains,
**	storing many infos about the token.
*/

t_token	*create_token(const char *source, struct s_info *info, size_t end_index)
{
	t_token		*token;

	token = ft_memalloc(sizeof(*token) * 1);
	token->value = ft_strdup(info->value.str);
	token->delim = source[end_index];
	token->state_info = info;
	token->id = 0;
	token->cmd_name = 0;
	return (token);
}

t_token	*dup_token(t_token *original)
{
	t_token	*new;

	new = ft_memalloc(sizeof(t_token));
	new->state_info = create_state_info();
	copy_state_info(original->state_info, new->state_info);
	new->value = ft_strdup(original->value);
	new->delim = original->delim;
	new->id = original->id;
	return (new);
}

void	free_token(void *value)
{
	t_token *token;

	if (!value)
		return ;
	token = (t_token*)value;
	free(token->value);
	free_info(token->state_info);
	free(token);
}
