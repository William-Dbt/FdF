/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:32:08 by wdebotte          #+#    #+#             */
/*   Updated: 2021/12/26 17:32:44 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	size_t	i;

	if (!src && !dst)
		return (NULL);
	i = -1;
	while (++i < size)
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	return (dst);
}
