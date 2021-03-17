/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:10:30 by mbenjell          #+#    #+#             */
/*   Updated: 2017/07/16 12:28:42 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				protect(void *m)
{
	if (!m)
	{
		write(1, "ERROR\n", 6);
		exit(1);
	}
}

static int			usage(void)
{
	write(1, "Fractales disponibles : ", 24);
	write(1, "\e[31mJulia ", 11);
	write(1, "\e[32mMandelbrot ", 16);
	write(1, "\e[33mBurning_ship\n", 18);
	exit(1);
}

static void			init_env(t_env **e, void *select)
{
	int				bpp;
	int				s_l;
	int				endian;

	protect((void*)(*e = (t_env*)malloc(sizeof(t_env))));
	protect((*e)->mlx = mlx_init());
	protect((*e)->win = mlx_new_window((*e)->mlx, WIDTH, HEIGHT, TITLE));
	protect((*e)->p_img = mlx_new_image((*e)->mlx, WIDTH, HEIGHT));
	protect((*e)->d_img = mlx_get_data_addr((*e)->p_img, &bpp, &s_l, &endian));
	((*e)->alpha)[0] = 0.0;
	((*e)->alpha)[1] = 0.0;
	(*e)->color = COLOR_1;
	(*e)->kind_color = 0;
	(*e)->iter = 42;
	(*e)->pf = (t_f*)select;
	(*e)->xmin = -2;
	(*e)->xmax = 2;
	(*e)->ymin = -2;
	(*e)->ymax = 2;
	(*e)->scale = 4 / WIDTH;
}

static void			*select_fract(int argc, char const **argv)
{
	if (argc != 2)
		return (NULL);
	if (!ft_strcmp(argv[1], "Julia"))
		return ((void*)julia);
	if (!ft_strcmp(argv[1], "Mandelbrot"))
		return ((void*)mandelbrot);
	if (!ft_strcmp(argv[1], "Burning_ship"))
		return ((void*)burningship);
	return (NULL);
}

int					main(int argc, char const **argv)
{
	t_env			*e;
	void			*select;

	select = select_fract(argc, argv);
	if (select == NULL)
		usage();
	init_env(&e, select);
	draw(e);
	mlx_put_image_to_window(e->d_img, e->win, e->p_img, 0, 0);
	mlx_hook(e->win, KEY_PRESS, KEY_RELEASE, manage_key, (void*)e);
	mlx_hook(e->win, MOUSE_IN, MOUSE_OUT, manage_mouse, (void*)e);
	mlx_hook(e->win, SCROLL_PLUS, MOUSE_OUT, manage_zoom, (void*)e);
	mlx_loop(e->mlx);
	return (0);
}
