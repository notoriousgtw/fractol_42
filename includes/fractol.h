/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwood <gwood@42.us.org>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:06:16 by mhurd             #+#    #+#             */
/*   Updated: 2018/11/12 22:39:34 by gwood            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "libft.h"
# include "ft_color.h"
# include <pthread.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <errno.h>

# define FRACTAL_COUNT 1
# define THREAD_COUNT 9

/*
** KEYS
*/

# define KEY_ESC 0xff1b
# define KEY_ENTER 0xff8d

# define KEY_W	0x77
# define KEY_A	0x61
# define KEY_S	0x73
# define KEY_D	0x64

# define KEY_NP_ONE	0xff9c
# define KEY_NP_TWO	0xff99
# define KEY_NP_THREE	0xff9b
# define KEY_NP_FOUR	0xff96
# define KEY_NP_FIVE	0xff97
# define KEY_NP_SIX	0xff98
# define KEY_NP_SEVEN	0xff95
# define KEY_NP_EIGHT	0xff97
# define KEY_NP_NINE	0xff9a

# define KEY_NP_PLUS   0xffab
# define KEY_NP_MINUS  0xffad

typedef int		(*t_fractal_fnc)(int argc, char **argv);
typedef void	*(*t_thread_fnc)(void *data);

typedef struct	s_fractal_prg
{
	char			*name;
	t_fractal_fnc	draw;
}				t_fractal_prg;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pixel_img;
	int			bpp;
	int			s_line;
	int			ed;
	int			width;
	int			height;
	void		*fractal;
}				t_data;

void	init_pallete(t_color p[16]);
void	ft_putpixel(t_data *d, int x, int y, t_color color);

#endif
