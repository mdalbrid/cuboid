/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:19:20 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 20:14:44 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

// int		ft_finish_game(t_all *all)
// {
// 	int i;

// 	i = -1;
// 	while (all->map->game_world_map[++i])
// 		free(all->map->game_world_map[i]);
// 	free(all->map);
// 	exit(0);
// }

int		ft_exit_game(void)
{
	ft_putstr_fd("WP", 1);
	exit(0);
}

void	ft_play(char *argv, int save)
{
	t_all	all;
	t_win	win;
	t_plr	plr;
	t_map	map;

	all.win = &win;
	all.plr = &plr;
	all.map = &map;
	map = ft_parser(argv);
	all.win->mlx = mlx_init();
	all.win->win = mlx_new_window(all.win->mlx,
				all.map->x_res_width, all.map->y_res_hight, "cub3D");
	all.win->img = mlx_new_image(all.win->mlx,
				all.map->x_res_width, all.map->y_res_hight);
	all.win->addr = mlx_get_data_addr(all.win->img, &all.win->bits_per_pixel,\
				&all.win->line_length, &all.win->endian);
	ft_get_data_addr_img(&all);
	ft_lodev_ray_casting(&all);
	if (save)
		ft_screenshot(&all);
	mlx_hook(all.win->win, 33, (1L << 0), &ft_exit_game, &all);
	mlx_hook(all.win->win, 2, (1L << 0), &ft_pressing_key, &all);
	mlx_loop(all.win->mlx);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		ft_play(argv[1], 0);
	else if (argc == 3 && !ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
		ft_play(argv[1], 1);
	else
		ft_error("invalid arguments - [ ", argv[argc - 1]);
}
