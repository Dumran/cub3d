/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:11:20 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:11:22 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*buf;
	size_t	i;

	buf = ft_strdup(s);
	if (!buf)
		return (NULL);
	i = 0;
	while (buf[i])
	{
		buf[i] = f(i, buf[i]);
		i++;
	}
	return (buf);
}
