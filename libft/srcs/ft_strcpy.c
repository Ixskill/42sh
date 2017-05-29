/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:01:21 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/28 17:37:38 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"
#include "mem.h"

static void	align_memory(char **dst, unsigned char **src)
{
	while (**src && (((t_ulong)*dst & (ULONG_SIZE - 1)) != 0))
	{
		**dst = **src;
		(*dst)++;
		(*src)++;
	}
}

static void	cpy_last_bits(char *dst, char *src)
{
	while (*src != 0)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = *src;
}

char	*ft_strcpy(char *dst, const char *src)
{
	char	*origin;
	t_ulong	*src_ptr;
	t_ulong	*dst_ptr;

	origin = dst;
	align_memory(&dst, (unsigned char**)&src);
	if (*src == 0)
	{
		*dst = 0;
		return(origin);
	}
	src_ptr = (t_ulong*)src;
	dst_ptr = (t_ulong*)dst;
	while (42)
	{
		if (HAS_ZERO((*src_ptr)))
		{
			cpy_last_bits((char*)dst_ptr, (char*)src_ptr);
			return (origin);
		}
		else
			*dst_ptr++ = *src_ptr++;
	}
	return (NULL);
}
