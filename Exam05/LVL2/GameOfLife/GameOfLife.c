/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameOfLife.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:36:23 by pboucher          #+#    #+#             */
/*   Updated: 2026/04/25 15:26:23 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int count_neighbors(char **grid, int h, int w, int y, int x)
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
	if (ac != 4)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	int w = atoi(av[1]), h = atoi(av[2]), iter = atoi(av[3]);
	if (w <= 0 || h <= 0 || iter < 0)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	char **grid = malloc(sizeof(char *) * h), **temp = malloc(sizeof(char *) * h);
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
			grid[y][x] = 'O';
	}
	for (int it = 0; it < iter; it++)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				int num = count_neighbors(grid, h, w, i, j);
				if (grid[i][j] == 'O' && (num == 2 || num == 3))
					temp[i][j] = 'O';
				else if (grid[i][j] == ' ' && num == 3)
					temp[i][j] = 'O';
				else
					temp[i][j] = ' ';
			}
		}
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				grid[i][j] = temp[i][j];
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			printf("%c", grid[i][j]);
		printf("\n");
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