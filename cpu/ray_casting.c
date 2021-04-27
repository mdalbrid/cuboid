/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:19:20 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 20:03:03 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_declaring_dda(t_all *all, int x)
{
	all->plr->cameraX = 2 * x / (double)all->map->x_res_width - 1;
	all->plr->rayDirX = all->map->dirX + all->map->planeX \
							* all->plr->cameraX;
	all->plr->rayDirY = all->map->dirY + all->map->planeY \
							* all->plr->cameraX;
	all->plr->mapX = (int)all->map->player_X;
	all->plr->mapY = (int)all->map->player_Y;
	if (all->plr->rayDirX == 0)
		all->plr->deltaDistY = 0;
	else
		all->plr->deltaDistY = all->plr->rayDirY == 0 ? \
									1 : fabs(1 / all->plr->rayDirY);
	if (all->plr->rayDirY == 0)
		all->plr->deltaDistX = 0;
	else
		all->plr->deltaDistX = all->plr->rayDirX == 0 ? \
									1 : fabs(1 / all->plr->rayDirX);
	all->plr->hit = 0;
}

void	ft_calculate_step_and_initial_sidedist(t_all *all)
{
	if (all->plr->rayDirX < 0)
	{
		all->plr->stepX = -1;
		all->plr->dpos_map = all->map->player_X - all->plr->mapX;
		all->plr->sideDistX = all->plr->dpos_map * all->plr->deltaDistX;
	}
	else
	{
		all->plr->stepX = 1;
		all->plr->dpos_map = all->plr->mapX + 1.0 - all->map->player_X;
		all->plr->sideDistX = all->plr->dpos_map * all->plr->deltaDistX;
	}
	if (all->plr->rayDirY < 0)
	{
		all->plr->stepY = -1;
		all->plr->dpos_map = all->map->player_Y - all->plr->mapY;
		all->plr->sideDistY = all->plr->dpos_map * all->plr->deltaDistY;
	}
	else
	{
		all->plr->stepY = 1;
		all->plr->dpos_map = all->plr->mapY + 1.0 - all->map->player_Y;
		all->plr->sideDistY = all->plr->dpos_map * all->plr->deltaDistY;
	}
}

void	ft_hit(t_all *all)
{
	while (all->plr->hit == 0)
	{
		if (all->plr->sideDistX < all->plr->sideDistY)
		{
			all->plr->sideDistX += all->plr->deltaDistX;
			all->plr->mapX += all->plr->stepX;
			all->plr->side = 0;
		}
		else
		{
			all->plr->sideDistY += all->plr->deltaDistY;
			all->plr->mapY += all->plr->stepY;
			all->plr->side = 1;
		}
		if (all->map->game_world_map[all->plr->mapX][all->plr->mapY] == '1')
			all->plr->hit = 1;
	}
	if (all->plr->side == 0)
		all->plr->perpWallDist = (all->plr->mapX - all->map->player_X + \
								(1 - all->plr->stepX) / 2) / all->plr->rayDirX;
	else
		all->plr->perpWallDist = (all->plr->mapY - all->map->player_Y + \
								(1 - all->plr->stepY) / 2) / all->plr->rayDirY;
}

void	ft_drawing_wall_continued(t_all *all, int x)
{
	int		j;

	j = 0;
	while (j < all->plr->drawStart)
	{
		my_mlx_pixel_put(all->win, x, j, all->map->ceilingcolor);
		j++;
	}
	while (all->plr->drawStart < all->plr->drawEnd)
	{
		all->plr->texY = (int)all->plr->texPos & 63;
		all->plr->texPos += all->plr->step;
		ft_selecting_texture(all);
		my_mlx_pixel_put(all->win, x, all->plr->drawStart, all->color);
		all->plr->drawStart++;
	}
	while (all->plr->drawEnd < all->map->y_res_hight)
	{
		my_mlx_pixel_put(all->win, x, all->plr->drawEnd, all->map->floorcolor);
		all->plr->drawEnd++;
	}
}

void	ft_drawing_wall(t_all *all, int x)
{
	all->plr->lineHeight = (int)(all->map->y_res_hight \
												/ all->plr->perpWallDist);
	all->plr->drawStart = -all->plr->lineHeight / 2 + all->map->y_res_hight / 2;
	if (all->plr->drawStart < 0)
		all->plr->drawStart = 0;
	all->plr->drawEnd = all->plr->lineHeight / 2 + all->map->y_res_hight / 2;
	if (all->plr->drawEnd >= all->map->y_res_hight)
		all->plr->drawEnd = all->map->y_res_hight - 1;
	all->color = 0xb0b7c6;
	if (all->plr->side == 1)
		all->color = all->color * 1.5;
	if (all->plr->side == 0)
		all->plr->wallX = all->map->player_Y + all->plr->perpWallDist * \
							all->plr->rayDirY;
	else
		all->plr->wallX = all->map->player_X + all->plr->perpWallDist * \
							all->plr->rayDirX;
	all->plr->wallX -= floor(all->plr->wallX);
	all->plr->texX = (int)(all->plr->wallX * 64);
	all->plr->step = 64.0 / (double)all->plr->lineHeight;
	all->plr->texPos = (all->plr->drawStart - all->map->y_res_hight / \
						2 + all->plr->lineHeight / 2) * all->plr->step;
	ft_drawing_wall_continued(all, x);
}
