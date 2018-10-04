/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_hooks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:33:57 by mhurd             #+#    #+#             */
/*   Updated: 2018/10/02 20:51:30 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"

// static	void	key_hook_rotation(int keycode, t_data *d)
// {
// 	if (keycode == KEY_EIGHT)
// 		d->xr += 0.01;
// 	else if (keycode == KEY_TWO)
// 		d->xr -= 0.01;
// 	else if (keycode == KEY_SIX)
// 		d->yr += 0.01;
// 	else if (keycode == KEY_FOUR)
// 		d->yr -= 0.01;
// 	else if (keycode == KEY_NINE)
// 		d->zr += 0.01;
// 	else if (keycode == KEY_SEVEN)
// 		d->zr -= 0.01;
// }

// static	void	key_hook_translation(int keycode, t_data *d)
// {
// 	if (keycode == KEY_W)
// 		d->ytrans += 5;
// 	else if (keycode == KEY_S)
// 		d->ytrans -= 5;
// 	else if (keycode == KEY_A)
// 		d->xtrans += 5;
// 	else if (keycode == KEY_D)
// 		d->xtrans -= 5;
// }

// static	void	key_hook_scale(int keycode, t_data *d)
// {
// 	if (keycode == KEY_PLUS)
// 		d->scale += 0.1;
// 	else if (keycode == KEY_MINUS)
// 		d->scale = fabs(d->scale - 0.1);
// }

int	m_expose_hook()
{
	return (0);
}

int	m_key_hook(int keycode, t_data *d)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	m_draw(d);
	return (0);
}
