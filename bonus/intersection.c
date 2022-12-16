/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:18 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/12/16 20:08:04 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	checkiswall(t_data *data, t_index inter, int check, int face)
{
	t_int_idx	index;

	if (face == 1)
		inter.y += check;
	else
		inter.x += check;
	if (inter.y > data->pars.num_lines * SQ)
		return (0);
	if (inter.x > data->pars.max_line * SQ)
		return (0);
	index.x = floor(inter.x / SQ);
	index.y = floor(inter.y / SQ);
	if (index.y < 0 || index.y >= data->pars.num_lines)
		return (0);
	if (index.x < 0 || index.x >= data->pars.max_line)
		return (0);
	if (data->map[index.y][index.x] == '1')
		return (0);
	return (1);
}

double	distance(double x, double y, double x1, double y1)
{
	return (sqrt(pow(x1 - x, 2) + pow(y1 - y, 2)));
}

double	horizontal_inter(t_data *data, t_index player, double angle)
{
	int		check;

	check = 0;
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	data->first.y = floor(player.y / SQ) * SQ;
	if ((angle > 0 && angle < M_PI))
		data->first.y += SQ;
	data->first.x = player.x + (data->first.y - player.y) / tan(angle);
	data->steps.y = SQ;
	if (!(angle > 0 && angle < M_PI))
	{
		data->steps.y *= -1;
		check = -1;
	}
	data->steps.x = data->steps.y / tan(angle);
	if ((angle < 0.5 * M_PI || angle > 1.5 * M_PI) && data->steps.x < 0)
		data->steps.x *= -1;
	if (!(angle < 0.5 * M_PI || angle > 1.5 * M_PI) && data->steps.x > 0)
		data->steps.x *= -1;
	while (checkiswall(data, data->first, check, 1))
	{
		data->first.x += data->steps.x;
		data->first.y += data->steps.y;
	}
	data->inter.ray_hor_inter_x = data->first.x;
	data->inter.ray_hor_inter_y = data->first.y;
	return (distance(player.x, player.y, data->first.x, data->first.y));
}

double	vertical_inter(t_data *data, t_index player, double angle)
{
	int		check;

	check = 0;
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	data->first.x = floor(player.x / SQ) * SQ;
	if ((angle < 0.5 * M_PI || angle > 1.5 * M_PI))
		data->first.x += SQ;
	data->first.y = player.y + (data->first.x - player.x) * tan(angle);
	data->steps.x = SQ;
	if (!(angle < 0.5 * M_PI || angle > 1.5 * M_PI))
	{
		data->steps.x *= -1;
		check = -1;
	}
	data->steps.y = data->steps.x * tan(angle);
	if (!(angle > 0 && angle < M_PI) && data->steps.y > 0)
		data->steps.y *= -1;
	if ((angle > 0 && angle < M_PI) && data->steps.y < 0)
		data->steps.y *= -1;
	while (checkiswall(data, data->first, check, 0))
	{
		data->first.x += data->steps.x;
		data->first.y += data->steps.y;
	}
	data->inter.ray_ver_inter_x = data->first.x;
	data->inter.ray_ver_inter_y = data->first.y;
	return (distance(player.x, player.y, data->first.x, data->first.y));
}