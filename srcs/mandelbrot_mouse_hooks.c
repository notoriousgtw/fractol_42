/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_mouse_hooks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:51:23 by gwood             #+#    #+#             */
/*   Updated: 2018/10/04 16:12:00 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"
#include <stdio.h>

static int	m_zoom_hook(int button, int x, int y, t_data *d)
{
	t_mandelbrot	*m;

	m = (t_mandelbrot *) d->fractol;
	if (button == 4)
	{
		if (x == y)
		{
			;
		}
		// m->range -= m->range / 3;
		if (m->depth < 5)
			m->range -= 0.3;
		else
			m->range -= 0.1 * pow(0.7, 0.1 * m->depth);
		m->depth++;
		// m->location.i += (m->range / d->height) * (y + 800);
		// m->location.r += (m->range / d->width) * (x - 800);
	}
	if (button == 5)
	{
		// m->range += m->range / 3;
		if (m->depth < 6)
			m->range += 0.3;
		else
			m->range += 0.1 * pow(0.7, 0.1 * m->depth);
		m->depth--;
	}
	return (0);
}

int			m_mouse_hook(int button, int x, int y, t_data *d)
{
	m_zoom_hook(button, x, y, d);
	m_draw(d);
	return (0);
}
