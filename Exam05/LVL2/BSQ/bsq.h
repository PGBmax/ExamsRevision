#ifndef BSQ_H
#define BSQ_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char	*raw_data;
	char	**grid;
	int		**obs_grid;
	char	obs;
	char	empty;
	char	full;
	int		he;
	int		we;
} t_map;

int		ft_strlen(const char *s);
int		is_print(char c);
int		all_unique(char a, char b, char c);
void	ft_bzero(void *dest, size_t n);
int		atoi_safe(const char *s);

void	map_error(void);
void	free_map(t_map *m);

int		parse_map(t_map *m, FILE *stream);
void	solve(t_map *m);

int		handle_map(FILE *stream);
int		main(int ac, char **av);

#endif