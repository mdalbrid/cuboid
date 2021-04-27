/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:19:20 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 20:11:21 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		checking_the_map_parameters(t_map *map, char *line, int final_check)
{
	int		i;

	i = 0;
	if (map->x_res_width && map->no_texture \
		&& map->so_texture && map->we_texture && map->ea_texture \
		&& map->sprite && map->floorcolor && map->ceilingcolor)
	{
		if (line)
			while (line[i])
			{
				if (line[i] != '1' && line[i] != '2' && line[i] != '0' &&
					line[i] != 'S' && line[i] != 'N' && line[i] != 'W' &&
					line[i] != 'E' && line[i] != ' ')
					ft_error("garbage on the game world map [ ", line + i);
				i++;
			}
		return (0);
	}
	else if (final_check)
		ft_error("missing arguments on the map !", 0);
	return (1);
}

void	ft_check_valid_game_world_map(t_map *s_map, char **map, int i, int j)
{
	if (!map[i][j + 1] || map[i][j + 1] == ' ' \
			|| !map[i][j - 1] || map[i][j - 1] == ' ' \
			|| !map[i + 1] || map[i + 1][j] == ' ' || i == 0 \
			|| map[i - 1][j] == ' ' || !map[i - 1])
		ft_error("the map is invalid, check the Adjacent walls - [ ", map[i]);
	if (!map[i + 1][j + 1] || map[i + 1][j + 1] == ' ' || !map[i - 1][j - 1] \
			|| map[i - 1][j - 1] == ' ' || !map[i + 1][j - 1] \
			|| map[i + 1][j - 1] == ' ' || !map[i - 1][j + 1] \
			|| map[i - 1][j + 1] == ' ')
		ft_error("the map is invalid, check the Diagonal walls - [ ", map[i]);
	if (map[i][j] == '2')
	{
		s_map->spr[s_map->spriteNum].x = (double)i + .5;
		s_map->spr[s_map->spriteNum].y = (double)j + .5;
		s_map->spriteNum++;
	}
}

void	ft_check_direction_player_view(t_map *s_map, char **map, int i, int j)
{
	if (map[i][j] == 'W' || map[i][j] == 'E')
	{
		s_map->dirX = 0;
		s_map->dirY = map[i][j] == 'W' ? -1 : 1;
		s_map->planeX = map[i][j] == 'W' ? -.66 : .66;
		s_map->planeY = 0;
	}
	else if (map[i][j] == 'N' || map[i][j] == 'S')
	{
		s_map->dirX = map[i][j] == 'N' ? -1 : 1;
		s_map->dirY = 0;
		s_map->planeX = 0;
		s_map->planeY = map[i][j] == 'N' ? .66 : -.66;
	}
	s_map->player_X = (double)i + .5;
	s_map->player_Y = (double)j + .5;
}

void	ft_check_game_world_map(t_map *s_map, char **map)
{
	int		i;
	int		j;
	int		player;

	i = -1;
	player = 0;
	while (map[++i] != 0)
	{
		j = -1;
		while (map[i][++j] != 0)
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' \
				|| map[i][j] == 'E' || map[i][j] == 'S')
			{
				if (++player > 1)
					ft_error("only one player allowed - [ ", map[i]);
				ft_check_direction_player_view(s_map, map, i, j);
			}
			if (map[i][j] == '0' || map[i][j] == '2' || map[i][j] == 'N' \
				|| map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S')
				ft_check_valid_game_world_map(s_map, map, i, j);
		}
	}
	if (player == 0)
		ft_error("player not found !", 0);
}
