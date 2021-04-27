/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:19:20 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 20:13:06 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_resolution_parser_atoi(char **line)
{
	int		i;
	int		resol;

	i = 0;
	resol = 0;
	while (ft_isdigit(**line))
	{
		if (i <= 4)
		{
			resol = resol * 10 + (**line - '0');
			i++;
		}
		++*line;
	}
	return (resol);
}

void	ft_resolution_parser(t_map *map, char *line)
{
	int		i;

	i = 0;
	if (*(line - 1) == 'R' && map->x_res_width)
		ft_error("double resolution - [ ", (line - 1));
	while (i++ != 2)
	{
		ft_skip_space(&line);
		if (!ft_isdigit(*line))
			ft_error("garbage in resolution - [ ", line);
		if (!map->x_res_width && i == 1)
			map->x_res_width = ft_resolution_parser_atoi(&line);
		else
			map->y_res_hight = ft_resolution_parser_atoi(&line);
	}
	if (*line != 0)
		ft_error("garbage in resolution - [ ", line);
	if (map->x_res_width > 2560)
		map->x_res_width = 2560;
	if (map->y_res_hight > 1440)
		map->y_res_hight = 1440;
}

char	*ft_texture_parser(t_map *map, char *line)
{
	char *address;

	ft_skip_space(&line);
	if (*line == 'N' && map->no_texture)
		ft_error("double NOrth texture - [ ", line);
	else if (*line == 'S' && *(line + 1) == 'O' && map->so_texture)
		ft_error("double SOuth texture - [ ", line);
	else if (*line == 'W' && map->we_texture)
		ft_error("double WEast texture - [ ", line);
	else if (*line == 'E' && map->ea_texture)
		ft_error("double EAst texture - [ ", line);
	else if (*line == 'S' && map->sprite)
		ft_error("double Sprite texture - [ ", line);
	address = line + 2;
	ft_skip_space(&address);
	ft_skip_space(&line);
	if ((open(address, O_RDONLY)) == -1)
		ft_error("texture doesn't open(check the spaces) - [ ", address);
	return (address);
}

int		ft_color_parser(t_map *map, char *line)
{
	int		color[3];
	int		i;

	if (*(line - 1) == 'F' && map->floorcolor)
		ft_error("double parameter - Floor color - [ ", (line - 1));
	else if (*(line - 1) == 'C' && map->ceilingcolor)
		ft_error("double parameter - Ceiling color - [ ", (line - 1));
	i = -1;
	while (i++ != 2)
	{
		ft_skip_space(&line);
		if (!ft_isdigit(*line))
			ft_error("garbage in RGB - [ ", line);
		color[i] = ft_resolution_parser_atoi(&line);
		if (color[i] < 0 || color[i] > 255)
			ft_error("[ 0 < Color RGB < 255 ! ] ", 0);
		ft_skip_space(&line);
		if (*line == ',' && i != 2)
			++(line);
		else if (*line == 0 && i != 2)
			ft_error("not enough arguments in RGB !", 0);
	}
	if (*line != 0)
		ft_error("garbage in RGB - [ ", line);
	return (converting_to_hex(color));
}
