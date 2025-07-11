/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:09:12 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/10 19:24:11 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	col_count(char *line)
{
	int	i;
	int	is_in_nbr;
	int	count;

	count = 0;
	is_in_nbr = 0;
	if (!line)
		return (0);
	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] != ' ') && !is_in_nbr)
		{
			is_in_nbr = 1;
			count ++;
		}
		else if (line[i] == ' ' || line[i] == '\n')
			is_in_nbr = 0;
		i++;
	}
	return (count);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	**create_tab(int lines, int col)
{
	int	**tab;
	int	i;

	tab = malloc(sizeof(int *) * (lines + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tab[lines + 1] = NULL;
	while (i < lines)
	{
		tab[i] = malloc(sizeof(int) * (col + 1));
		if (!tab[i])
			return (free_tab(tab), NULL);
		ft_memset(tab[i], '\0', col + 1);
		i++;
	}
	return (tab);
}

int	map_parsing(t_map *map, char *src_map)
{
	char	**splitted;
	int		i;
	int		j;

	i = 0;
	splitted = ft_split(src_map, ' ');
	map->array_map = create_tab(map->lines, map->columns);
	while (i < map->lines)
	{
		j = 0;
		while (j < map->columns)
		{
			map->array_map[i][j] = ft_atoi(splitted++);
			j++;
			if (*splitted == '\n')
				splitted++;
		}
		i++;
	}
}

int	check_extract_map(t_map *map, int fd)
{
	char	*src_map;
	char	*tmp;
	char	*line;

	line = get_next_line(fd);
	map->columns = col_count(line);
	tmp = NULL;
	src_map = NULL;
	while (line)
	{
		if (col_count(line) != map->columns)
			return (1);
		tmp = src_map;
		src_map = ft_strjoin(src_map, line);
		free(tmp);
		free(line);
		map->lines++;
		line = get_next_line(fd);
	}
	close(fd);
	map_parsing(map, src_map);
	return (0);
}
