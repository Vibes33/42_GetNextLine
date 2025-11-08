#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

// Structure simplifiée : on garde juste ce qui reste après chaque lecture
typedef struct s_gnl
{
	char *stash; // Ce qui reste de la lecture précédente
} t_gnl;

char	*get_next_line(int fd);
char	*ft_strjoin_free(char *s1, char *s2);
char	*extract_line(char **stash);
int		has_newline(char *s);
size_t	ft_strlen(const char *s);

#endif