#include "libft.h"
#include "lexer.h"

struct s_lex_action g_lex_action[] = 
{
	{DEFAULT, &lex_action_default},
	{WORD, &lex_action_word},
	{WHITESPACE, &lex_action_whitespace},
	{QUOTES, &lex_action_quotes},
	{DQUOTES, &lex_action_dquotes},
	{BS, &lex_action_bs},
	{OPERATOR, &lex_action_operator},
	{NEWLINE, &lex_action_newline},
	{COMMENT, &lex_action_comment},
	{PARAM_EXP, &lex_action_param_exp},
	{CMD_SUBST, &lex_action_cmd_subst},
};

/*
**	PARAMS:
**		lex is the address of an existing lexer.
**
**	RETVAL:
**		If a token is created, returns the created token.
**		Otherwise (error, nothing to lex) return NULL.
*/

/*
** LOCAL_VAR:
** 		state_info is a cache. The last token or minitoken we delimited is storred.
**	Cycle of life :
**	Step 1 = Delimitation automata.
**		- Find the set of possible actions corresponding to the current state.
**		- Within this set, find the exact action corresponding to the given input.
**		- Work is done when we came back to our original state and the last state we poped was complete (has an end defined).
**	During delimitation of a token, we may enter different states, and delimit "mini-tokens".
**	Step 2 = Token creation followed by token identification
*/

/*
**	In the natural flow, every new_value of state_info frees the precent one,
**	and the very last one is kept and used. If unnatural stop occurs, the last
**	value is not used, and must be freed manually.
*/

/*
**	Returning function pointer is tricky ...
*/

#include <stdio.h>

static int	(*get_action(ssize_t state))(t_lexer *, ssize_t **)
{
	size_t	i;

	i = 0;
	while (g_lex_action[i].state != state)
		++i;
#ifdef LEXER_DEBUG
	/* dprintf(2, "Get action returned action %ld\n", g_lex_action[i].state);//			REMOVE */		
#endif
	return (g_lex_action[i].func);
}

t_token	*get_token(t_lexer *lex)
{
	/* INIT */
	ssize_t	*state_info;
	t_token	*token;
	int		ret;

	ret = TRUE;
	token = NULL;
	state_info = NULL;

	/* DELIM */
	while (ret && !(state_info && state_info[_T_END] != -1 && ((ssize_t*)lex->state->data)[_T_STATE] == DEFAULT))
		ret = get_action(((ssize_t*)lex->state->data)[_T_STATE])(lex, &state_info);

	/* Check for errors */
	if (((ssize_t*)lex->state->data)[_T_STATE] == DEFAULT) /* If everything is ok, TOKENIZE */
	{
		token = create_token(lex->line, state_info);
		get_token_id(lex, token);
	}
	else
		free(state_info);
	return (token);
}
