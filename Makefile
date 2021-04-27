SRC					=	./parser/parser_main.c\
						./parser/checks.c\
						./parser/parser.c\
						./parser/pars_utils.c\
						./cpu/key_hook.c\
						./cpu/ray_casting_sprites.c\
						./cpu/ray_casting.c\
						./cpu/management_functions.c\
						./cpu/utils.c\
						./cpu/screenshot.c\
						./main.c
HDR					=	cub3dh.h
MLX_HDR				=	mlx.h
OBJ					=	${SRC:%.c=%.o}
NAME				=	cub3D
CFLAGS				=	-Wall -Wextra -Werror
NORM				=	norminetteV2
NORMO				=	${SRC} ${HDR}

all:				${NAME}

%.o:				%.c ${HDR}
					gcc ${CFLAGS} -c $< -o $@

${NAME}: 			${OBJ}
					gcc ${OBJ} libmlx.dylib -o ${NAME}

linux: 				${OBJ}
					gcc ${OBJ} -lXext -lX11 -lm -lz ./minilibx-linux/libmlx.a -o ${NAME}

win10: 				${OBJ}
					gcc ${OBJ} -lz libft.a ./minilibx-linux/libmlx.a -lXext -lX11 -lm -lbsd -o ${NAME}

clean:
					@rm -f ${OBJ}

fclean:				clean
					@rm -f ${NAME}

norm:
					@${NORM} ${NORMO}

re:					fclean ${NAME}

.PHONY:				all clean fclean re norm
