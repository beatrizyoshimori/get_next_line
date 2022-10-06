/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:26:09 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/06 23:24:42 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*make_next_line(char **next_line, int rd, int fd)
{
	int		i;
	int		length;
	char	*str;
	char	*aux;

	length = ft_strlen(next_line[0]);
	i = 0;
	while (next_line[0][i] != '\n' && i < length)
		i++;
	if (next_line[0][i] == '\n' || rd < BUFFER_SIZE)
	{
		aux = ft_strdup_free(next_line[0]);
		str = ft_substr(aux, 0, i + 1);
		next_line[0] = ft_substr(aux, i + 1, length - i);
		free(aux);
		if (!next_line[0][0])
		{
			free(next_line[0]);
			next_line[0] = NULL;
		}
		return (str);
	}
	else
		str = get_next_line(fd);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*nxt_line[1024];
	int			rd;

	str = (char *)calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!str)
		return (NULL);
	rd = read(fd, str, BUFFER_SIZE);
	if (BUFFER_SIZE <= 0 || rd < 0 || (rd == 0 && ft_strlen(nxt_line[fd]) == 0))
	{
		free(str);
		return (NULL);
	}
	if (nxt_line[fd] == NULL)
		nxt_line[fd] = calloc(1, 1);
	nxt_line[fd] = ft_strjoin_free(nxt_line[fd], str);
	return (make_next_line(&nxt_line[fd], rd, fd));
}
