/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:59:38 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/17 17:43:29 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

static void	ft_readmap(t_map *map, int fd, int x, int y)
{
	char	*line;
	char	**temp_map;

	while (1)
	{
		line = get_next_line(fd);
		temp_map = ft_split(line, ' ');
		if (temp_map == NULL)
		{
			ft_freestrtab(temp_map, line);
			break ;
		}
		x = 0;
		while (temp_map[x] && temp_map[x][0] != '\n')
			x++;
		if (x > map->max_columns)
			map->max_columns = x;
		y++;
		ft_freestrtab(temp_map, line);
	}
	map->max_lines = y;
	close(fd);
}

static t_point	**ft_mallocmap(int max_x, int max_y)
{
	int		y;
	t_point	**map_tab;

	map_tab = (t_point **)malloc(sizeof(t_point *) * max_y + 1);
	if (map_tab == NULL)
		return (NULL);
	y = 0;
	while (y < max_y)
	{
		map_tab[y] = (t_point *)malloc(sizeof(t_point) * max_x);
		if (map_tab[y] == NULL)
		{
			ft_freemap(map_tab, max_y);
			return (NULL);
		}
		y++;
	}
	return (map_tab);
}

static void	ft_set_data_to_struct(t_map *map, char *temp_map, int x, int y)
{
	char	**split_elems;

	if (ft_strchr(temp_map, ','))
	{
		split_elems = ft_split(temp_map, ',');
		map->map[y][x].z = ft_atoi(split_elems[0]);
		map->map[y][x].color = malloc(sizeof(char *)
				* (ft_strlen(split_elems[1] + 1)));
		if (map->map[y][x].color == NULL)
			return ;
		ft_strlcpy(map->map[y][x].color, split_elems[1],
			ft_strlen(split_elems[1]));
		ft_freestrtab(split_elems, NULL);
	}
	else
		map->map[y][x].z = ft_atoi(temp_map);
}

static void	ft_fillmap(t_map *map, char *filename, int x, int y)
{
	int		fd;
	char	*line;
	char	**temp_map;

	fd = ft_openfile(filename);
	while (1)
	{
		line = get_next_line(fd);
		temp_map = ft_split(line, ' ');
		if (temp_map == NULL)
		{
			ft_freestrtab(temp_map, line);
			break ;
		}
		x = 0;
		while (x < map->max_columns)
		{
			if (temp_map[x] != NULL)
				ft_set_data_to_struct(map, temp_map[x], x, y);
			x++;
		}
		ft_freestrtab(temp_map, line);
		y++;
	}
	close(fd);
}

void	ft_checkmap(t_map *map, char *filename)
{
	int	fd;

	fd = ft_openfile(filename);
	map->max_columns = 0;
	map->max_lines = 0;
	ft_readmap(map, fd, 0, 0);
	map->map = ft_mallocmap(map->max_columns, map->max_lines);
	if (map->map == NULL)
		ft_exit("An error occured while mallocing the map !", NULL,
			EXIT_FAILURE);
	ft_fillmap(map, filename, 0, 0);
}