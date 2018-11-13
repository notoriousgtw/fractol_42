/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_mouse_hooks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:51:23 by gwood             #+#    #+#             */
/*   Updated: 2018/11/13 14:28:42 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"
#include <stdio.h>

static void	m_zoom(int x, int y, t_data *d, double z)
{
	t_mandelbrot	*m;
	double			w;
	double			h;
	double			nw;
	double			nh;

	m = (t_mandelbrot *) d->fractal;
	w = m->range.r * m->zoom;
	h = m->range.i * m->zoom;
	nw = m->range.r * m->zoom * z;
	nh = m->range.i * m->zoom * z;
	m->zoom *= z;
	m->location.r += ((double) x / d->width) * (nw - w);
	m->location.i += ((double) y / d->height) * (nh - h);
}

static int	m_zoom_hook(int button, int x, int y, t_data *d)
{
	if (button == 4)
		m_zoom(x, y, d, 1.1);
	if (button == 5)
		m_zoom(x, y, d, 1 / 1.1);
	return (0);
}

int			m_mouse_hook(int button, int x, int y, t_data *d)
{
	m_zoom_hook(button, x, y, d);
	m_draw(d, (t_mandelbrot *) d->fractal);
	return (0);
}
