/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 01:49:36 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/05 21:59:33 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_substr(char const *s, int start, int len)
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

char	*ft_strdup(char *src)
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
	return (c);
}

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (s3);
}

char    *get_next_line(int fd)
{
	//char		*buf;
	char		*str = NULL;
	char		*aux;
	static char	*next_line = 0;
	int			rd;
	int			i;

	str = (char *)calloc(BUFFER_SIZE + 1, sizeof(char));
	rd = read(fd, str, BUFFER_SIZE);
	// if (rd == 0)
	// {
	// 	free(str);
	// 	str = ft_strdup("");
	// }
	if (BUFFER_SIZE <= 0 || rd < 0 || !str || (rd == 0 && (!next_line || ft_strlen(next_line) == 0)))
	{
		free(str);
		return (NULL);
	}
	if (next_line == NULL)
		next_line = ft_strdup("");
	aux = ft_strjoin(next_line, str);
	free(str);
	free(next_line);
	next_line = ft_strdup(aux);
	free(aux);
	i = 0;
	while (next_line[i] != '\n' && next_line[i] && i < ft_strlen(next_line))
		i++;
	if (next_line[i] == '\n' || rd < BUFFER_SIZE)
	{
		str = ft_substr(next_line, 0, i + 1);
		// if (ft_strlen(str) == 0)
		// {
		// 	free(str);
		// 	//str = NULL;
		// }
		aux = ft_substr(next_line, i + 1, ft_strlen(next_line) - i);
		free(next_line);
		next_line = ft_strdup(aux);
		free(aux);
		return (str);
	}
	else
	{
		aux = get_next_line(fd);
		str = ft_strdup(aux);
		free(aux);
	}
	return (str);
}

int main(void)
{
    int fd;
	int	i;

    fd = open("teste", O_RDONLY);
	i = 0;
	while (i < 2)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
}