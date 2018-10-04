/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 12:00:38 by gwood             #+#    #+#             */
/*   Updated: 2018/10/02 22:11:31 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mandelbrot.h"

void	init_dispatch(t_fractal_prg *t)
{
	t[0].name = "mandelbrot";
	t[0].draw = mandelbrot;
}

int		main(int argc, char **argv)
{
	int				i;
	int				j;
	t_fractal_prg	fractals[FRACTAL_COUNT];

	init_dispatch(fractals);
	if (argc > 1)
	{
		i = 0;
		while (++i < argc)
		{
			j = -1;
			while (++j < FRACTAL_COUNT)
			{
				if (ft_strequ(argv[i], fractals[j].name))
					fractals[j].draw(argc - i, argv + i);
			}
		}
	}
	write(1, "\n", 1);
	return (0);
}
