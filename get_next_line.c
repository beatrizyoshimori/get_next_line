/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 01:49:36 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/08 23:09:25 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*str;
	static char	*next_line;
	int			rd;
	int			i;

	str = (char *)calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!str)
		return (NULL);
	rd = read(fd, str, BUFFER_SIZE);
	if (BUFFER_SIZE < 1 || rd < 0 || (rd == 0 && ft_strlen(next_line) == 0))
		return (free(str), NULL);
	if (next_line == NULL)
		next_line = calloc(1, 1);
	next_line = ft_strjoin_free(next_line, str);
	i = 0;
	while (next_line[i] != '\n' && next_line[i] != '\0')
		i++;
	if (next_line[i] == '\n' || rd < BUFFER_SIZE)
	{
		str = ft_strdup(next_line);
		next_line = ft_substr_free(next_line, i + 1, ft_strlen(next_line) - i);
		return (ft_substr_free(str, 0, i + 1));
	}
	return (get_next_line(fd));
}
