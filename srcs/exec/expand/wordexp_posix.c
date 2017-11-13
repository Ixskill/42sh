#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "environ.h"
#include "exec.h"
#include "local.h"
#include "glob.h"
#include "expand.h"

static char **list_to_array(t_list *lst)
{
	size_t	n;
	char	**res;
	int		i;
	
	n = ft_lst_len(lst);
	res = ft_memalloc(sizeof(char *) * (n + 1));
	i = 0;
	while (lst)
	{
		res[i] = (char *)lst->data;
		lst = lst->next;
		i++;
	}
	return (res);
}

static char	**pathname_expension(t_expand *exp)
{
	t_list	*match_list;
	size_t		i;
	char	*no_match[2];
	char	**matches;
	char	**av = ft_memalloc(sizeof(char *) * (1));

	no_match[1] = NULL;
	i = 0;
	while (i < exp->actlen)
	{
		match_list = glob(exp->av_gword[i]);
		if (match_list)
		{
			matches = list_to_array(match_list);
			av = ft_arrayjoin_free(av, matches, 0b11);
			ft_simple_lst_remove(&match_list, NULL);
			ft_strdel(&exp->av_word[i]);
			ft_strdel(&exp->av_gword[i]);
		}
		else
		{
			no_match[0] = exp->av_word[i];
			av = ft_arrayjoin_free(av, no_match, 0b10);
			ft_strdel(&exp->av_gword[i]);
		}
		i++;
	}
	free(exp->av_gword);
	free(exp->av_word);
	return (av);
}

static char	**brace_expension(const char *words)
{
	t_list	*match_list;
	char	**matches;

	match_list = expand_curly_brackets((char *)words);
	if (match_list)
	{
		matches = list_to_array(match_list);
		ft_simple_lst_remove(&match_list, NULL);
	}
	else
	{
		//fprintf(stderr,"match list null\n");
		matches = ft_memalloc(sizeof(char *) * (2));
		matches[0] = ft_strdup(words);
	}
	return (matches);
}

static int		parse_loop (const char *words, t_expand *exp, const char *ifs)
{
	size_t	offset;
	t_word	word;
	t_word	g_word;

	w_newword (&word);
	w_newword (&g_word);
	offset = 0;
	while (words[offset])
	{
		if (words[offset] == '\\')
			parse_backslash (&g_word, &word, words, &offset);
		else if (words[offset] == '"')
		{
			++offset;
			parse_dquote (&g_word, &word, words, &offset, exp, ifs);
			if (!word.str && !words[1 + offset])
				w_addword (exp, &g_word, &word);
		}
		else if (words[offset] == '\'')
		{
			++offset;
			parse_squote (&g_word, &word, words, &offset);
			if (!word.str && !words[1 + offset])
				w_addword (exp, &g_word, &word);
		}
		else if (words[offset] == '`')
		{
			++offset;
			parse_backtick (&g_word, &word, words, &offset, exp, ifs, 0);
		}
		else if (words[offset] == '$')
			parse_dollars (&g_word, &word, words, &offset, exp, ifs, 0);
		else if (words[offset] == '~')
			parse_tilde (&g_word, &word, words, &offset);
		else
		{
			//	fprintf(stderr,"w: {%s}, gw: {%s}\nwsize: {%zu}, gwsize: {%zu}\n", word.str, g_word.str, word.actlen, g_word.actlen);
			//	fprintf(stderr,"wsize max: {%zu}, gwsize max: {%zu}\n", word.maxlen, g_word.maxlen);
			w_addchar (&word, words[offset]);
			w_addchar (&g_word, words[offset]);
		}
		offset++;
	}
	if (word.str != NULL)
		w_addword (exp, &g_word, &word);
	return (0);
}

char	**word_expansion (const char *words, int flag) // NO_GLOBING | NO_FIELD_SPLITTING
{
	char *ifs;
	char	**braced_words;
	t_expand exp;
	size_t i;
	(void)flag;
	w_newexp (&exp);

	ifs = var_get_value (singleton_env(), "IFS");
	if (ifs == NULL)
		ifs = ft_strdup(" \t\n");

	braced_words = brace_expension(words);
	i = 0;
	while (braced_words[i])
	{
		parse_loop (braced_words[i], &exp, ifs);
		i++;
	}
	//for (i=0; i < exp.actlen; i++)
		//fprintf(stderr,"w: {%s}, gw: {%s}\n", exp.av_word[i], exp.av_gword[i]);
	free(ifs);
	if (!(flag & NO_GLOBBING))
		return (pathname_expension(&exp));
	ft_arraydel(&exp.av_gword);
	return (exp.av_word);
}
