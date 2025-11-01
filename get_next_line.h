#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl_v
{
	char		*line;
	char		*buffer;
	size_t		c_end; // dernier nn nul
	size_t		c_treated;
	size_t		c_endline; // premier nn traite
} t_gnl_v;

char				*ft_strdup(char *s1);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2);
static char			*_fill_line_buffer(int fd, char *left_c, char *buffer);
static char			*_set_line(char *line);
char				*get_next_line(int fd);
size_t				ft_strlen(const char *str);

#endif