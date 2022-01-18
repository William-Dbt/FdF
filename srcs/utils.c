/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:02:20 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/18 15:09:37 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

//status : EXIT_FAILURE = 1, EXIT_SUCCESS = 0
int	ft_exit(const char *error, t_env *mlx, int status)
{
	if (status == EXIT_FAILURE)
		ft_printf(STR_ERROR, error);
	if (mlx != NULL)
	{
		mlx_loop_end(mlx->mlx);
		mlx_destroy_window(mlx->mlx, mlx->window);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	exit(status);
	return (status);
}

void	my_mlx_pixel_put(t_env *mlx, int x, int y, int color)
{
	char	*dst;
	t_img	*img;

	if (x < 0 || y < 0 || x > mlx->win_width || y > mlx->win_height)
		return ;
	img = &mlx->img;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_freemap(t_point **tab, int max_y)
{
	int	y;

	y = 0;
	while (y < max_y)
		free(tab[y++]);
	free(tab);
}

void	ft_freestrtab(char **tab, char *line)
{
	int	y;

	y = 0;
	if (tab != NULL)
	{
		while (tab[y])
			free(tab[y++]);
		free(tab);
	}
	if (line != NULL)
		free(line);
}

int	ft_openfile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, "", 0) == -1)
		return (ft_exit("File doesn't exist !", NULL, EXIT_FAILURE));
	return (fd);
}