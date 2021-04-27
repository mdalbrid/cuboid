/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:19:20 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 20:13:46 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_blow_job(t_map *map, char *line)
{
	if (checking_the_map_parameters(map, 0, 0))
		ft_skip_space(&line);
	if (*line == 'R')
		ft_resolution_parser(map, ++line);
	else if (*line == 'N' && *(line + 1) == 'O')
		map->no_texture = ft_texture_parser(map, line);
	else if (*line == 'S' && *(line + 1) == 'O')
		map->so_texture = ft_texture_parser(map, line);
	else if (*line == 'W' && *(line + 1) == 'E')
		map->we_texture = ft_texture_parser(map, line);
	else if (*line == 'E' && *(line + 1) == 'A')
		map->ea_texture = ft_texture_parser(map, line);
	else if (*line == 'S' && *(line + 1) == ' ')
		map->sprite = ft_texture_parser(map, line);
	else if (*line == 'F')
		map->floorcolor = ft_color_parser(map, ++line);
	else if (*line == 'C')
		map->ceilingcolor = ft_color_parser(map, ++line);
	else if (!checking_the_map_parameters(map, line, 1) && *line)
		map->game_world_map[map_line_counter_global++] = line;
	else
		ft_error("garbage in the map - [ ", line);
}

void	ft_initialization(t_map *map)
{
	map->game_world_map = malloc(sizeof(t_sprite));
	map_line_counter_global = 0;
	map->x_res_width = 0;
	map->y_res_hight = 0;
	map->no_texture = 0;
	map->so_texture = 0;
	map->we_texture = 0;
	map->ea_texture = 0;
	map->sprite = 0;
	map->floorcolor = 0;
	map->ceilingcolor = 0;
	map->spriteNum = 0;
}

t_map	ft_parser(char *argv1)
{
	int		fd;
	char	*line;
	t_map	map;

	if ((fd = open(argv1, O_RDONLY)) == -1)
		ft_error("error reading the .cub file", 0);
	line = NULL;
	ft_initialization(&map);
	while (get_next_line(fd, &line))
	{
		if (*line == 0 && *map.game_world_map)
			ft_error("empty line on the game world map !", 0);
		else if (*line == 0)
			continue;
		else
			ft_blow_job(&map, line);
	}
	ft_blow_job(&map, line);
	close(fd);
	ft_check_game_world_map(&map, map.game_world_map);
	return (map);
}
