/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommehdiz <ommehdiz@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:02:47 by jotavare          #+#    #+#             */
/*   Updated: 2024/09/04 14:19:04 by ommehdiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (dest);
	d = dest;
	s = src;
	while (n > 0)
	{
		*d++ = *s++;
		n--;
	}
	return (dest);
}

/*int main()
{
	char	str[] = "Vou ser copiado.";
	char	dest[18];
	ft_putstr_fd(ft_memcpy(dest, str, 18), 1);
	ft_putchar_fd('\n', 1);
}*/
