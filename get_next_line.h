/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rydelepi <rydelepi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:59:40 by rydelepi          #+#    #+#             */
/*   Updated: 2025/11/08 14:04:32 by rydelepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1234
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_gnl
{
	char	*stash;
}	t_gnl;

char	*get_next_line(int fd);
char	*ft_strjoin_free(char *s1, char *s2);
char	*extract_line(char **stash);
int		has_newline(char *s);
size_t	ft_strlen(const char *s);

#endif