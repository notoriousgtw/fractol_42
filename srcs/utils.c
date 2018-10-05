/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:36:16 by mhurd             #+#    #+#             */
/*   Updated: 2018/10/04 14:13:31 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	ft_putpixel(t_data *d, int x, int y, t_color color)
{
	int				i;

	if (x > 0 && y > 0 && x < d->width && y < d->height)
	{
		i = (x * 4) + (y * d->s_line);
		d->pixel_img[i] = ft_color_get(color, b);
		d->pixel_img[++i] = ft_color_get(color, g);
		d->pixel_img[++i] = ft_color_get(color, r);
	}
}

void	init_pallete(t_color p[16])
{
	p[0].i = 0x421e0f;
	p[1].i = 0x19071a;
	p[2].i = 0x09012f;
	p[3].i = 0x000764;
	p[4].i = 0x0c2c8a;
	p[5].i = 0x1852b1;
	p[6].i = 0x397dd1;
	p[7].i = 0x86b5e5;
	p[8].i = 0xd3ecf8;
	p[9].i = 0xf1e9bf;
	p[10].i = 0xf8c95f;
	p[11].i = 0xffaa00;
	p[12].i = 0xcc8000;
	p[13].i = 0x995700;
	p[14].i = 0x6a3403;
	p[15].i = 0x421e0f;
}
