/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rydelepi <rydelepi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:22:30 by rydelepi          #+#    #+#             */
/*   Updated: 2025/11/08 14:16:04 by rydelepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	find_line_end(char *stash)
{
	int	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (i);
}

static char	*copy_line(char *stash, int len)
{
	char	*line;
	int		j;

	line = malloc(len + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < len)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*create_new_stash(char *stash, int start)
{
	char	*new_stash;
	int		j;

	if (!stash[start])
		return (NULL);
	new_stash = malloc(ft_strlen(stash + start) + 1);
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[start])
		new_stash[j++] = stash[start++];
	new_stash[j] = '\0';
	return (new_stash);
}

char	*extract_line(char **stash)
{
	char	*line;
	char	*new_stash;
	int		line_end;

	if (!*stash || !**stash)
		return (NULL);
	line_end = find_line_end(*stash);
	line = copy_line(*stash, line_end);
	if (!line)
		return (NULL);
	new_stash = create_new_stash(*stash, line_end);
	if (!new_stash && (*stash)[line_end])
	{
		free(line);
		return (NULL);
	}
	free(*stash);
	*stash = new_stash;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	char			buffer[BUFFER_SIZE + 1];
	ssize_t			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!has_newline(gnl.stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		gnl.stash = ft_strjoin_free(gnl.stash, buffer);
		if (!gnl.stash)
			return (NULL);
	}
	if (bytes_read < 0 || (!gnl.stash || !*gnl.stash))
	{
		free(gnl.stash);
		gnl.stash = NULL;
		return (NULL);
	}
	return (extract_line(&gnl.stash));
}
