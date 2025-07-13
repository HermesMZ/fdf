/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:45:26 by zoum              #+#    #+#             */
/*   Updated: 2025/07/13 17:31:18 by zoum             ###   ########.fr       */
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

char	*new_line(int fd)
{
	char	*line;
	char	*tmp;

	tmp = get_next_line(fd);
	if (!tmp)
		return (NULL);
	line = ft_strtrim(tmp, "\n");
	free(tmp);
	if (!line)
		return (NULL);
	return (line);
}

static int	add_line(t_mlx_data *data, int fd, int expected_cols)
{
	char	*line;

	line = new_line(fd);
	while (line != NULL)
	{
		if (col_count(line) != expected_cols)
		{
			free(line);
			close_gnl_fd(fd);
			ft_putstr_fd("Error: Inconsistent number of columns in map.\n", 2);
			return (1);
		}
		data->map->lines++;
		free(line);
		line = new_line(fd);
	}
	return (0);
}

int	count_map_dimensions(t_mlx_data *data, char *file_path)
{
	char	*line;
	int		fd;
	int		expected_cols;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file for counting dimensions"), 1);
	data->map->lines = 0;
	line = new_line(fd);
	if (!line)
		return (close_gnl_fd(fd), 1);
	expected_cols = col_count(line);
	if (expected_cols == 0)
	{
		free(line);
		close_gnl_fd(fd);
		return (1);
	}
	data->map->columns = expected_cols;
	data->map->lines++;
	free(line);
	if (add_line(data, fd, expected_cols))
		return (1);
	close_gnl_fd(fd);
	return (0);
}
