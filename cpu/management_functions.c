/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:21:10 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 20:42:20 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_lodev_ray_casting(t_all *all)
{
	int		x;
	double	zbuffer[all->map->x_res_width];

	x = 0;
	while (x < all->map->x_res_width)
	{
		ft_declaring_dda(all, x);
		ft_calculate_step_and_initial_sidedist(all);
		ft_hit(all);
		ft_drawing_wall(all, x);
		zbuffer[x] = all->plr->perpWallDist;
		++x;
	}
	ft_sprites(all, zbuffer);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	mlx_do_sync(all->win->mlx);
}

int		ft_pressing_key(int key, t_all *all)
{
	double		olddirx;
	double		oldplanex;

	oldplanex = all->map->planeX;
	olddirx = all->map->dirX;
	if (key == KEY_W || key == KEY_S)
		ft_key_w_s_hook(all, key);
	if (key == KEY_A || key == KEY_D)
		ft_key_a_d_hook(all, key);
	if (key == KEY_RIGHT || key == KEY_LEFT)
		ft_key_left_right_hook(all, key, olddirx, oldplanex);
	if (key == KEY_ESCAPE)
	{
		// mlx_destroy_window(all->win->mlx, all->win->win);
		ft_exit_game();
		// ft_finish
	}
	ft_lodev_ray_casting(all);
	return (0);
}
