/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:38:20 by gwood             #+#    #+#             */
/*   Updated: 2018/11/13 02:08:17 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"

void	*mandelbrot_render(t_mandelbrot_thread *t)
{
	int		x;
	int		y;

	y = t->y_start;
	while (++y < t->y_end)
	{
		x = t->x_start;
		while (++x < t->x_end)
		{
			t->c.r = map(x, t->d->width, t->m->location.r - t->m->range.r,
						t->m->location.r + t->m->range.r) / t->m->zoom;
			t->c.i = -map(y, t->d->height, t->m->location.i - t->m->range.i,
						t->m->location.i + t->m->range.i) / t->m->zoom;
			// t->c.r = (double) x / t->m->zoom + (t->m->location.r - t->m->range.r);
			// t->c.i = (double) y / t->m->zoom + (t->m->location.i - t->m->range.i);
			// t->c.r = ((2 * t->m->range * x / t->d->width - t->m->range) /
			// 		 t->m->zoom) + (t->m->location.r / t->d->width);
			// t->c.i = ((2 * t->m->range * y / t->d->height - t->m->range) /
			// 		 t->m->zoom) + (t->m->location.i / t->d->height);
			t->mu = m_iter(t->c, t->m);
			// ft_putpixel(d, x, y, get_color(d, mu));
			ft_color_lerp(t->m->pallete[(int) floor(t->mu)],
						  t->m->pallete[(int) floor(t->mu) + 1],
						  fmod(t->mu, 1.0), &t->color);
			ft_putpixel(t->d, x, y, t->color);
		}
	}
	pthread_exit(0);
	return (NULL);
}
