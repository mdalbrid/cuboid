/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:21:10 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 20:10:35 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_key_w_s_hook(t_all *all, int key)
{
	if (key == KEY_W)
	{
		if (all->map->game_world_map[(int)(all->map->player_X + all->map->dirX\
						* (mvSpeed + .4))][(int)all->map->player_Y] != '1')
			all->map->player_X += mvSpeed * all->map->dirX;
		if (all->map->game_world_map[(int)all->map->player_X]\
		[(int)(all->map->player_Y + all->map->dirY * (mvSpeed + .4))] != '1')
			all->map->player_Y += mvSpeed * all->map->dirY;
	}
	if (key == KEY_S)
	{
		if (all->map->game_world_map[(int)(all->map->player_X - all->map->dirX
						* (mvSpeed + .4))][(int)all->map->player_Y] != '1')
			all->map->player_X -= mvSpeed * all->map->dirX;
		if (all->map->game_world_map[(int)(all->map->player_X)]\
		[(int)(all->map->player_Y - all->map->dirY * (mvSpeed + .4))] != '1')
			all->map->player_Y -= mvSpeed * all->map->dirY;
	}
}

void	ft_key_a_d_hook(t_all *all, int key)
{
	if (key == KEY_A)
	{
		if (all->map->game_world_map[(int)(all->map->player_X - \
		all->map->planeX * (mvSpeed - .4))][(int)all->map->player_Y] != '1')
			all->map->player_X += mvSpeed * all->map->planeX;
		if (all->map->game_world_map[(int)(all->map->player_X)]\
		[(int)(all->map->player_Y - all->map->planeY * (mvSpeed - .4))] != '1')
			all->map->player_Y += mvSpeed * all->map->planeY;
	}
	if (key == KEY_D)
	{
		if (all->map->game_world_map[(int)(all->map->player_X + \
		all->map->planeX * (mvSpeed - .4))][(int)all->map->player_Y] != '1')
			all->map->player_X -= mvSpeed * all->map->planeX;
		if (all->map->game_world_map[(int)(all->map->player_X)]\
		[(int)(all->map->player_Y + all->map->planeY * (mvSpeed - .4))] != '1')
			all->map->player_Y -= mvSpeed * all->map->planeY;
	}
}

void	ft_key_left_right_hook(t_all *all, int key, double olddirx, \
															double oldplanex)
{
	if (key == KEY_RIGHT)
	{
		all->map->dirX = all->map->dirX * cos(-rotSpeed) - \
											all->map->dirY * sin(-rotSpeed);
		all->map->dirY = olddirx * sin(-rotSpeed) + \
											all->map->dirY * cos(-rotSpeed);
		all->map->planeX = all->map->planeX * cos(-rotSpeed) - \
											all->map->planeY * sin(-rotSpeed);
		all->map->planeY = oldplanex * sin(-rotSpeed) + \
											all->map->planeY * cos(-rotSpeed);
	}
	if (key == KEY_LEFT)
	{
		all->map->dirX = all->map->dirX * cos(rotSpeed) - \
												all->map->dirY * sin(rotSpeed);
		all->map->dirY = olddirx * sin(rotSpeed) + \
												all->map->dirY * cos(rotSpeed);
		all->map->planeX = all->map->planeX * cos(rotSpeed) - \
											all->map->planeY * sin(rotSpeed);
		all->map->planeY = oldplanex * sin(rotSpeed) + \
											all->map->planeY * cos(rotSpeed);
	}
}
