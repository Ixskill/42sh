/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:58 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "printf.h"
#include "libft.h"

static struct s_debug_token_id g_debug_token_id[] =
{
	{TK_WORD, "TK_WORD" },
	{TK_ASSIGNMENT_WORD, "TK_ASSIGNMENT_WORD" },
	{TK_NAME, "TK_NAME" },
	{TK_NEWLINE, "TK_NEWLINE" },
	{TK_IO_NUMBER, "TK_IO_NUMBER" },
	{TK_LESS, "TK_LESS" },
	{TK_GREAT, "TK_GREAT" },
	{TK_SEMI, "TK_SEMI" },
	{TK_PIPE, "TK_PIPE" },
	{TK_AND, "TK_AND" },
	{TK_AND_IF, "TK_AND_IF" },
	{TK_OR_IF, "TK_OR_IF" },
	{TK_DSEMI, "TK_DSEMI" },
	{TK_DLESS, "TK_DLESS" },
	{TK_DGREAT, "TK_DGREAT" },
	{TK_LESSAND, "TK_LESSAND" },
	{TK_GREATAND, "TK_GREATAND" },
	{TK_LESSGREAT, "TK_LESSGREAT" },
	{TK_DLESSDASH, "TK_DLESSDASH" },
	{TK_CLOBBER, "TK_CLOBBER" },
	{TK_IF, "TK_IF" },
	{TK_THEN, "TK_THEN" },
	{TK_ELSE, "TK_ELSE" },
	{TK_ELIF, "TK_ELIF" },
	{TK_FI, "TK_FI" },
	{TK_DO, "TK_DO" },
	{TK_DONE, "TK_DONE" },
	{TK_CASE, "TK_CASE" },
	{TK_ESAC, "TK_ESAC" },
	{TK_WHILE, "TK_WHILE" },
	{TK_UNTIL, "TK_UNTIL" },
	{TK_FOR, "TK_FOR" },
	{TK_LBRACE, "TK_LBRACE" },
	{TK_RBRACE, "TK_RBRACE" },
	{TK_BANG, "TK_BANG" },
	{TK_LPAREN, "TK_LPAREN" },
	{TK_RPAREN, "TK_RPAREN" },
	{TK_IN, "TK_IN" },
	{DOLAR, "DOLAR"},
	{-1, NULL}
};

void	debug_token(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
	{
		ft_dprintf(1, "token not found\n");
		return ;
	}
	while (g_debug_token_id[i].name)
	{
		if (token->id == g_debug_token_id[i].id)
		{
			ft_dprintf(1, "%s\n", g_debug_token_id[i].name);
			return ;
		}
		i++;
	}
}
