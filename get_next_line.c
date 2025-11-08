/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rydelepi <rydelepi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:22:30 by rydelepi          #+#    #+#             */
/*   Updated: 2025/11/08 13:52:26 by rydelepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *extract_line(char **stash)
{
	char *line;
	char *new_stash;
	int i = 0;

	if (!*stash || !**stash)
		return (NULL);
		
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;

	if ((*stash)[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);

	int j = 0;
	while (j < i)
	{
		line[j] = (*stash)[j];
		j++;
	}
	line[j] = '\0';

	if ((*stash)[i])
	{
		new_stash = malloc(ft_strlen(*stash + i) + 1);
		if (!new_stash)
		{
			free(line);
			return (NULL);
		}
		j = 0;
		while ((*stash)[i])
			new_stash[j++] = (*stash)[i++];
		new_stash[j] = '\0';
	}
	else
		new_stash = NULL;

	free(*stash);
	*stash = new_stash;
	return (line);
}


char *get_next_line(int fd)
{
	static t_gnl gnl;
	char buffer[BUFFER_SIZE + 1];
	ssize_t bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	while (!has_newline(gnl.stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break;
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