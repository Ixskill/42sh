#include "exec.h"
#include "expand.h"
#include "builtin.h"
#include "local.h"
#include "job_control.h"

/*
**	cmd_suffix       :            io_redirect
**	                 | cmd_suffix io_redirect
**	                 |            WORD
**	                 | cmd_suffix WORD
*/

char	**exec_cmd_suffix(t_ast	*ast, t_list **redirect_list, char **av)
{
	t_ast	*io_redirect = NULL;
	t_ast	*word = NULL;
	char		**word_expanded;

	if (is_symb(ast->child[0], IO_REDIRECT))
		io_redirect = ast->child[0];
	else if (is_symb(ast->child[1], IO_REDIRECT))
		io_redirect = ast->child[1];
	if (is_token(ast->child[0], TK_WORD))
		word = ast->child[0];
	else if (is_token(ast->child[1], TK_WORD))
		word = ast->child[1];
	if (word)
	{
		word_expanded = word_expansion(word->token->value, 0);
		av = av ? ft_arrayjoin_free(word_expanded, av, 0b11) : word_expanded;
	}
	else if (io_redirect)
	{
		//av = av ? ft_arrayjoin_free(&io_redirect->heredoc, av, 0b11) : io_redirect->heredoc;
		// TODO Donne il faut cree des char ** 
		av = (char**)ft_parrnew();
		ft_parrpush((void***)&av, io_redirect->heredoc);
	}
	if (io_redirect)
		exec_io_redirect(io_redirect, redirect_list);
	if (is_symb(ast->child[0], CMD_SUFFIX))
		return (exec_cmd_suffix(ast->child[0], redirect_list, av));
	return (av);
}

/*
**	cmd_prefix       :            io_redirect
**	                 | cmd_prefix io_redirect
**	                 |            ASSIGNMENT_WORD
**	                 | cmd_prefix ASSIGNMENT_WORD
**	                 ;
*/

#include <stdio.h>
void	exec_assignment_word(t_ast *ast)
{
	char		**word_expanded;
	char		*eq_pos;
	
	eq_pos = ft_strchr(ast->token->value, '=');
	word_expanded = word_expansion(eq_pos + 1, NO_GLOBBING | NO_FIELDSPLITING);
	if (word_expanded[0])
	{
		//fprintf(stderr, "word expanded\n");
		*eq_pos = 0;
		local_add_change_from_key_value(singleton_env(), ast->token->value, word_expanded[0]);
		*eq_pos = '=';
	}
	else
	{
		//fprintf(stderr, "word expanded NULL \n");
		local_add_change_from_string(singleton_env(), ast->token->value);
	}
	//ft_arraydel(&word_expanded); //TODO: fait peter a=b
}

void	exec_cmd_prefix(t_ast *ast, t_list **redirect_list)
{
	t_ast	*assignement_word = NULL;
	t_ast	*io_redirect = NULL;

	if (is_symb(ast->child[0], IO_REDIRECT))
		io_redirect = ast->child[0];
	else if (is_symb(ast->child[1], IO_REDIRECT))
		io_redirect = ast->child[1];
	if (is_token(ast->child[0], TK_ASSIGNMENT_WORD))
		assignement_word = ast->child[0];
	else if (is_token(ast->child[1], TK_ASSIGNMENT_WORD))
		assignement_word = ast->child[1];
	if (assignement_word)
		exec_assignment_word(assignement_word);
	if (io_redirect)
		exec_io_redirect(io_redirect, redirect_list);
	if (is_symb(ast->child[0], CMD_PREFIX))
		exec_cmd_prefix(ast->child[0], redirect_list);
}

char	*extract_word(t_ast *ast)
{
	return (ft_strdup(ast->token->value));
}

char	**get_cmd_name(t_ast *ast, int flag)
{
	char 	*word = NULL;

	if (is_symb(ast->child[1], CMD_WORD))
		word = ast->child[1]->child[0]->token->value;
	else if (is_symb(ast->child[0], CMD_NAME))
		word = ast->child[0]->child[0]->token->value;
	return (word ? word_expansion(word, flag): NULL);
}

/*
**	simple_command   : cmd_prefix cmd_word cmd_suffix
**	                 | cmd_prefix cmd_word
**	                 | cmd_prefix
**	                 | cmd_name cmd_suffix
**	                 | cmd_name
*/

int		exec_simple_command(t_ast *ast)
{
	char	**av = NULL;
	char	**av_cmdsuffix = NULL;
	t_list	*redirect_list = NULL;
	t_ast	*cmd_suffix = NULL;
	t_lst_func	*fct = NULL;

	if (is_symb(ast->child[0], CMD_PREFIX))
		exec_cmd_prefix(ast->child[0], &redirect_list);
	av = get_cmd_name(ast, 0);
	if (is_symb(ast->child[1], CMD_SUFFIX))
		cmd_suffix = ast->child[1];
	if (is_symb(ast->child[2], CMD_SUFFIX))
		cmd_suffix = ast->child[2];
	if (cmd_suffix)
	{
		av_cmdsuffix = exec_cmd_suffix(cmd_suffix, &redirect_list, av_cmdsuffix);
	//	fprintf(stderr, "[%s]\n", av_cmdsuffix[1]);
		av = av ? ft_arrayjoin_free(av, av_cmdsuffix, 0b11) : av_cmdsuffix;
	}
	exec_dup(redirect_list);
	if (av && av[0])
	{
		if ((fct = get_function(singleton_env(), av[0])))
			return (exec_function(fct->fct_body, av));

		if (get_exec_builtin(av[0]))
			return (exec_builtin(singleton_env(), (const char **)av));
		exec_bin(singleton_env(), (const char **)av);
		ft_arraydel(&av);
	}
	close_dup(redirect_list);
	return (EXIT_SUCCESS);
}
