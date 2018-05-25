/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_construct_prompt.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:41 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdio.h>

struct s_token_to_prompt	g_token_to_prompt[] =
{
	{TK_PIPE, "pipe"},
	{TK_AND_IF, "cmdand"},
	{TK_OR_IF, "cmdor"},
	{TK_IF, "if"},
	{TK_THEN, "then"},
	{TK_ELSE, "else"},
	{TK_ELIF, "elif"},
	{TK_CASE, "case"},
	{TK_WHILE, "while"},
	{TK_UNTIL, "until"},
	{TK_FOR, "for"},
	{TK_LBRACE, "cursh"},
	{TK_LPAREN, "subsh"},
	{-1, NULL},
};

char			*token_to_prompt(int token_id)
{
	int	i;

	i = 0;
	while (g_token_to_prompt[i].string)
	{
		if (token_id == g_token_to_prompt[i].id)
			return (g_token_to_prompt[i].string);
		i++;
	}
	return (NULL);
}

static char		*beginoftheloop(t_ast_lst **tmp, int *token_next_id)
{
	int			token_id;

	token_id = -1;
	if ((*tmp)->ast->token)
		token_id = (*tmp)->ast->token->id;
	if ((*tmp)->next && (*tmp)->next->ast->token)
		*token_next_id = (*tmp)->next->ast->token->id;
	if (token_id == TK_RPAREN && *token_next_id == TK_LPAREN)
	{
		(*tmp) = (*tmp)->next;
		return ("function");
	}
	return (token_to_prompt(token_id));
}

char			*parser_construct_prompt(t_ast_lst *ast_stack)
{
	int			token_next_id;
	char		*prompt;
	char		*token_prompt;
	t_ast_lst	*tmp;

	prompt = NULL;
	tmp = ast_stack;
	while (tmp)
	{
		token_prompt = beginoftheloop(&tmp, &token_next_id);
		if (token_prompt)
		{
			if (!prompt)
				prompt = ft_strdup(token_prompt);
			else
				prompt = ft_strjoin3_free(token_prompt, " ", prompt, 1);
		}
		tmp = tmp->next;
	}
	return (prompt);
}
