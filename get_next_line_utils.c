/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rydelepi <rydelepi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:53:53 by aeherve           #+#    #+#             */
/*   Updated: 2025/11/08 13:52:28 by rydelepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
	size_t i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int has_newline(char *s)
{
	int i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *ft_strjoin_free(char *s1, char *s2)
{
	char *result;
	size_t i = 0, j = 0;
	size_t len1 = ft_strlen(s1);
	size_t len2 = ft_strlen(s2);

	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	free(s1);
	return (result);
}