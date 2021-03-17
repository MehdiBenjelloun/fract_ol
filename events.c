/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 00:45:44 by mbenjell          #+#    #+#             */
/*   Updated: 2017/07/16 12:30:14 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom(t_env *e, int x, int y, int in_out)
{
	double	gx;
	double	dx;
	double	gy;
	double	dy;

	gx = 100 * x / WIDTH;
	dx = 100 - gx;
	gy = 100 * y / WIDTH;
	dy = 100 - gy;
	e->xmin = e->xmin + (in_out) * gx * e->scale;
	e->xmax = e->xmax - (in_out) * dx * e->scale;
	e->ymin = e->ymin + (in_out) * gy * e->scale;
	e->ymax = e->ymax - (in_out) * dy * e->scale;
	e->scale = (e->xmax - e->xmin) / WIDTH;
	e->iter += ITER;
}

int			manage_key(int keycode, void *env)
{
	t_env	*e;

	e = (t_env*)env;
	if (keycode == ESC)
		exit(1);
	if (keycode == SPACE)
		e->block = (e->block + 1) % 2;
	if (keycode >= COLOR_1 && keycode <= COLOR_3)
		e->color = keycode % 3;
	if (keycode == PLUS)
		(e->iter)++;
	if (keycode == MINUS)
		(e->iter)--;
	if (keycode == ENTER)
		e->kind_color = (e->kind_color + 1) % 2;
	draw(((t_env*)e));
	mlx_put_image_to_window(e->d_img, e->win, e->p_img, 0, 0);
	return (0);
}

int			manage_mouse(int x, int y, void *env)
{
	t_env	*e;

	e = (t_env*)env;
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT && !e->block)
	{
		(e->alpha)[0] = x / 1000.0;
		(e->alpha)[1] = y / 1000.0;
	}
	draw((t_env*)e);
	mlx_put_image_to_window(e->d_img, e->win, e->p_img, 0, 0);
	return (0);
}

int			manage_zoom(int button, int x, int y, void *env)
{
	t_env	*e;

	e = (t_env*)env;
	if (button == SCROLL_PLUS)
		zoom(e, x, y, 1);
	if (button == SCROLL_MINUS)
	{
		if (e->iter < ITER_MIN)
			e->iter = ITER_MIN;
		zoom(e, x, y, -1);
	}
	draw((t_env*)e);
	mlx_put_image_to_window(e->d_img, e->win, e->p_img, 0, 0);
	return (0);
}
