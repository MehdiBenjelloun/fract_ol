/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 23:51:25 by mbenjell          #+#    #+#             */
/*   Updated: 2017/07/16 12:22:29 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		calcul(t_env *e, double *re, double *im, int pos[2])
{
	double		dx;
	double		dy;

	dx = e->xmax - e->xmin;
	dy = e->ymax - e->ymin;
	*re = e->xmin + dx * (double)pos[0] / WIDTH;
	*im = e->ymin + dy * (double)pos[1] / HEIGHT;
}

int				julia(t_env *e, int pos[2])
{
	int			iter;
	double		re;
	double		im;
	double		re_temp;

	iter = 0;
	calcul(e, &re, &im, pos);
	while (re * re + im * im <= 4 && iter++ < e->iter)
	{
		re_temp = re * re - im * im - (e->alpha)[0];
		im = 2 * re * im + (e->alpha)[1];
		re = re_temp;
	}
	return (iter);
}

int				mandelbrot(t_env *e, int pos[2])
{
	double		a;
	double		b;
	double		a_temp;
	int			iter;
	double		c[2];

	a = (e->alpha)[0];
	b = (e->alpha)[1];
	iter = 0;
	calcul(e, &(c[0]), &c[1], pos);
	while (a * a + b * b <= 4 && iter < e->iter)
	{
		a_temp = a * a - b * b + c[0];
		b = 2 * a * b + c[1];
		a = a_temp;
		iter++;
	}
	return (iter);
}

int				burningship(t_env *e, int pos[2])
{
	double		a;
	double		b;
	double		a_temp;
	int			iter;
	double		c[2];

	a = fabs((e->alpha)[0]);
	b = fabs((e->alpha)[1]);
	iter = 0;
	calcul(e, &(c[0]), &c[1], pos);
	while (a * a + b * b <= 4 && iter < e->iter)
	{
		a = fabs(a);
		b = fabs(b);
		a_temp = a * a - b * b + c[0];
		b = 2 * a * b + c[1];
		a = a_temp;
		iter++;
	}
	return (iter);
}
