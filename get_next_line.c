/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 01:49:36 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/04 02:58:55 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s != NULL && s[length])
		length++;
	return (length);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
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

char	*ft_strdup(const char *src)
{
	int		i;
	int		length;
	char	*c;

	length = ft_strlen(src);
	c = malloc(length + 1);
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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size < 0)
		dst[ft_strlen(src) + 1 + size] = '\0';
	i = 0;
	if (size != 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(1, "\n", 1);
}

char    *get_next_line(int fd)
{
    char            *buf;
    char            *str = NULL;
    char            *aux;
    static char     *next_line = 0;
    int             rd;
    int             i;

    //printf("next_line1: %s\n", next_line);
    buf = malloc(BUFFER_SIZE);
    rd = read(fd, buf, BUFFER_SIZE);
    //printf("rd: %d\n", rd);
	if (next_line == NULL)
		next_line = ft_strdup("");
    // printf("buf: %s\n", buf);
    if (rd == 0)
    {
        if (ft_strlen(next_line) != 0)
		{
			printf("if(rd0): ");
			ft_putstr_fd(next_line, 1);
			return (next_line);
        }
		ft_putstr_fd("(null)", 1);
        return (str);
    }
    i = 0;
    while (i < rd)
    {
        if (buf[i] == '\n')
            break ;
        i++;
    }

	printf("i: %d\n", i);
    // if (rd < bytes)
    //     i = rd;
    if (buf[i] == '\n')
    {
        str = ft_strjoin(next_line, ft_substr(buf, 0, i));
        //aux = ft_strdup(next_line);
        next_line = ft_substr(buf, i + 1, BUFFER_SIZE - i);
		printf("if:");
		printf("str: %s\n", str);
		printf("next_line: %s\n*", next_line);
        ft_putendl_fd(str, 1);
		if (ft_strlen(next_line) != 0)
			get_next_line(fd);
        //printf("next_line: %s\n", next_line);
		return (str);
    }
    else
    {
        aux = ft_strdup(next_line);
        next_line = ft_strjoin(aux, buf);
        //printf("next_line(else): %s\n", next_line);
        str = ft_strdup(get_next_line(fd));
        //printf("line(else): %s\n", str);
    }
    return (str);
    // str = ft_strjoin(next_line, buf);
    // //ft_strlcpy(str, buf, i + 1);
    // printf("str: %s\n", str);
    // if (next_line != 0)
    // {
    //     aux = ft_strjoin(next_line, str);
    //     printf("aux: %s\n", aux);
    // }
    // if (i < bytes)
    //     next_line = &buf[i];
    // else
    // {
    //     next_line = buf;
    //     printf("next_line: %s\n", next_line);
    //     get_next_line(fd);
    // }
    // return (aux);
}

int main(void)
{
    int fd;

    fd = open("teste", O_RDONLY);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    //get_next_line(fd);
}