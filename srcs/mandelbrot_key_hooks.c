/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_key_hooks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:33:57 by mhurd             #+#    #+#             */
/*   Updated: 2018/10/04 13:58:49 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"

int	m_expose_hook()
{
	return (0);
}

int	m_key_hook(int keycode, t_data *d)
{
	// t_mandelbrot m;

	// m = *(t_mandelbrot *) d->fractol;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}

	m_draw(d);
	return (0);
}
