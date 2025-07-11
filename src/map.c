/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:09:12 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/11 15:20:57 by mzimeris         ###   ########.fr       */
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

void	free_map(int **tab)
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

int	**create_map(int lines, int col)
{
	int	**tab;
	int	i;

	tab = malloc(sizeof(int *) * (lines + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tab[lines] = NULL;
	while (i < lines)
	{
		tab[i] = malloc(sizeof(int) * (col + 1));
		if (!tab[i])
			return (free_map(tab), NULL);
		ft_memset(tab[i], 0, sizeof(int) * col);
		i++;
	}
	return (tab);
}

void	map_parsing(t_mlx_data *data, char *src_map)
{
	char	**splitted;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	splitted = ft_split(src_map, ' ');
	data->map->array_map = create_map(data->map->lines, data->map->columns);
	while (i < data->map->lines && splitted[k])
	{
		j = 0;
		while (j < data->map->columns && splitted[k])
		{
			if (splitted[k][0] != '\n')
				data->map->array_map[i][j] = ft_atoi(splitted[k]);
			j++;
			k++;
		}
		i++;
	}
	free_splitted(splitted);
}

int	check_extract_map(t_mlx_data *data, int fd)
{
	char	*src_map;
	char	*tmp;
	char	*line;

	line = get_next_line(fd);
	data->map->columns = col_count(line);
	tmp = NULL;
	src_map = ft_strdup("");
	while (line)
	{
		if (col_count(line) != data->map->columns)
			return (1);
		tmp = ft_strjoin(src_map, line);
		free(src_map);
		free(line);
		src_map = tmp;
		data->map->lines++;
		line = get_next_line(fd);
	}
	close(fd);
	map_parsing(data, src_map);
	free(src_map);
	return (0);
}
