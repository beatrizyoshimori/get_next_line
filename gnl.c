#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

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

char    *get_next_line(int fd)
{
    char            *buf;
    char            *str;
    char            *aux;
    char            *tmp;
    static char     *next_line = 0;
    int             rd;
    int             bytes;
    int             i;

    //printf("next_line1: %s\n", next_line);
    bytes = 5;
    buf = malloc(bytes);
    rd = read(fd, buf, bytes);
    if (rd <= 0)
        return (NULL);
    //printf("buf: %s\n", buf);
    i = 0;
    while (i < bytes)
    {
        if (buf[i] == '\n')
            break ;
        i++;
    }
    if (rd < bytes)
        i = rd;
    printf("i: %d\n", i);
    if (i < bytes)
    {
        str = ft_strjoin(next_line, ft_substr(buf, 0, i));
        aux = ft_strdup(next_line);
        next_line = ft_substr(buf, i + 1, bytes - i);
        printf("line: %s\n", str);
        //printf("next_line: %s\n", next_line);
    }
    else
    {
        aux = ft_strdup(next_line);
        next_line = ft_strjoin(aux, buf);
        //printf("next_line(else): %s\n", next_line);
        str = ft_strjoin(buf, get_next_line(fd));
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
}