/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 01:40:22 by byoshimo          #+#    #+#             */
/*   Updated: 2022/10/06 23:25:38 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int		ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strdup(char *src);
//char	*ft_substr(char *s, int start, int len);
char	*ft_substr_free(char *s, int start, int len);

#endif