#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include "./libft/libft.h"
// # include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

/*
**keymap for Linux
*/

#define KEY_W 119
#define KEY_S 115
# define KEY_A 100
# define KEY_D 97
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_ESCAPE 65307
# define rotSpeed 0.09
# define mvSpeed 0.13

/*
**keymap for Mac
**# define KEY_W 13
**# define KEY_S 1
**# define KEY_A 0
**# define KEY_D 2
**# define KEY_RIGHT 123
**# define KEY_LEFT 121
**# define KEY_ESCAPE 53
*/

int					map_line_counter_global;

typedef struct	s_plr
{
	double			cameraX;
	double			rayDirX;
	double			rayDirY;
	double			deltaDistX;
	double			deltaDistY;
	int				hit;
	double			perpWallDist;
	int				stepX;
	int				stepY;
	int				side;
	double			sideDistX;
	double			sideDistY;
	int				mapX;
	int				mapY;
	double			dpos_map;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	double			wallX;
	int				texX;
	double			step;
	double			texPos;
	int				texY;
}				t_plr;

typedef struct	s_sprite
{
	int				spriteOrder;
	double			spriteDistance;
	double			x;
	double			y;
	double			spriteX;
	double			spriteY;
	double			transformX;
	double			transformY;
	double			invDet;
	double			spriteScreenX;
	int				spriteHeight;
	int				spriteWidth;
	int				drawStartY;
	int				drawStartX;
	int				drawEndY;
	int				drawEndX;
	int				texX;
	int				texY;
	int				color;
	int				vMS;
}				t_sprite;

typedef struct	s_map
{
	char			**game_world_map;
	int				x_res_width;
	int				y_res_hight;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*sprite;
	unsigned int	floorcolor;
	unsigned int	ceilingcolor;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	double			player_X;
	double			player_Y;
	int				spriteNum;
	t_sprite		spr[1024];
}				t_map;

typedef struct	s_win
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				img_height;
	int				img_width;
}				t_win;

typedef struct	s_all
{
	t_win			*win;
	t_plr			*plr;
	t_map			*map;
	t_win			img_no;
	t_win			img_so;
	t_win			img_we;
	t_win			img_ea;
	t_win			img_sprite;
	int				color;
	t_sprite		*spri;
}				t_all;

t_map	ft_parser(char *argv1);
void	ft_error(char *error, char *id);
void	ft_sprites(t_all *all, double *ZBuffer);
void	my_mlx_pixel_put(t_win *win, int x, int y, int color);
int		ft_selecting_texture(t_all *all);
void	ft_lodev_ray_casting(t_all *all);
void	ft_declaring_dda(t_all *all, int x);
void	ft_calculate_step_and_initial_sidedist(t_all *all);
void	ft_hit(t_all *all);
void	ft_drawing_wall(t_all *all, int x);
int		ft_pressing_key(int key, t_all *all);
void	ft_get_data_addr_img(t_all *all);
int		main(int argc, char **argv);
void	ft_key_left_right_hook(t_all *all, int key, double oldDirX, \
															double oldPlaneX);
void	ft_key_a_d_hook(t_all *all, int key);
void	ft_key_w_s_hook(t_all *all, int key);
void	ft_screenshot(t_all *all);
int		ft_exit_game(void);
void	ft_check_game_world_map(t_map *s_map, char **map);
void	ft_check_direction_player_view(t_map *s_map, char **map, int i, int j);
void	ft_check_valid_game_world_map(t_map *s_map, char **map, int i, int j);
int		checking_the_map_parameters(t_map *map, char *line, int final_check);
void ft_error(char *error, char *id);
void	ft_skip_space(char **line);
int		converting_to_hex(int *rgb);
int		ft_color_parser(t_map *map, char *line);
char	*ft_texture_parser(t_map *map, char *line);
void	ft_resolution_parser(t_map *map, char *line);
int		ft_resolution_parser_atoi(char **line);

#endif