/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 19:45:13 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 19:59:02 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** static unsigned char infoHeader[] = {
**		0, 0, 0, 0, /// header size
**		0, 0, 0, 0, /// image width
**		0, 0, 0, 0, /// image height
**		0, 0,     /// number of color planes
**		0, 0,     /// bits per pixel
**		0, 0, 0, 0, /// compression
**		0, 0, 0, 0, /// image size
**		0, 0, 0, 0, /// horizontal resolution
**		0, 0, 0, 0, /// vertical resolution
**		0, 0, 0, 0, /// colors in color table
**		0, 0, 0, 0, /// important color count
**
** };
*/

void	init_bmp_header(t_all *all, int fd, int size)
{
	write(fd, "BM", 2);
	write(fd, (char *)&size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\x36\0\0\0", 4);
	write(fd, "\x28\0\0\0", 4);
	write(fd, (char *)&all->map->x_res_width, 4);
	write(fd, (char *)&all->map->y_res_hight, 4);
	write(fd, "\1\0", 2);
	write(fd, (char *)&all->win->bits_per_pixel, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
}

void	ft_screenshot(t_all *all)
{
	int		fd;
	int		size;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0666);
	if (fd < 0)
		ft_error("open screenshot !", 0);
	size = all->map->x_res_width * all->map->y_res_hight *\
						(all->win->bits_per_pixel / 8) + 54;
	init_bmp_header(all, fd, size);
	while (all->map->y_res_hight >= 0)
	{
		write(fd, (all->win->addr + all->win->line_length * \
			all->map->y_res_hight), (all->map->x_res_width * \
								all->win->bits_per_pixel / 8));
		all->map->y_res_hight--;
	}
	close(fd);
	ft_putstr_fd("The screenshot is ready !", 1);
	exit(0);
}
