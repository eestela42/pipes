#ifndef PIPEX_H
# define PIPEX_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# include <sys/types.h>
# include <sys/wait.h>

char		**ft_split(const char *s, char c);

int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_strlen(char *s);
int			ft_strend_is(char *str, char *end);

void		ft_error(char *str);
void		free_comm(char **command);
#endif