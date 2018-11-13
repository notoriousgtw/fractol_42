/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_key_hooks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:33:57 by mhurd             #+#    #+#             */
/*   Updated: 2018/11/13 14:37:06 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"

int	m_expose_hook()
{
	return (0);
}

int	m_key_hook(int keycode, t_data *d)
{
	t_mandelbrot *m;

	m = (t_mandelbrot *) d->fractal;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	else if (keycode == KEY_W)
		m->location.i -= 1 / m->zoom;
	else if (keycode == KEY_S)
		m->location.i += 1 / m->zoom;
	else if (keycode == KEY_A)
		m->location.r -= 1 / m->zoom;
	else if (keycode == KEY_D)
		m->location.r += 1 / m->zoom;

	m_draw(d, (t_mandelbrot *) d->fractal);
	return (0);
}
