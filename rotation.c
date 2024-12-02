/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:25:20 by mquero            #+#    #+#             */
/*   Updated: 2024/12/02 14:08:33 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	rotate_z(int *x, int *y, t_coord *c)
{
	double	calc_x;
	double	calc_y;

	calc_x = roundf(*x * cos(c->gamma) - (*y * sin(c->gamma)));
	calc_y = roundf(*x * sin(c->gamma) + (*y * cos(c->gamma)));
	*x = calc_x;
	*y = calc_y;
}

void	rotate_y(int *x, int *z, t_coord *c)
{
	double	calc_x;
	double	calc_z;

	calc_x = roundf(*x * cos(c->tetha) + (*z * sin(c->tetha)));
	calc_z = roundf(*z * cos(c->tetha) - (*x * sin(c->tetha)));
	*x = calc_x;
	*z = calc_z;
}

void	rotate_x(int *y, int *z, t_coord *c)
{
	double	calc_z;
	double	calc_y;

	calc_y = roundf(*y * cos(c->alpha) - (*z * sin(c->alpha)));
	calc_z = roundf(*y * sin(c->alpha) + (*z * cos(c->alpha)));
	*y = calc_y;
	*z = calc_z;
}
