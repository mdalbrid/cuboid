/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_sprites.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:21:10 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 20:01:18 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_sort_sprites(t_all *all)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (!i)
	{
		j = 0;
		i = 1;
		while (j < all->map->spriteNum - 1)
		{
			if (all->map->spr[j].spriteDistance < \
									all->map->spr[j + 1].spriteDistance)
			{
				tmp = all->map->spr[j];
				all->map->spr[j] = all->map->spr[j + 1];
				all->map->spr[j + 1] = tmp;
				i = 0;
			}
			j++;
		}
	}
}

void	ft_sprites_continued(t_all *all, t_sprite *tmp, int i)
{
	tmp->spriteX = all->map->spr[i].x - all->map->player_X;
	tmp->spriteY = all->map->spr[i].y - all->map->player_Y;
	tmp->invDet = 1.0 / (all->map->planeX * all->map->dirY - \
							all->map->dirX * all->map->planeY);
	tmp->transformX = tmp->invDet * (all->map->dirY * tmp->spriteX - \
						all->map->dirX * tmp->spriteY);
	tmp->transformY = tmp->invDet * (-all->map->planeY * tmp->spriteX + \
						all->map->planeX * tmp->spriteY);
	tmp->spriteScreenX = (int)((all->map->x_res_width / 2) * \
							(1 + tmp->transformX / tmp->transformY));
	tmp->spriteHeight = (int)fabs((all->map->y_res_hight / tmp->transformY));
	tmp->drawStartY = -tmp->spriteHeight / 2 + all->map->y_res_hight / 2;
	if (tmp->drawStartY < 0)
		tmp->drawStartY = 0;
	tmp->drawEndY = tmp->spriteHeight / 2 + all->map->y_res_hight / 2;
	if (tmp->drawEndY > all->map->y_res_hight)
		tmp->drawEndY = all->map->y_res_hight - 1;
	tmp->spriteWidth = (int)fabs((all->map->x_res_width / tmp->transformY));
	tmp->drawStartX = -tmp->spriteWidth / 2 + tmp->spriteScreenX;
	if (tmp->drawStartX < 0)
		tmp->drawStartX = 0;
	tmp->drawEndX = tmp->spriteWidth / 2 + tmp->spriteScreenX;
	if (tmp->drawEndX > all->map->x_res_width)
		tmp->drawEndX = all->map->x_res_width - 1;
}

void	ft_drawing_sprites(t_all *all, t_sprite *tmp, double *zbuffer)
{
	int		y;

	while (tmp->drawStartX < tmp->drawEndX)
	{
		tmp->texX = (int)(256 * (tmp->drawStartX - (-tmp->spriteWidth / 2 + \
						tmp->spriteScreenX)) * all->img_sprite.img_width / \
													tmp->spriteWidth) / 256;
		y = tmp->drawStartY;
		if (tmp->transformY > 0 && tmp->drawStartX >= 0 && tmp->drawStartX < \
		all->map->x_res_width && tmp->transformY < zbuffer[tmp->drawStartX])
			while (y < tmp->drawEndY)
			{
				tmp->texY = (int)(((double)y - (double)all->map->y_res_hight \
					/ 2 + (double)tmp->spriteHeight / 2) * \
					(all->img_sprite.img_height) / (double)tmp->spriteHeight);
				tmp->color = *(int*)(all->img_sprite.addr + (tmp->texY * \
							all->img_sprite.line_length + (int)tmp->texX * \
										(all->img_sprite.bits_per_pixel / 8)));
				if (tmp->color != 0xFFFFFF && tmp->color)
					my_mlx_pixel_put(all->win, tmp->drawStartX, y, tmp->color);
				y++;
			}
		tmp->drawStartX++;
	}
}

void	ft_sprites(t_all *all, double *zbuffer)
{
	t_sprite	tmp;
	int			i;

	i = 0;
	while (i < all->map->spriteNum)
	{
		all->map->spr[i].spriteDistance = \
				pow((all->map->player_X - all->map->spr[i].x), 2) * \
					pow((all->map->player_Y - all->map->spr[i].y), 2);
		i++;
	}
	i = 0;
	ft_sort_sprites(all);
	while (i < all->map->spriteNum)
	{
		ft_sprites_continued(all, &tmp, i);
		ft_drawing_sprites(all, &tmp, zbuffer);
		++i;
	}
}
