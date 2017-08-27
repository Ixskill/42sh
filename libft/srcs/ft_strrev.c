/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:13:14 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:14:49 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if ((new_str = ft_strnew(ft_strlen(str) + 1)) == NULL || str == NULL)
		return (NULL);
	i = ft_strlen(str);
	j = 0;
	while (i > 0)
		new_str[j++] = str[--i];
	return (new_str);
}
