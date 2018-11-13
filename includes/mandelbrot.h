/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:42:02 by gwood             #+#    #+#             */
/*   Updated: 2018/11/13 00:37:03 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDELBROT_H
# define MANDELBROT_H

# include "fractol.h"
# include "ft_comlpex.h"

typedef struct	s_mandelbrot	t_mandelbrot;
typedef struct	s_mandelbrot_thread
{
	t_mandelbrot	*m;
	t_data			*d;
	t_complex		c;
	double			mu;
	t_color			color;
	int				x_start;
	int				x_end;
	int				y_start;
	int				y_end;
}				t_mandelbrot_thread;
typedef struct	s_mandelbrot
{
	t_color				pallete[16];
	size_t				max_iter;
	double				escape_radius;
	t_complex			location;
	t_complex			range;
	double				zoom;
	pthread_t			thread_ids[THREAD_COUNT];
	pthread_attr_t		thread_attrs;
	t_mandelbrot_thread	threads[THREAD_COUNT];
}				t_mandelbrot;


double			map(int x, int max, double min_d, double max_d);
int				mandelbrot(int argc, char **argv);
void			*mandelbrot_render(t_mandelbrot_thread *thread_data);
double			m_iter(t_complex c, t_mandelbrot *m);
int				m_expose_hook();
int				m_mouse_hook(int button, int x, int y, t_data *d);
int				m_key_hook(int keycode, t_data *d);
void			m_draw(t_data *d, t_mandelbrot *m);

#endif
