/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 01:49:36 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/06 23:22:50 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*make_next_line(char **next_line, int rd, int fd)
{
	int		i;
	//int		length;
	char	*str;

	//length = ft_strlen(next_line[0]);
	i = 0;
	while (next_line[0][i] != '\n' && next_line[0][i] != '\0')
		i++;
	if (next_line[0][i] == '\n' || rd < BUFFER_SIZE)
	{
		str = ft_strdup(next_line[0]);
		//str = ft_substr_free(str, 0, i + 1);
		next_line[0] = ft_substr_free(next_line[0], i + 1, ft_strlen(next_line[0]) - i);
		// if (!next_line[0][0])
		// {
		// 	free(next_line[0]);
		// 	next_line[0] = NULL;
		// }
		return (ft_substr_free(str, 0, i + 1));
	}
	else
		str = get_next_line(fd);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*next_line;
	int			rd;

	str = (char *)calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!str)
		return (NULL);
	rd = read(fd, str, BUFFER_SIZE);
	if (BUFFER_SIZE <= 0 || rd < 0 || (rd == 0 && ft_strlen(next_line) == 0))
		return (free(str), NULL);
	// if (next_line == NULL)
	// 	next_line = calloc(1, 1);
	next_line = ft_strjoin_free(next_line, str);
	return (make_next_line(&next_line, rd, fd));
}

// int main(void)
// {
//     int fd;
// 	int	i;
// 	char	*str;

//     fd = open("teste", O_RDONLY);
// 	i = 0;
// 	while (i < 2)
// 	{
// 		str = get_next_line(fd);
// 		printf("%s", str);
// 		free(str);
// 		i++;
// 	}
// }