/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_mac.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheel-n <jcheel-n@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:51:44 by eavedill          #+#    #+#             */
/*   Updated: 2024/01/11 19:46:53 by jcheel-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	key_events_resets(int key, t_field *field)
{
	if (key == XK_R)
	{
		field->camera = field->orig_camera;
		dump_mem_2_scr(field);
		printf("Restarting Camera\n");
	}
	else if (key == XK_L)
	{
		field->light = ft_clone_light(field->orig_light);
		dump_mem_2_scr(field);
		printf("Restarting Light\n");
	}
}

// printf("Entro en keyevents press %d -- %p\n", key, field);
int	key_events_press(int key, t_field *field)
{
	if (key == XK_CTRL)
	{
		field->events.key_ctrl_press = 1;
		if (!field->events.btn_left_presd)
			field->aux = create_vect(0, 0, 0);
	}
	else if (key == XK_ALT)
	{
		field->events.key_alt_press = 1;
		if (!field->events.btn_left_presd)
			field->aux = create_vect(0, 0, 0);
	}
	else if (key == XK_SHIFT)
	{
		field->events.key_shift_press = 1;
		if (!field->events.btn_left_presd)
			field->aux = create_vect(0, 0, 0);
	}
	key_events_resets(key, field);
	return (0);
}

int	key_events_release(int key, t_field *field)
{
	if (key == XK_ESC)
		ft_close(field);
	else if (key == XK_CTRL)
	{
		field->events.key_ctrl_press = 0;
		dump_mem_2_scr(field);
	}
	else if (key == XK_ALT)
	{
		field->events.key_alt_press = 0;
		dump_mem_2_scr(field);
	}
	else if (key == XK_SHIFT)
	{
		field->events.key_shift_press = 0;
		dump_mem_2_scr(field);
	}
	return (0);
}
