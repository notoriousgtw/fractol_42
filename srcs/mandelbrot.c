/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 17:39:25 by gwood             #+#    #+#             */
/*   Updated: 2018/11/13 01:39:11 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mandelbrot.h"
#include <math.h>
#include <stdio.h>

static void		display_controls(void)
{
	ft_putendl("CONTROLS:\n");
}

double		m_iter(t_complex c, t_mandelbrot *m)
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
	while (i < m->max_iter && modulus < m->escape_radius)
	{
		tmp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2.0 * z.r * z.i + c.i;
		z.r = tmp;
		modulus = sqrt(z.r*z.r + z.i*z.i);
		i++;
	}
	if (i == m->max_iter)
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

void		m_draw(t_data *d, t_mandelbrot *m)
{
	int					t;
	int					side;
	int					i[2];
	int					x[2];
	int					y[2];

	pthread_attr_init(&m->thread_attrs);
	d->img = mlx_new_image(d->mlx, d->width, d->height);
	d->pixel_img = mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	t = -1;
	side = (int) sqrt(THREAD_COUNT);
	i[0] = -1;
	y[0] = 0;
	y[1] = d->height / side;
	while (++i[0] < side)
	{
		i[1] = -1;
		x[0] = 0;
		x[1] = d->width / side;
		while (++i[1] < side)
		{
			m->threads[++t].d = d;
			m->threads[t].m = m;
			m->threads[t].x_start = x[0];
			if (i[1] == side - 1)
				m->threads[t].x_end = d->width;
			else
				m->threads[t].x_end = d->width - x[1] * (side - i[1] - 1);
			m->threads[t].y_start = y[0];
			if (i[0] == side - 1)
				m->threads[t].y_end = d->height;
			else
				m->threads[t].y_end = d->height - y[1] * (side - i[0] - 1);
			pthread_create(&m->thread_ids[t], &m->thread_attrs, (t_thread_fnc) mandelbrot_render, &m->threads[t]);
			x[0] += x[1];
		}
		y[0] += y[1];
	}
	while (t >= 0)
		pthread_join(m->thread_ids[t--], NULL);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	mlx_destroy_image(d->mlx, d->img);
}

int				mandelbrot(int argc, char** argv)
{
	t_data			d;
	t_mandelbrot	m;

	if (argc > 0 && argv[0] != NULL)
	{
		d.mlx = mlx_init();
		d.width = 1600;
		d.height = 1600;
		d.win = mlx_new_window(d.mlx, d.width, d.height, "Fract'ol");
		d.fractal = &m;
		m.location.i = 0;
		m.location.r = -0.75;
		m.range.i = 1.3;
		m.range.r = 1.3;
		m.zoom = 1;
		m.max_iter = 64;
		m.escape_radius = 3;
		display_controls();
		init_pallete(m.pallete);
		mlx_do_key_autorepeaton(d.mlx);
		mlx_expose_hook(d.win, m_expose_hook, NULL);
		// mlx_hook(d.win, 2, 0, m_key_hook, &d);
		mlx_key_hook(d.win, m_key_hook, &d);
		mlx_mouse_hook(d.win, m_mouse_hook, &d);
		m_draw(&d, &m);
		mlx_loop(d.mlx);
	}
	return (0);
}
