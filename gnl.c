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
    static char     *next_line = 0;
    int             rd;
    int             bytes;
    int             i;

    printf("next_line1: %s\n", next_line);
    bytes = 5;
    rd = read(fd, buf, bytes);
    printf("buf: %s\n", buf);
    i = 0;
    while (i < bytes)
    {
        if (buf[i] == '\n')
            break ;
        i++;
    }
    str = malloc(i);
    ft_strlcpy(str, buf, i);
    printf("str: %s\n", str);
    if (next_line != 0)
    {
        aux = ft_strjoin(next_line, str);
        printf("aux: %s\n", aux);
    }
    if (i < bytes)
        next_line = &buf[i];
    else
    {
        next_line = buf;
        printf("next_line: %s\n", next_line);
        get_next_line(fd);
    }
    return (aux);
}

int main(void)
{
    int fd;

    fd = open("teste", O_RDONLY);
    printf("%s\n", get_next_line(fd));
}