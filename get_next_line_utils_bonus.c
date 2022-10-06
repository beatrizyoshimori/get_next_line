/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:29:21 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/06 23:25:15 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s != NULL && s[length])
		length++;
	return (length);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	j;
	void	*t;

	if (size == 0 || nmemb == 0 || nmemb >= 2147483647 / size)
		return (NULL);
	i = nmemb * size;
	t = malloc(i);
	j = 0;
	while (j < i)
	{
		((unsigned char *)t)[j] = '\0';
		j++;
	}
	return (t);
}

char	*ft_strdup_free(char *src)
{
	int		i;
	int		length;
	char	*c;

	length = ft_strlen(src);
	if (!src)
		return (NULL);
	c = (char *)malloc((length + 1) * sizeof(char));
	if (c == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		c[i] = src[i];
		i++;
	}
	c[i] = '\0';
	free(src);
	return (c);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*sub;

	if (start > ft_strlen(s))
		sub = malloc(1);
	else if (len < ft_strlen(s))
		sub = malloc(len + 1);
	else
		sub = malloc(ft_strlen(s) - start + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	if (start <= ft_strlen(s))
	{
		while (s[start] && i < len)
		{
			sub[i] = s[start];
			i++;
			start++;
		}
	}
	sub[i] = '\0';
	return (sub);
}

// char	*ft_substr_free(char *s, int start, int len)
// {
// 	int		i;
// 	char	*sub;

// 	if (start > ft_strlen(s))
// 		sub = malloc(1);
// 	else if (len < ft_strlen(s))
// 		sub = malloc(len + 1);
// 	else
// 		sub = malloc(ft_strlen(s) - start + 1);
// 	if (sub == NULL)
// 		return (NULL);
// 	i = 0;
// 	if (start <= ft_strlen(s))
// 	{
// 		while (s[start] && i < len)
// 		{
// 			sub[i] = s[start];
// 			i++;
// 			start++;
// 		}
// 	}
// 	sub[i] = '\0';
// 	free(s);
// 	return (sub);
// }

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s3[i] = s2[j];
		j++;
		i++;
	}
	s3[i] = '\0';
	free(s1);
	free(s2);
	return (s3);
}
