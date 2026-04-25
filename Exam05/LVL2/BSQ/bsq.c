#include "bsq.h"

int	ft_strlen(const char *s) {
	int	len = 0;
	while (*s++) ++len;
	return len;
}

int	is_print(char c) { return c >= 32 && c <= 126; }
int	all_unique(char a, char b, char c) { return !(a == b || a == c || b == c); }

void	ft_bzero(void *dest, size_t n) {
	unsigned char	*d = dest;
	for (size_t i = 0; i < n; ++i) d[i] = 0;
}

int	atoi_safe(const char *s) {
	int	res = 0, prev = -1;
	while (*s) {
		if (*s >= '0' && *s <= '9') {
			res = res * 10 + (*s - '0');
			if (res < prev) return -1;
			prev = res;
		} else return -1;
		++s;
	}
	return res;
}

void	map_error(void) {
	fputs("map error\n", stderr);
}

void	free_map(t_map *m) {
	if (m->obs_grid) {
		for (int r = 0; r < m->he; ++r)
			free(m->obs_grid[r]);
		free(m->obs_grid);
	}
	if (m->grid) {
		for (int r = 0; r < m->he; ++r)
			free(m->grid[r]);
		free(m->grid);
	}
	free(m->raw_data);
}

static int	parse_header(t_map *m, const char *line) {
	int			nb = 0;
	const char	*p = line;

	if (*p < '1' || *p > '9') return 0;
	while (*p >= '0' && *p <= '9')
		nb = nb * 10 + (*p++ - '0');
	if (*p++ != ' ') return 0;
	char	empty = *p++;
	if (!is_print(empty) || *p++ != ' ') return 0;
	char	obs = *p++;
	if (!is_print(obs) || *p++ != ' ') return 0;
	char	full = *p++;
	if (!is_print(full) || *p != '\0') return 0;
	if (!all_unique(empty, obs, full)) return 0;
	m->he = nb;
	m->empty = empty;
	m->obs = obs;
	m->full = full;
	return 1;
}

static char	*ft_strndup(const char *s, int n) {
	char	*dup = malloc((size_t)(n + 1));
	if (!dup) return NULL;
	for (int i = 0; i < n; ++i) dup[i] = s[i];
	dup[n] = '\0';
	return dup;
}

int	parse_map(t_map *m, FILE *stream) {
	ft_bzero(m, sizeof(t_map));

	char	*line = NULL;
	size_t	cap = 0;
	ssize_t	len;

	len = getline(&line, &cap, stream);
	if (len <= 0 || line[len - 1] != '\n') { free(line); return EXIT_FAILURE; }
	line[--len] = '\0';
	if (!parse_header(m, line)) { free(line); return EXIT_FAILURE; }

	m->grid = malloc(sizeof(char *) * (size_t)m->he);
	if (!m->grid) { free(line); return EXIT_FAILURE; }
	ft_bzero(m->grid, sizeof(char *) * (size_t)m->he);

	int	width = -1;
	for (int r = 0; r < m->he; ++r) {
		len = getline(&line, &cap, stream);
		if (len <= 0 || line[len - 1] != '\n') { free(line); return EXIT_FAILURE; }
		line[--len] = '\0';
		if (len == 0) { free(line); return EXIT_FAILURE; }
		if (width == -1) width = (int)len;
		else if ((int)len != width) { free(line); return EXIT_FAILURE; }
		for (int c = 0; c < (int)len; ++c)
			if (line[c] != m->empty && line[c] != m->obs) { free(line); return EXIT_FAILURE; }
		m->grid[r] = ft_strndup(line, (int)len);
		if (!m->grid[r]) { free(line); return EXIT_FAILURE; }
	}
	free(line);
	m->we = width;

	m->obs_grid = malloc(sizeof(int *) * (size_t)m->he);
	if (!m->obs_grid) return EXIT_FAILURE;
	ft_bzero(m->obs_grid, sizeof(int *) * (size_t)m->he);
	for (int r = 0; r < m->he; ++r) {
		m->obs_grid[r] = calloc((size_t)m->we, sizeof(int));
		if (!m->obs_grid[r]) return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

static int	min3(int a, int b, int c) {
	int	mn = a < b ? a : b;
	return mn < c ? mn : c;
}

void	solve(t_map *m) {
	int	best = 0, br = 0, bc = 0, best_tr = 0, best_tc = 0;

	for (int r = 0; r < m->he; ++r) {
		for (int c = 0; c < m->we; ++c) {
			if (m->grid[r][c] == m->obs) {
				m->obs_grid[r][c] = 0;
			} else {
				int	top     = r > 0 ? m->obs_grid[r - 1][c] : 0;
				int	left    = c > 0 ? m->obs_grid[r][c - 1] : 0;
				int	topleft = (r > 0 && c > 0) ? m->obs_grid[r - 1][c - 1] : 0;
				m->obs_grid[r][c] = min3(top, left, topleft) + 1;
				int	sz = m->obs_grid[r][c];
				int	tr = r - sz + 1;
				int	tc = c - sz + 1;
				if (sz > best
					|| (sz == best && tr < best_tr)
					|| (sz == best && tr == best_tr && tc < best_tc)) {
					best = sz; br = r; bc = c;
					best_tr = tr; best_tc = tc;
				}
			}
		}
	}
	if (best == 0) return;
	for (int r = best_tr; r <= br; ++r)
		for (int c = best_tc; c <= bc; ++c)
			m->grid[r][c] = m->full;
}

int	handle_map(FILE *stream) {
	t_map	m;

	if (parse_map(&m, stream) != EXIT_SUCCESS) {
		map_error();
		free_map(&m);
		return EXIT_FAILURE;
	}
	solve(&m);
	for (int r = 0; r < m.he; ++r)
		fprintf(stdout, "%s\n", m.grid[r]);
	free_map(&m);
	return EXIT_SUCCESS;
}

int	main(int ac, char **av) {
	if (ac == 1) {
		handle_map(stdin);
		return 0;
	}
	for (int i = 1; i < ac; ++i) {
		FILE	*f = fopen(av[i], "r");
		if (!f) {
			map_error();
		} else {
			handle_map(f);
			fclose(f);
		}
		if (i + 1 < ac)
			fprintf(stdout, "\n");
	}
	return 0;
}