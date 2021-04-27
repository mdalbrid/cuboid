/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:21:10 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 20:08:59 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		ft_selecting_texture(t_all *all)
{
	if (all->plr->side)
	{
		if (all->plr->rayDirY < 0)
		{
			return (all->color = *(int*)(all->img_we.addr + ((int)all->plr->texY
								* all->img_we.line_length + all->plr->texX * \
											(all->img_we.bits_per_pixel / 8))));
		}
		return (all->color = *(int*)(all->img_ea.addr + ((int)all->plr->texY\
								* all->img_ea.line_length + all->plr->texX * \
											(all->img_ea.bits_per_pixel / 8))));
	}
	if (all->plr->rayDirX > 0)
	{
		return (all->color = *(int*)(all->img_so.addr + ((int)all->plr->texY \
								* all->img_so.line_length + all->plr->texX * \
											(all->img_so.bits_per_pixel / 8))));
	}
	else
	{
		return (all->color = *(int*)(all->img_no.addr + ((int)all->plr->texY \
								* all->img_no.line_length + all->plr->texX * \
											(all->img_no.bits_per_pixel / 8))));
	}
}

void	ft_get_data_addr_img(t_all *all)
{
	all->img_sprite.img = mlx_xpm_file_to_image(all->win->mlx,\
	all->map->sprite, &all->img_sprite.img_width, &all->img_sprite.img_height);
	all->img_sprite.addr = mlx_get_data_addr(all->img_sprite.img,\
				&all->img_sprite.bits_per_pixel, &all->img_sprite.line_length,\
													&all->img_sprite.endian);
	all->img_no.img = mlx_xpm_file_to_image(all->win->mlx,\
		all->map->no_texture, &all->img_no.img_width, &all->img_no.img_height);
	all->img_no.addr = mlx_get_data_addr(all->img_no.img,\
				&all->img_no.bits_per_pixel, &all->img_no.line_length,\
														&all->img_no.endian);
	all->img_so.img = mlx_xpm_file_to_image(all->win->mlx,\
		all->map->so_texture, &all->img_so.img_width, &all->img_so.img_height);
	all->img_so.addr = mlx_get_data_addr(all->img_so.img,\
				&all->img_so.bits_per_pixel, &all->img_so.line_length,\
														&all->img_so.endian);
	all->img_we.img = mlx_xpm_file_to_image(all->win->mlx,\
		all->map->we_texture, &all->img_we.img_width, &all->img_we.img_height);
	all->img_we.addr = mlx_get_data_addr(all->img_we.img,\
				&all->img_we.bits_per_pixel, &all->img_we.line_length,\
														&all->img_we.endian);
	all->img_ea.img = mlx_xpm_file_to_image(all->win->mlx,\
		all->map->ea_texture, &all->img_ea.img_width, &all->img_ea.img_height);
	all->img_ea.addr = mlx_get_data_addr(all->img_ea.img,\
				&all->img_ea.bits_per_pixel, &all->img_ea.line_length,\
														&all->img_ea.endian);
}
