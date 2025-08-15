/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-amr <moel-amr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:33:45 by moel-amr &        #+#    #+#             */
/*   Updated: 2025/08/12 13:48:55 by moel-amr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_ray(t_ray *ray, t_player *player, double angle)
{
	ray->start_x = player->x;
	ray->start_y = player->y;
	ray->end_x = 0;
	ray->end_y = 0;
	ray->angle = angle;
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	if (ray->angle >= 2 * M_PI)
		ray->angle -= 2 * M_PI;
}

void	init_ray_cast_data(t_ray_cast_data *data, t_all_data *all_data,
		double angle)
{
	data->x_ray_direction = cos(angle);
	data->y_ray_direction = sin(angle);
	data->ray_distance_x = 0;
	data->ray_distance_y = 0;
	data->map_x = (int)(all_data->player->x);
	data->map_y = (int)(all_data->player->y);
	data->distance_to_wall = 0;
}

void	calculate_deltas(t_ray_cast_data *data)
{
	if (data->x_ray_direction != 0)
		data->delta_x = fabs(1 / data->x_ray_direction);
	if (data->y_ray_direction != 0)
		data->delta_y = fabs(1 / data->y_ray_direction);
}
