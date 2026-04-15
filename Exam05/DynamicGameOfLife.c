/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicGameOfLife.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:36:23 by pboucher          #+#    #+#             */
/*   Updated: 2026/04/15 01:54:23 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

# define RST "\e[0m"
# define RED "\e[1;91m"
# define GRN "\e[1;92m"
# define YEL "\e[1;93m"
# define BLU "\e[1;94m"
# define MAG "\e[1;95m"
# define CYN "\e[1;96m"
# define WHT "\e[1;97m"

char	**g_grid = NULL;
char	**g_temp = NULL;
int	g_h = 0;

void	free_grids(void)
{
	for (int i = 0; i < g_h; i++)
	{
		if (g_grid) free(g_grid[i]);
		if (g_temp) free(g_temp[i]);
	}
	free(g_grid);
	free(g_temp);
	g_grid = NULL;
	g_temp = NULL;
}

void handler(int sig)
{
	(void)sig;
	free_grids();
	printf(RED "\nGame interrupted. Exiting...\n" RST);
	exit(0);
}

int count_live_neighbors(char **grid, int h, int w, int y, int x)
{
	int count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;
			int ny = y + i, nx = x + j;
			if (ny < 0 || ny >= h || nx < 0 || nx >= w)
				continue;
			if (grid[ny][nx] == 'O' || grid[ny][nx] == 'o')
				count++;
		}
	}
	return (count);
}

int main(int ac, char **av)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	if (ac != 5)
	{
		printf(RED "Error: Invalid number of arguments\n");
		printf("Usage: ./DynamicGameOfLife <width> <height> <iterations> <speed>\n" RST);
		return (1);
	}
	int w = atoi(av[1]), h = atoi(av[2]), iter = atoi(av[3]), speed = atoi(av[4]);
	if (w <= 0 || h <= 0 || iter < 0 || speed <= 0)
	{
		printf(RED "Error: Invalid argument values\n");
		printf("Width and height must be positive integers, iterations must be non-negative, and speed must be a positive integer\n" RST);
		return (1);
	}
	g_h = h;
	char **grid = malloc(sizeof(char *) * h), **temp = malloc(sizeof(char *) * h);
	g_grid = grid;
	g_temp = temp;
	for (int i = 0; i < h; i++)
	{
		grid[i] = malloc(w);
		temp[i] = malloc(w);
		for (int j = 0; j < w; j++)
			grid[i][j] = ' ';
	}
	int x = 0, y = 0, pen = 0;
	char c;
	while (read(0, &c, 1) > 0)
	{
		if (c == 'x')
			pen = !pen;
		if (c == 'w' && y > 0)
			y--;
		if (c == 's' && y < h - 1)
			y++;
		if (c == 'a' && x > 0)
			x--;
		if (c == 'd' && x < w - 1)
			x++;
		if (pen)
			grid[y][x] = 'o';
	}
	for (int it = 0; it < iter; it++)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				int live_neighbors = count_live_neighbors(grid, h, w, i, j);
				if ((grid[i][j] == 'O' || grid[i][j] == 'o') && (live_neighbors == 2 || live_neighbors == 3))
					temp[i][j] = 'O';
				else if (grid[i][j] == ' ' && live_neighbors == 3)
					temp[i][j] = 'o';
				else
					temp[i][j] = ' ';
			}
		}
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				grid[i][j] = temp[i][j];
		printf("\033[H\033[2J");
		printf("  " GRN "Game of Life" RST " — Generation %d\n\n", it + 1);
		printf("┌");
		for (int j = 0; j < w; j++) printf("─");
		printf("┐\n");
		for (int i = 0; i < h; i++)
		{
			printf("│");
			for (int j = 0; j < w; j++)
			{
				if (grid[i][j] == 'O')
					printf(GRN "█" RST);
				else if (grid[i][j] == 'o')
					printf(YEL "█" RST);
				else
					printf(" ");
			}
			printf("│\n");
		}
		printf("└");
		for (int j = 0; j < w; j++) printf("─");
		printf("┘\n");
		usleep(speed * 1e3);
	}
	for (int i = 0; i < h; i++)
	{
		free(grid[i]);
		free(temp[i]);
	}
	free(grid);
	free(temp);
	return (0);
}