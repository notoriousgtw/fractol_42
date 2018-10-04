/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:34:16 by mhurd             #+#    #+#             */
/*   Updated: 2018/10/02 18:52:28 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double		m_iterate(t_mandelbrot m)
{
	int	i;
	t_complex z;
	double tmp;
	double log_zn;
	double mu;

	z.r = 0.0;
	z.i = 0.0;
	i = 0;
	while (i < MAX_ITER && z.r * z.r + z.i * z.i < (1 << 16))
	{
		tmp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2.0 * z.r * z.i + c.i;
		z.r = tmp;
		i++;
	}
	mu = i;
	if (i < MAX_ITER)
	{
		log_zn = log(z.r * z.r + z.i * z.i) / (double)2;
		if (isinf(log_zn))
			return (0.0);
		mu = log(log_zn / log(2)) / log(2);
	}
		// mu = (double)i - log2(log2(z.r * z.r + z.i * z.i)) + 4.0;
	return (mu);
}

double	map(int x, double min_r, double max_r)
{
	double range;

	range = max_r - min_r;
	return (x * (range / WINDOW_SIZE_X) + min_r);
}

int		get_color(t_data *d, int mu)
{
	int		color1;
	int		color2;

	color1 = d->colors[(int)floor(mu)];
	color2 = d->colors[((int)floor(mu) + 1)];
	return ((int)floor(ft_lerp(color1, color2, fmod(mu, 1))));
}

void	m_draw(t_data *d, t_mandelbrot m)
{
	int		x;
	int		y;
	double	mu;

	y = -1;
	while (++y < WINDOW_SIZE_Y)
	{
		x = -1;
		while (++x < WINDOW_SIZE_X)
		{
			m.c.r = map(x, m.min.r, m.max.r);
			m.c.i = map(y, m.min.i, m.max.i);
			mu = find_mu(m.c);
			// ft_putpixel(d, x, y, (int)floor(ft_lerp(color1, color2, fmod(n, 1))));
			ft_putpixel(d, x, y, get_color(d, mu));
			// ft_putpixel(d, x, y, (int)floor(mu));
			mu = mu;
		}
	}
}

void	draw_julia(t_data *d)
{
	int			i;
	int			x;
	int			y;
	t_complex	*c;
	t_complex	*z;
	t_complex	*tmp;

	c = ft_complex(-0.7, 0.27015);
	d->zoom = 10;
	d->tx = 0;
	d->ty = 0;
	y = -1;
	while (++y < WINDOW_SIZE_Y)
	{
		x = -1;
		while (++x < WINDOW_SIZE_X)
		{
			z = ft_complex(1.5 * (x - WINDOW_SIZE_X / 2) /
									(0.5 * d->zoom * WINDOW_SIZE_X) + d->tx,
									(y - WINDOW_SIZE_Y / 2) / (0.5 * d->zoom *
									WINDOW_SIZE_Y) + d->ty);
			i = 0;
			while (i < MAX_ITER)
			{
				tmp = ft_complex(z->r, z->i);
				z->r = tmp->r * tmp->r - tmp->i * tmp->i + c->r;
				z->i = 2 * tmp->r * tmp->i + c->i;
				free(tmp);
				if (z->r * z->r + z->i * z->i > 4)
					break;
				i++;
        	}
			if (i < MAX_ITER)
				ft_putpixel(d, x, y, d->colors[i]);
			free(z);
		}
	}
	free(c);
}



void	draw_reload(t_data *d)
{
	t_mandelbrot m;

	d->img = mlx_new_image(d->mlx, WINDOW_SIZE_X + 100, WINDOW_SIZE_Y + 100);
	d->pixel_img = mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	draw_mandelbrot(d, m);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	mlx_destroy_image(d->mlx, d->img);
}

void	draw_everything(t_data *d)
{
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "Fract'ol");
	d->zoom = 10;
	d->tx = 0;
	d->ty = 0;
	init_color_table(d);
	mlx_expose_hook(d->win, expose_hook, NULL);
	mlx_key_hook(d->win, key_hook, d);
	mlx_loop(d->mlx);
}
