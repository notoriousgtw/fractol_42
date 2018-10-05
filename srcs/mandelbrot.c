/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 17:39:25 by gwood             #+#    #+#             */
/*   Updated: 2018/10/04 14:56:17 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mandelbrot.h"
#include <math.h>
#include <stdio.h>

static void		display_controls(void)
{
	ft_putendl("CONTROLS:\n");
}

double		iter(t_mandelbrot m)
{
	size_t	i;
	t_complex z;
	double tmp;
	double modulus;
	double mu;

	z.r = 0.0;
	z.i = 0.0;
	i = 0;
	modulus = 0;
	while (i < m.max_iter && modulus < m.escape_radius)
	{
		tmp = z.r * z.r - z.i * z.i + m.c.r;
		z.i = 2.0 * z.r * z.i + m.c.i;
		z.r = tmp;
		modulus = sqrt(z.r*z.r + z.i*z.i);
		i++;
	}
	if (i == m.max_iter)
		return (i + 1);
	// mu = (log(log(modulus))) / log(2.0);
	mu = log( (log(z.r * z.r + z.i * z.i) / 2) / log(2) ) / log(2);
	if (isnan(mu))
		mu = 0;
	else
		mu = (double) (i + 1) - mu;
	// mu = ((double) 15 / (double) m.max_iter) * (double) i;
	return (mu);
}

double	map(int x, int max, double min_d, double max_d)
{
	double range;

	range = max_d - min_d;
	return (x * (range / max) + min_d);
}

void		m_draw(t_data *d)
{
	int				x;
	int				y;
	t_mandelbrot	m;
	double			mu;
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
			m.c.r = map(x, d->width, m.location.r - m.range,
						m.location.r + m.range);
			m.c.i = map(y, d->height, m.location.i - m.range,
						m.location.i + m.range);
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
		d->width = 1600;
		d->height = 1600;
		d->win = mlx_new_window(d->mlx, d->width, d->height, "Fract'ol");
		d->fractol = m;
		m->location.i = 0;
		m->location.r = -0.75;
		m->range = 1.3;
		m->depth = 0;
		m->max_iter = 64;
		m->escape_radius = 3;
		display_controls();
		init_pallete(m->pallete);
		mlx_expose_hook(d->win, m_expose_hook, NULL);
		mlx_key_hook(d->win, m_key_hook, d);
		mlx_mouse_hook(d->win, m_mouse_hook, d);
		m_draw(d);
		mlx_loop(d->mlx);
	}
	return (0);
}
