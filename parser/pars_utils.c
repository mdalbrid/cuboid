/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalbrid <mdalbrid@student.21>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:19:20 by mdalbrid          #+#    #+#             */
/*   Updated: 2021/04/27 20:11:55 by mdalbrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(char *error, char *id)
{
	if (id)
	{
		if (*id == '\0' && !(*(id - 1)))
			id = "remove the last line in the map !";
		write(1, "  -  \n", 7);
		write(1, "Error - ", 8);
		ft_putstr_fd(error, 1);
		ft_putstr_fd(id, 1);
		write(1, " ]", 2);
		write(1, "\n  -  \n", 7);
		exit(-1);
	}
	else
	{
		write(1, "  -  \n", 7);
		write(1, "Error - ", 8);
		ft_putstr_fd(error, 1);
		write(1, "\n  -  \n", 8);
		exit(-1);
	}
}

void	ft_skip_space(char **line)
{
	while (**line && (**line == ' ' || **line == '\t'))
		++(*line);
}

int		converting_to_hex(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
