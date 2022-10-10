/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:26:09 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/08 23:03:05 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*str;
	static char	*next_line[1024];
	int			rd;
	int			i;

	str = (char *)calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!str)
		return (NULL);
	rd = read(fd, str, BUFFER_SIZE);
	if (BUFFER_SIZE < 1 || rd < 0 || (rd == 0 && ft_strlen(next_line[fd]) == 0))
		return (free(str), NULL);
	if (next_line[fd] == NULL)
		next_line[fd] = calloc(1, 1);
	next_line[fd] = ft_strjoin_free(next_line[fd], str);
	i = 0;
	while (next_line[fd][i] != '\n' && next_line[fd][i] != '\0')
		i++;
	if (next_line[fd][i] == '\n' || rd < BUFFER_SIZE)
	{
		str = ft_strdup(next_line[fd]);
		next_line[fd] = ft_substr_free(next_line[fd], \
						i + 1, ft_strlen(next_line[fd]) - i);
		return (ft_substr_free(str, 0, i + 1));
	}
	return (get_next_line(fd));
}
