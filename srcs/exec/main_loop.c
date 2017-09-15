#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#define LOCAL_BUFF_SIZE 4096

#ifdef PARSER_DEBUG
# ifdef OUT
static void	read_tree(t_ast *ast_start)
{
	size_t	index;
	t_token	*token_parent;
	char	*parent_name;
	t_list	*first_child;

	index = 0;
	token_parent = ast_start->token;
	printf(GRN"NODE = "RESET);
	if (token_parent)
		parent_name = token_parent->value;
	else
	{
		if (ast_start->symbol == SIMPLE_COMMAND)
			parent_name = "SIMPLE_COMMAND";
		if (ast_start->symbol == IO_REDIRECT)
			parent_name = "IO_REDIRECT";
	}
	printf(MAG"#"CYN"%s"MAG"#"RESET""YEL"(%d)\n"RESET, parent_name,
			ast_start->symbol);
	first_child = ast_start->child;
	while (first_child)
	{
		printf(RED"Starting treatment of child nb "BLU"%zu"RESET" of parent"
				MAG"#"CYN"%s"MAG"#"YEL"(%d)\n"RESET, index, parent_name, \
				ast_start->symbol);
		if (first_child->data)
			read_tree(first_child->data);
		printf(PNK"\nBACK TO PARENT -> "RESET"Current node = "CYN"%s"RESET" !!!\n", parent_name);
		first_child = first_child->next;
		index++;
	}
}
# endif
#endif

/*
**	Receives an array containing the command name and its arguments.
*/

void	exec(t_env *env, const char **argv, t_lst_head *head)
{
	size_t		index;

	index = 0;
	if (*argv != NULL)
	{
		if (!(exec_builtin(env, argv, head)))
			fork_exec_bin(env, argv, head);
	}
	else
		env->previous_exit = EXIT_FAILURE;
	while (argv[index] != NULL)
	{
		free((void*)(argv[index]));
		index++;
	}
	free(argv);
}
#ifndef NO_TERMCAPS
void	init_main_loop(t_line *line, t_hist *hist)
{
	(void)hist;
	line->len = 0;
	line->pos = 0;
	line->visu_mode = 0;
	line->copied_text = NULL;
	line->ws_col = get_ws_col();
	line->buff = ft_strnew(BUFF_LINE_SIZE);
	env_add_change(singleton_env(), "PS1", "$> ");
	env_add_change(singleton_env(), "PS2", "dquote> ");
	env_add_change(singleton_env(), "PS3", "quote> ");
	line->size = BUFF_LINE_SIZE;
	load_prompt(singleton_env(), line, "PS1", "$> ");
	line->heredoc = 0;
}

char	*line_editing_get_input(t_line *line, t_hist *hist)
{
	put_prompt(line);
	history_init(hist);
	edit_line_init(line);
	return (edit_get_input());
}
#endif

void	history_write_last_command();	// PROTO

void	main_loop(t_env *env)
{
	t_ast		*ast;
	char		*buff;
	t_lexer		lex;
	t_lst_head	*head = NULL;
	t_list		*token_list;

	init_main_loop(singleton_line(), singleton_hist());
	while (42)
	{
		load_prompt(env, singleton_line(), "PS1", "$> ");
		buff = ft_strdup(line_editing_get_input(singleton_line(), singleton_hist()));
		if (*buff != 0)
		{
			history_refresh(buff);
			buff = ft_strchange(buff, ft_strjoin(buff, "\n"));
			lex = init_lexer(buff);
			token_list = start_lex(&lex);
			ast = ast_parse(NULL, &token_list, &head);
			history_write_last_command();
			conf_term_normal();
			exec_tree(ast, head);
			if (token_list)
				ft_simple_lst_remove(&token_list, free_token);
			conf_term_canonical();
			ast = flush_tree(ast);
			if (head != NULL)
				ft_remove_head(&head, free_pipe);
			free(buff);
		}
		else
			free(buff);
	}
}
