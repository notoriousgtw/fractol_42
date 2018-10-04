/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 17:39:25 by gwood             #+#    #+#             */
/*   Updated: 2018/10/03 20:04:13 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mandelbrot.h"

static void		display_controls(void)
{
	ft_putendl("CONTROLS:\n");
}

double		iter(t_mandelbrot m)
{
	size_t	i;
	t_complex z;
	double tmp;
	// double log_zn;
	double mu;

	z.r = 0.0;
	z.i = 0.0;
	i = 0;
	while (i < m.max_iter)
	{
		tmp = z.r * z.r - z.i * z.i + m.c.r;
		z.i = 2.0 * z.r * z.i + m.c.i;
		z.r = tmp;
		i++;
	}
	mu = (15 / m.max_iter) * i;
	return (mu);
}

static double	map(int x, int max, double min_r, double max_r)
{
	double range;

	range = max_r - min_r;
	return (x * (range / max) + min_r);
}

void		m_draw(t_data *d)
{
	int				x;
	int				y;
	t_mandelbrot	m;
	int				mu;
	t_color			color;

	color.i = 0;
	d->img = mlx_new_image(d->mlx, d->width, d->height);
	d->pixel_img = mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	m = *(t_mandelbrot *) d->fractol;
	y = -1;
	while (++y < d->height)
	{
		x = -1;
		while (++x < d->width)
		{
			m.c.r = map(x, d->width, m.min.r, m.max.r);
			m.c.i = map(y, d->height, m.min.i, m.max.i);
			mu = iter(m);
			// ft_putpixel(d, x, y, get_color(d, mu));
			ft_color_lerp(m.pallete[(int) floor(mu)],
						  m.pallete[(int) floor(mu) + 1],
						  fmod(mu, 1.0), &color);
			ft_putpixel(d, x, y, color);
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	mlx_destroy_image(d->mlx, d->img);
}

int				mandelbrot(int argc, char** argv)
{
	t_data			*d;
	t_mandelbrot	*m;

	if (argc > 0 && argv[0] != NULL)
	{
		if (!(d = (t_data *)ft_memalloc(sizeof(t_data))))
			return (-1);
		if (!(m = (t_mandelbrot *)ft_memalloc(sizeof(t_mandelbrot))))
			return (-1);
		d->mlx = mlx_init();
		d->width = 1080;
		d->height = 1080;
		d->win = mlx_new_window(d->mlx, d->width, d->height, "Fract'ol");
		d->fractol = m;
		m->min.r = -0.5;
		m->max.r = 1.5;
		m->min.i = -1;
		m->max.i = 1;
		m->max_iter = 500;
		m->escape_radius = 3;
		display_controls();
		init_pallete(m->pallete);
		mlx_expose_hook(d->win, m_expose_hook, NULL);
		mlx_key_hook(d->win, m_key_hook, d);
		mlx_loop(d->mlx);
	}
	return (0);
}
