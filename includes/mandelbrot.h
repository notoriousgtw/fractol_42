/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:42:02 by gwood             #+#    #+#             */
/*   Updated: 2018/10/03 18:23:13 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDELBROT_H
# define MANDELBROT_H

# include "fractol.h"
# include "ft_comlpex.h"

typedef struct	s_mandelbrot
{
	size_t		max_iter;
	t_color		pallete[16];
	t_complex	c;
	t_complex	min;
	t_complex	max;
	double		escape_radius;
	double		zoom;
	double		tx;
	double		ty;
}				t_mandelbrot;

int				mandelbrot(int argc, char **argv);
int				m_expose_hook();
int				m_key_hook(int keycode, t_data *d);
void			m_draw(t_data *d);

#endif
