#include "line_editing.h"
#include "failure.h"
#include "t_lexer.h"
#include "history.h"
#include "exec.h"
#include "lexer.h"

void		reopen_line_editing(t_lexer *lex, int res_lexer, int res_parser)
{
	char	*new_command;

	printf("reopen line editing: res_lexer = %d, res_parser = %d\n", res_lexer, res_parser);
	printf("tk_and %d\n", TK_AND);
	if (res_parser == TK_PIPE)
		load_prompt(singleton_env(), singleton_line(), NULL, "pipe> ");
	else if (res_parser == TK_AND_IF)
		load_prompt(singleton_env(), singleton_line(), NULL, "cmdand> ");
	else if (res_parser == TK_OR_IF)
		load_prompt(singleton_env(), singleton_line(), NULL, "cmdor> ");
	else if (res_lexer == '"')
		load_prompt(singleton_env(), singleton_line(), "PS2", "dquote> ");
	else if (res_lexer == '\'')
		load_prompt(singleton_env(), singleton_line(), "PS3", "quote> ");
	new_command = ft_strdup(line_editing_get_input(singleton_line(), \
			singleton_hist(), &edit_set_signals_reopen));
	lex->line = ft_strchange((char*)lex->line, \
			ft_strjoin((char*)lex->line, new_command));
	free(new_command);
}
