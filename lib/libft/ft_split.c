/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:10:34 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:10:36 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != (unsigned char) c
			&& (s[i + 1] == (unsigned char) c || !s[i + 1]))
		{
			count++;
		}
		i++;
	}
	return (count);
}

static char	**ft_dispose_arr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (NULL);
}

static char	**ft_fill_arr(char **arr, char const *s, char c)
{
	int	i;
	int	j;
	int	ai;

	i = 0;
	ai = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			arr[ai] = ft_substr(s, j, i - j);
			if (arr[ai] == NULL)
				return (ft_dispose_arr(arr, ai));
			ai++;
		}
	}
	arr[ai] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = (char **) malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (ft_fill_arr(arr, s, c));
}
