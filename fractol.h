/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 13:55:25 by mbenjell          #+#    #+#             */
/*   Updated: 2017/07/16 12:22:51 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define TITLE 			"fract'ol"
# define WIDTH 			800
# define HEIGHT			800
# define ESC			53

# define ITER			1
# define ITER_MIN 		12

# define KEY_PRESS		2
# define KEY_RELEASE	3
# define PLUS			69
# define MINUS			78
# define SPACE			49
# define ENTER			76

# define MOUSE_IN		6
# define MOUSE_OUT		8

# define SCROLL_PLUS	4
# define SCROLL_MINUS	5

# define COLOR_1		83
# define COLOR_2		84
# define COLOR_3		85

typedef unsigned char	t_oct;

typedef	struct			s_env
{
	void				*mlx;
	void				*win;
	void				*p_img;
	char				*d_img;
	double				alpha[2];
	int					color;
	int					iter;
	double				scale;
	int					block;
	double				xmin;
	double				xmax;
	double				ymin;
	double				ymax;
	int					(*pf)(struct s_env*, int[2]);
	int					kind_color;
}						t_env;

typedef struct			s_complex
{
	double				re;
	double				im;
}						t_complex;

typedef	int				t_f(t_env *env, int pos[2]);

int						ft_strcmp(const char *s1, const char *s2);
void					protect(void *m);
int						julia(t_env *e, int pos[2]);
int						mandelbrot(t_env *e, int pos[2]);
int						burningship(t_env *e, int pos[2]);
int						manage_key(int keycode, void *env);
int						manage_mouse(int x, int y, void *env);
int						manage_zoom(int button, int x, int y, void *env);
void					draw(t_env *e);

#endif
