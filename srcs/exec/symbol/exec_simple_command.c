/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:10 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include "expand.h"
#include "builtin.h"
#include "failure.h"
#include "local.h"
#include "exec.h"
#include "job_control.h"

char			*extract_word(t_ast *ast)
{
	return (ft_strdup(ast->token->value));
}

char			**get_cmd_name(t_ast *ast, int flag)
{
	char	*word;

	word = NULL;
	if (is_symb(ast->child[1], CMD_WORD))
		word = ast->child[1]->child[0]->token->value;
	else if (is_symb(ast->child[0], CMD_NAME))
		word = ast->child[0]->child[0]->token->value;
	return (word ? word_expansion(word, flag) : NULL);
}

/*
**	simple_command   : cmd_prefix cmd_word cmd_suffix
**	                 | cmd_prefix cmd_word
**	                 | cmd_prefix
**	                 | cmd_name cmd_suffix
**	                 | cmd_name
*/

static int		layer_command_suffix(t_ast *ast, char ***av, \
	t_list **redirect_list)
{
	t_ast	*cmd_suffix;
	char	**av_cmdsuffix;

	cmd_suffix = NULL;
	av_cmdsuffix = NULL;
	*av = get_cmd_name(ast, 0);
	if (is_symb(ast->child[1], CMD_SUFFIX))
		cmd_suffix = ast->child[1];
	if (is_symb(ast->child[2], CMD_SUFFIX))
		cmd_suffix = ast->child[2];
	if (cmd_suffix)
	{
		if (!exec_cmd_suffix(cmd_suffix, redirect_list, &av_cmdsuffix))
			return (EXIT_FAILURE);
		if (av_cmdsuffix)
			*av = *av ? ft_arrayjoin_free(*av, av_cmdsuffix, 0b11) : \
				av_cmdsuffix;
	}
	return (EXIT_SUCCESS);
}

int				exec_simple_command(t_ast *ast)
{
	char	**av;
	t_list	*redirect_list;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	redirect_list = NULL;
	av = NULL;
	if (is_symb(ast->child[0], CMD_PREFIX))
	{
		if (!(exec_cmd_prefix(ast->child[0], &redirect_list)))
			return (EXIT_FAILURE);
	}
	if (layer_command_suffix(ast, &av, &redirect_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exec_dup(redirect_list);
	if (av && av[0])
		exit_status = layer_exec(singleton_env(), av);
	ft_arraydel(&av);
	close_dup(redirect_list);
	return (exit_status);
}
