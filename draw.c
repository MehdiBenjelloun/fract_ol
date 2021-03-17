/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 22:08:58 by mbenjell          #+#    #+#             */
/*   Updated: 2017/07/16 11:28:57 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		plot(char *img, int x, int y, int color[3])
{
	if (x < 0 || y < 0)
		return ;
	if (!((x < WIDTH) && (y < HEIGHT)))
		return ;
	*(img + x * 4 + y * WIDTH * 4) = (char)color[2];
	*(img + x * 4 + y * WIDTH * 4 + 1) = (char)color[1];
	*(img + x * 4 + y * WIDTH * 4 + 2) = (char)color[0];
}

static void		set_color(t_env *e, int pos[2])
{
	int			color[3];
	int			iter;

	iter = (e->pf)(e, pos);
	if (iter < e->iter)
	{
		color[(0 + e->color) % 3] = (char)(255 * cos(0.02 * iter));
		color[(1 + e->color) % 3] = (char)(255 * cos(0.03 * iter));
		color[(2 + e->color) % 3] = (char)(255 * cos(0.04 * iter));
	}
	else
	{
		color[0] = (char)0;
		color[1] = (char)0;
		color[2] = (char)0;
	}
	plot(e->d_img, pos[0], pos[1], color);
}

static void		set_color_2(t_env *e, int pos[2])
{
	int			color[3];
	int			iter;

	iter = (e->pf)(e, pos);
	if (iter < e->iter)
	{
		color[(0 + e->color) % 3] = (char)(255 * sin(0.02 * iter));
		color[(1 + e->color) % 3] = (char)(255 * sin(0.03 * iter));
		color[(2 + e->color) % 3] = (char)(255 * sin(0.04 * iter));
	}
	else
	{
		color[0] = (char)0;
		color[1] = (char)0;
		color[2] = (char)0;
	}
	plot(e->d_img, pos[0], pos[1], color);
}

void			draw(t_env *e)
{
	int			pos[2];
	void		(*p_color)(t_env*, int[2]);

	pos[0] = -1;
	pos[1] = -1;
	if (e->kind_color)
		p_color = set_color;
	else
		p_color = set_color_2;
	while (pos[1]++ < HEIGHT)
	{
		while (pos[0]++ < WIDTH)
			p_color(e, pos);
		pos[0] = -1;
	}
}
