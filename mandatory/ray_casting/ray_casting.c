/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-amr <moel-amr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:34:11 by moel-amr &        #+#    #+#             */
/*   Updated: 2025/08/13 15:15:04 by moel-amr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calculate_first_intersection(t_ray_cast_data *data,
		t_all_data *all_data)
{
	if (data->x_ray_direction > 0)
		data->ray_distance_x = data->delta_x * ((data->map_x + 1)
				- all_data->player->x);
	else if (data->x_ray_direction < 0)
		data->ray_distance_x = data->delta_x * (all_data->player->x
				- data->map_x);
	else
		data->ray_distance_x = INFINITY;
	if (data->y_ray_direction > 0)
		data->ray_distance_y = data->delta_y * ((data->map_y + 1)
				- all_data->player->y);
	else if (data->y_ray_direction < 0)
		data->ray_distance_y = data->delta_y * (all_data->player->y
				- data->map_y);
	else
		data->ray_distance_y = INFINITY;
}

void	step_horizontal(t_ray_cast_data *data, t_ray *ray)
{
	data->distance_to_wall = data->ray_distance_y;
	if (data->y_ray_direction > 0)
		data->map_y += 1;
	else
		data->map_y -= 1;
	data->ray_distance_y += data->delta_y;
	ray->hit_type = HORIZONTAL;
}

void	step_vertical(t_ray_cast_data *data, t_ray *ray)
{
	data->distance_to_wall = data->ray_distance_x;
	if (data->x_ray_direction > 0)
		data->map_x += 1;
	else
		data->map_x -= 1;
	data->ray_distance_x += data->delta_x;
	ray->hit_type = VERTICAL;
}

void	perform_dda(t_ray_cast_data *data, t_all_data *all_data, t_ray *ray)
{
	while (all_data->map[data->map_y][data->map_x] != '1')
	{
		if (data->ray_distance_x < data->ray_distance_y)
			step_vertical(data, ray);
		else
			step_horizontal(data, ray);
	}
	ray->end_x = all_data->player->x + data->distance_to_wall
		* data->x_ray_direction;
	ray->end_y = all_data->player->y + data->distance_to_wall
		* data->y_ray_direction;
}

void	cast_rays(t_all_data *all)
{
	t_ray_cast_data	data;
	double			ray_angle;
	int				screen_x_offset_from_center;
	int				screen_x;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		screen_x_offset_from_center = screen_x - (WIDTH / 2);
		ray_angle = all->player->direction + atan2(screen_x_offset_from_center,
				(WIDTH / 2));
		init_ray(&all->rays[screen_x], all->player, ray_angle);
		init_ray_cast_data(&data, all, ray_angle);
		calculate_deltas(&data);
		calculate_first_intersection(&data, all);
		perform_dda(&data, all, &all->rays[screen_x]);
		screen_x++;
	}
}
